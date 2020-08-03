//
// Created by aurailus on 2020-07-28.
//

#pragma once

#include <memory>
#include <glm/vec3.hpp>

#include "../../entity/Entity.h"
#include "../../../util/CovariantPtr.h"
#include "../../../def/DefinitionAtlas.h"

class World;
class Packet;
class Subgame;
class Inventory;
class Dimension;
class Deserializer;
class InventoryList;

class Player : public virtual Entity {
public:
    enum class NetField {
        ID, POS, VEL, PITCH, YAW, LOOK_OFF, FLYING,
        HAND_INV, WIELD_INV, WIELD_INDEX };

    Player(SubgamePtr game, DimensionPtr dim, unsigned int id = 0) :
            game(game), dim(dim), id(id), lookOffset(0, 1.65, 0) {
        collision = {{-0.3, 0, -0.3}, {0.3, 1.8, 0.3}};
    }

    virtual unsigned int getId();
    virtual void setId(unsigned int id);

    virtual void setPos(glm::vec3 pos, bool assert = false);
    virtual void setVel(glm::vec3 vel, bool assert = false);

    virtual float getYaw();
    virtual void setYaw(float yaw, bool assert = false);

    virtual float getPitch();
    virtual void setPitch(float pitch, bool assert = false);

    virtual glm::vec3 getLookOffset();
    virtual void setLookOffset(glm::vec3 lookOffset, bool assert = false);

    virtual bool isFlying();
    virtual void setFlying(bool flying, bool assert = false);

    virtual std::string& getHandList();
    virtual void setHandList(const std::string& list, bool assert = false);

    virtual std::string& getWieldList();
    virtual void setWieldList(const std::string& list, bool assert = false);

    virtual unsigned short getWieldIndex();
    virtual void setWieldIndex(unsigned short index, bool assert = false);

    virtual InventoryPtr getInventory() = 0;
    DimensionPtr getDimension();

    virtual void handleAssertion(Deserializer& d) = 0;
protected:
    virtual void assertField(Packet packet) = 0;

    unsigned int id = 0;

    SubgamePtr game;
    DimensionPtr dim;

    float yaw = 0;
    float pitch = 0;

    glm::vec3 lookOffset {};

    bool flying = false;

    std::string handList = "";
    std::string wieldList = "";

    unsigned int handItem = DefinitionAtlas::AIR;
    unsigned int wieldItem = DefinitionAtlas::AIR;

    unsigned int wieldIndex = 0;
};
