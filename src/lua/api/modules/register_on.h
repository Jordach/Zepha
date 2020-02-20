//
// Created by aurailus on 2020-02-17.
//

#pragma once

namespace Api {
    static void register_on_s(sol::state& lua, sol::table& core, ServerLuaParser& parser) {
        core["registered_callbacks"] = lua.create_table();
        core["registered_callbacks"]["player_join"] = lua.create_table();
        core["registered_callbacks"]["player_connect"] = lua.create_table();
        core["registered_callbacks"]["player_disconnect"] = lua.create_table();

        lua.script(R"(
            zepha.register_on = function(event, callback)
                if type(event) ~= "string" then return nil end
                if type(callback) ~= "function" then return nil end
                if zepha.registered_callbacks[event] == nil then return nil end

                table.insert(zepha.registered_callbacks[event], callback)
            end
        )");
    }
}