//
// Created by aurailus on 18/04/19.
//

#ifndef ZEUS_GAMEDEFS_H
#define ZEUS_GAMEDEFS_H

#include "texture/TextureAtlas.h"
#include "block/client/LocalBlockAtlas.h"
#include "../api/LuaApi.h"

class LocalDefs {
public:
    LocalDefs() = default;
    explicit LocalDefs(std::string tex_path);

    LocalBlockAtlas& blocks();
    TextureAtlas& textures();

    ~LocalDefs() = default;
private:
    TextureAtlas textureAtlas;
    LocalBlockAtlas blockAtlas;
    LuaApi luaApi;
};


#endif //ZEUS_GAMEDEFS_H