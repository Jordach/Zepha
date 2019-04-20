//
// Created by aurailus on 02/12/18.
//

#ifndef GLPROJECT_BLOCKDEF_H
#define GLPROJECT_BLOCKDEF_H

#include <string>
#include "graph/BlockModel.h"
#include "graph/SelectionBox.h"

class BlockDef {

public:
    BlockDef(std::string identifier, BlockModel model, bool solid, SelectionBox selectionBox);

    bool         isCulling();
    bool         isSolid();
    BlockModel&  getModel();
    std::string  getIdentifier();
    SelectionBox getSelectionBox();
private:
    bool culls;
    bool solid;
    SelectionBox selectionBox;
    BlockModel model;
    std::string identifier;
};


#endif //GLPROJECT_BLOCKDEF_H
