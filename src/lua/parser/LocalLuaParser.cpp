//
// Created by aurailus on 17/12/18.
//

#include "LocalLuaParser.h"

#include "../ErrorFormatter.h"
#include "../register/RegisterBlocks.h"
#include "../register/RegisterItems.h"
#include "../register/RegisterBiomes.h"
#include "../register/RegisterKeybinds.h"
#include "../../game/ClientState.h"

// Usertypes
#include "../api/class/LuaGuiElement.h"
#include "../api/usertype/cItemStack.h"
#include "../api/class/LocalLuaPlayer.h"
#include "../api/usertype/cLuaEntity.h"
#include "../api/usertype/cInventoryRef.h"
#include "../api/usertype/cAnimationManager.h"

// Modules
#include "../api/modules/delay.h"
#include "../api/modules/register_block.h"
#include "../api/modules/register_blockmodel.h"
#include "../api/modules/register_biome.h"
#include "../api/modules/register_item.h"
#include "../api/modules/register_entity.h"
#include "../api/modules/set_block.h"
#include "../api/modules/get_block.h"
#include "../api/modules/remove_block.h"
#include "../api/modules/add_entity.h"
#include "../api/modules/remove_entity.h"
#include "../api/modules/register_keybind.h"
#include "../api/modules/time.h"
#include "../api/modules/create_structure.h"

// Functions
#include "../api/functions/trigger_event.h"
#include "../api/functions/update_entities.h"

LocalLuaParser::LocalLuaParser(): keybinds(this) {}

void LocalLuaParser::init(ClientGame& defs, LocalWorld& world, Player& player, ClientState& state) {
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math, sol::lib::table);

    loadApi(defs, world, player);
    handler.executeMods(std::bind(&LocalLuaParser::runFileSandboxed, this, std::placeholders::_1));
    state.renderer.window.input.setCallback(std::bind(&LuaKeybindHandler::keybindHandler, &keybinds, std::placeholders::_1, std::placeholders::_2));

    registerDefs(defs);
}

void LocalLuaParser::update(double delta) {
    LuaParser::update(delta);

    this->delta += delta;
    while (this->delta > static_cast<double>(UPDATE_STEP)) {
        safe_function(core["__builtin"]["update_entities"], static_cast<double>(UPDATE_STEP));
        this->delta -= static_cast<double>(UPDATE_STEP);
    }
}

LocalModHandler& LocalLuaParser::getHandler() {
    return handler;
}

void LocalLuaParser::loadApi(ClientGame &defs, LocalWorld &world, Player& player) {
    //Create Zepha Table
    core = lua.create_table();
    lua["zepha"] = core;
    core["__builtin"] = lua.create_table();

    // Types
    ClientApi::entity            (lua);
    ClientApi::animation_manager (lua);
    ClientApi::local_player      (lua);
    ClientApi::inventory         (lua);
    ClientApi::item_stack        (lua);
    ClientApi::gui_element       (lua);

    core["client"] = true;
    core["player"] = LocalLuaPlayer(player);

    // Modules
    Api::delay (core, delayed_functions);

    Api::register_block      (lua, core);
    Api::register_blockmodel (lua, core);
    Api::register_biome      (lua, core);
    Api::register_item       (lua, core);
    Api::register_entity     (lua, core);
    Api::register_keybind    (lua, core);

    Api::get_block    (core, defs.defs, world);
    Api::set_block    (core, defs.defs, world);
    Api::remove_block (core, defs.defs, world);

    Api::add_entity_c    (lua, core, defs, world);
    Api::remove_entity_c (lua, core, defs, world);

    Api::time(lua, core);

    Api::create_structure (lua, core);

    // Functions
    Api::update_entities(lua);

    // Create sandboxed runfile()
    lua["dofile"] = lua["loadfile"] = sol::nil;
    lua.set_function("runfile", &LocalLuaParser::runFileSandboxed, this);
}

void LocalLuaParser::registerDefs(ClientGame &defs) {
    RegisterBlocks  ::client(core, defs);
    RegisterItems   ::client(core, defs);
    RegisterBiomes  ::client(core, defs);
    RegisterKeybinds::client(core, keybinds);
}

sol::protected_function_result LocalLuaParser::errorCallback(sol::protected_function_result errPfr) const {
    sol::error err = errPfr;
    std::string errString = err.what();

    std::string::size_type slash = errString.find('/');
    assert(slash != std::string::npos);

    std::string modString = errString.substr(0, slash);

    std::string::size_type lineNumStart = errString.find(':', slash);
    assert(lineNumStart != std::string::npos);
    std::string::size_type lineNumEnd = errString.find(':', lineNumStart + 1);
    assert(lineNumEnd != std::string::npos);

    std::string fileName = errString.substr(0, lineNumStart);
    int lineNum = std::stoi(errString.substr(lineNumStart + 1, lineNumEnd - lineNumStart - 1));

    for (const auto& mod : handler.cGetMods()) {
        if (mod.config.name == modString) {
            for (auto& file : mod.files) {
                if (file.path == fileName) {
                    std::cout << std::endl << ErrorFormatter::formatError(fileName, lineNum, errString, file.file) << std::endl;
                    exit(1);
                }
            }
            break;
        }
    }

    std::cout << Log::err << "Zepha has encountered an error, and ErrorFormatter failed to format it:"
              << std::endl << std::endl << errString << Log::endl;

    exit(1);
    return errPfr;
}

sol::protected_function_result LocalLuaParser::runFileSandboxed(std::string file) {
    size_t modname_length = file.find('/');

    if (modname_length == std::string::npos) {
        std::cout << Log::err << "Filestring \"" + file + "\" is invalid." << Log::endl;
        return nullptr;
    }

    std::string modname = file.substr(0, modname_length);

    for (const LuaMod& mod : handler.cGetMods()) {
        if (modname == mod.config.name) {

            for (const LuaModFile& f : mod.files) {
                if (f.path == file) {

                    sol::environment env(lua, sol::create, lua.globals());
                    env["_PATH"] = f.path.substr(0, f.path.find_last_of('/') + 1);
                    env["_FILE"] = f.path;
                    env["_MODNAME"] = mod.config.name;

                    return lua.safe_script(f.file, env, std::bind(&LocalLuaParser::errorCallback, this,
                            std::placeholders::_2), "@" + f.path, sol::load_mode::text);
                }
            }

            std::cout << Log::err << "Error opening \"" + file + "\", not found." << Log::endl;
            break;
        }
    }
}
