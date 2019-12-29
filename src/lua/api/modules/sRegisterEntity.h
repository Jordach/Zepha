//
// Created by aurailus on 11/10/19.
//

#pragma once

#include <sol2/sol.hpp>

namespace ServerApi {
    void register_entity(sol::state& lua, sol::table& core) {
        core["registered_entities"] = lua.create_table();

        core.set_function("register_entity", [&](sol::this_environment env, sol::optional<std::string> identifier, sol::optional<sol::table> data) {
            if (!identifier || !identifier->length()) throw "expected a string as the first argument.";
            if (!data) throw "expected a table as the second argument.";

            auto modname = static_cast<sol::environment>(env).get<std::string>("_MODNAME");

            if (identifier->compare(0, modname.length() + 1, modname + ":")) throw
                        "identifier '" + *identifier + "' must begin with the calling mod's prefix, '" + modname + "'.";

            (*data)["__index"] = *data;
            core["registered_entities"][*identifier] = *data;
        });
    }
}