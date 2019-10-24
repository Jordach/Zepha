//
// Created by aurailus on 11/10/19.
//

#pragma once

#include <sol2/sol.hpp>

namespace ServerApi {
    void register_entity(sol::state& lua, sol::table& core) {
        //TODO: Do anything
        core["registered_entities"] = lua.create_table();

        core.set_function("register_entity", [&](std::string identifier, sol::table data) {
            if (identifier.length() == 0) throw "Missing Identifier";
            data["__index"] = data;
            core["registered_entities"][identifier] = data;
        });
    }
}