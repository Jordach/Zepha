//
// Created by aurailus on 14/12/18.
//

#ifndef GLPROJECT_BLOCKCHUNK_H
#define GLPROJECT_BLOCKCHUNK_H

#include <vec3.hpp>
#include <vector>
#include <iostream>
#include "../../util/Vec.h"
#include "../../util/net/Packet.h"
#include "../../util/Vec.h"

class BlockChunk {
public:
    BlockChunk();
    explicit BlockChunk(std::vector<int> blocks);
    BlockChunk(std::vector<int> blocks, glm::vec3 pos);

    glm::vec3 pos;

    bool adjacent[6] = {false, false, false, false, false, false};

    bool isEmpty();
    bool allAdjacentsExist();

    int getBlock(int ind);
    int getBlock(glm::vec3* pos);
    int getBlock(int x, int y, int z);

    bool setBlock(glm::vec3* pos, int ind);

    std::vector<int> rleEncode();
    void rleDecode(std::vector<int>& blocksRle, std::vector<int>& buffer);

    std::string serialize();
    bool deserialize(std::string gzip);

    static std::vector<int> deserializeToVec(std::string gzip);
private:
    std::vector<int> blocks;
    bool empty;
};

#endif //GLPROJECT_BLOCKCHUNK_H