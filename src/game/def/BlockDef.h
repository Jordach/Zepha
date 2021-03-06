//
// Created by aurailus on 10/06/19.
//

#pragma once

#include <string>

#include "ItemDef.h"

#include "lua/Lua.h"
#include "util/Util.h"
#include "lua/Callback.h"
#include "game/def/mesh/BlockModel.h"
#include "game/def/mesh/SelectionBox.h"

class BlockDef : public ItemDef {
public:
    BlockDef(): ItemDef {"", "", 0, 0, ItemDef::Type::BLOCK} {};

    void createModel();
    bool hasInteraction();

    BlockModel model;
    BlockModel farModel;

    bool culls = true;
    bool solid = true;
    bool lightPropagates = false;

    int health = 0;
    int defense = 0;

    glm::ivec3 lightSource {};

    std::vector<SelectionBox> sBoxes {};
    std::vector<SelectionBox> cBoxes {};

    std::unordered_map<Callback, sol::protected_function, Util::EnumClassHash> callbacks {};
};
