//
// Created by aurailus on 13/08/19.
//

#pragma once

#include <memory>
#include "AtlasRef.h"
#include "../LocalDefs.h"

class Font {
public:
    Font() = default;
    Font(TextureAtlas& atlas, std::shared_ptr<AtlasRef> tex);
    uint getCharWidth(char c);
    glm::vec4 getCharUVs(char c);

    const static unsigned int amountOfChars = 95;
    const static unsigned int charWidth = 7;
    const static unsigned int charHeight = 9;
private:
    void getCharWidths(TextureAtlas& atlas);

    glm::vec2 atlasSize {};

    std::shared_ptr<AtlasRef> fontTex = nullptr;
    std::array<unsigned short, 95> charWidths {};
};
