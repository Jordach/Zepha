//
// Created by aurailus on 11/06/19.
//

#include "LuaParser.h"

LuaParser::LuaParser(const std::string& root) :
        root(root), root_path(root) {}

void LuaParser::update() {
    //Loop through and call delayed functions
    auto it = delayed_functions.begin();
    while (it != delayed_functions.end()) {
        DelayedFunction& f = *it;
        f.timeout -= 0.048f;
        if (f.timeout <= 0) {
            if (f.function(sol::as_args(f.args))) {
                f.timeout = f.initial_timeout;
            } else {
                it = delayed_functions.erase(it);
                continue;
            }
        }
        it++;
    }
}

int LuaParser::DoFileSandboxed(std::string file) {
    if (root_path.contains(Path(file))) {
        lua.script_file(file);
    }
    else {
        std::cout << Log::err << "Error opening \"" + file + "\", access denied." << Log::endl;
    }
}

sol::table LuaParser::vecToTable(glm::vec3 vec) {
    return lua.create_table_with("x", vec.x, "y", vec.y, "z", vec.z);
}