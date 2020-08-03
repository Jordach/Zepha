//
// Created by aurailus on 29/06/19.
//

#include "ServerPlayer.h"

#include "ServerClient.h"
#include "../../Serializer.h"
#include "../../Deserializer.h"
#include "../world/ServerWorld.h"
#include "../../../game/inventory/ServerInventoryRefs.h"

ServerPlayer::ServerPlayer(ServerClient& client, SubgamePtr game, DimensionPtr dim) :
    Player(game, dim, client.id), client(client),
    inventory(dim->getWorld().getRefs()->createInventory("player:" + std::to_string(id))) {}

void ServerPlayer::assertField(Packet packet) {
    packet.type = PacketType::THIS_PLAYER_INFO;
    packet.sendTo(getPeer(), PacketChannel::INTERACT);
}

void ServerPlayer::handleAssertion(Deserializer &d) {
    while (!d.atEnd()) {
        switch (static_cast<NetField>(d.read<unsigned int>())) {
            case NetField::POS:    setPos(d.read<glm::vec3>()); break;
            case NetField::VEL:    setVel(d.read<glm::vec3>()); break;
            case NetField::PITCH:  setPitch(d.read<float>());   break;
            case NetField::YAW:    setYaw(d.read<float>());     break;
            case NetField::FLYING: setFlying(d.read<bool>());   break;

            case NetField::HAND_INV: setHandList(d.read<std::string>()); break;
            case NetField::WIELD_INV: setWieldList(d.read<std::string>());   break;
            case NetField::WIELD_INDEX: setWieldIndex(d.read<unsigned short>()); break;
        }
    }
}

void ServerPlayer::setPos(glm::vec3 pos, bool assert) {
    glm::vec3 lastMapBlock = Space::MapBlock::world::fromBlock(this->pos);
    glm::vec3 newMapBlock = Space::MapBlock::world::fromBlock(pos);

    Player::setPos(pos, assert);

    if (newMapBlock != lastMapBlock && !changedMapBlocks) changedMapBlocks = true;
}

InventoryPtr ServerPlayer::getInventory() {
    return inventory;
}

ENetPeer* ServerPlayer::getPeer() {
    return client.peer;
}
