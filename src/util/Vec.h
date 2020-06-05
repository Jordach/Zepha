//
// Created by aurailus on 29/03/19.
//

#pragma once

#include <array>
#include <glm/vec3.hpp>
#include <cstddef>
#include <functional>
#include "Space.h"

namespace Vec {
    struct vec3 {
        size_t operator()(const glm::vec3& k)const {
            return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
        }
    };

    struct ivec3 {
        size_t operator()(const glm::ivec3& k)const {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
        }
    };

    const static std::array<glm::ivec3, 6> adj = { glm::ivec3 {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1} };

    static inline void indAssignVec(int ind, glm::ivec3& vec, unsigned int wid = 16) {
        vec.y = ind / (wid * wid);
        ind -= ((int)vec.y * wid * wid);
        vec.z = ind / wid;
        vec.x = ind % wid;
    }
};

