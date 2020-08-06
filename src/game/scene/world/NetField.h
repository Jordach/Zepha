//
// Created by aurailus on 2020-08-05.
//

#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include "../../entity/Entity.h"
#include "../../../util/CovariantPtr.h"
#include "../../../def/DefinitionAtlas.h"

enum class NetField {
    // General
    ID,
    POS,
    VEL,
    ROT,
    SCALE,

    // Entities
    DISPLAY,
    VISUAL_OFF,

    // Players
    LOOK_OFF,
    LOOK_PITCH,
    LOOK_YAW,

    FLYING,

    HAND_INV,
    WIELD_INV,
    WIELD_INDEX,
};