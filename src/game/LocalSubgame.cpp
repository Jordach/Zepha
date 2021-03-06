//
// Created by aurailus on 18/04/19.
//

#include "LocalSubgame.h"

LocalSubgame::LocalSubgame(const std::string& texPath) :
    texPath(texPath),
    textures(2048),

    lua(std::make_unique<LocalLuaParser>(*this)),
    biomes(std::make_unique<LocalBiomeAtlas>()),
    defs(std::make_unique<LocalDefinitionAtlas>(textures)) {

    textures.loadDirectory(texPath);
}

void LocalSubgame::init(WorldPtr world, PlayerPtr player, ClientState& state) {
    lua->init(world, player, state);
}

void LocalSubgame::update(double delta) {
    lua->update(delta);
    textures.update();
}

LocalSubgame::~LocalSubgame() {}
