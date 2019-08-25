//
// Created by aurailus on 02/12/18.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#ifndef GLPROJECT_MESHPART_H
#define GLPROJECT_MESHPART_H

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <glm/vec4.hpp>
#include <glm/gtx/normal.hpp>

#include "ShaderMod.h"
#include "../texture/TextureAtlas.h"
#include "../../game/scene/world/graph/BlockModelVertex.h"

struct MeshPart {
    MeshPart(const std::vector<BlockModelVertex>& vertices, const std::vector<unsigned int>& indices, std::shared_ptr<AtlasRef> texture);

    std::vector<BlockModelVertex> vertices;
    std::vector<unsigned int> indices;

    std::shared_ptr<AtlasRef> texture;

    ShaderMod shaderMod = ShaderMod::NONE;
    float modValue = 0;
};


#endif //GLPROJECT_MESHPART_H

#pragma clang diagnostic pop