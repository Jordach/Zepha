//
// Created by aurailus on 2019-12-12.
//

#include "GameGuiBuilder.h"
#include "components/compound/GUIInventoryList.h"
//
//std::shared_ptr<GUIComponent> GameGuiBuilder::createComponent(SerializedGuiElem &data) {
//    auto comp = GuiBuilder::createComponent(data);
//    if (comp) return comp;
//
//    //Extra definitions
//
//    glm::vec2 pos {};
//
//    if (data.tokens.count("position")) {
//        auto tokens = splitValue(data.tokens["position"], 2);
//        pos = {stringToNum(tokens[0], PercentBehavior::BUFF_WIDTH),
//               stringToNum(tokens[1], PercentBehavior::BUFF_HEIGHT)};
//    }
//
//    glm::vec2 offset {};
//    if (data.tokens.count("position_anchor")) {
//        auto tokens = splitValue(data.tokens["position_anchor"], 2);
//        offset = {stringToNum(tokens[0], PercentBehavior::DECIMAL),
//                  stringToNum(tokens[1], PercentBehavior::DECIMAL)};
//    }
//
//    glm::vec2 size {};
//    if (data.tokens.count("size")) {
//        auto tokens = splitValue(data.tokens["size"], 2);
//        size = {stringToNum(tokens[0], PercentBehavior::BUFF_WIDTH),
//                stringToNum(tokens[1], PercentBehavior::BUFF_HEIGHT)};
//    }
//
//    pos -= offset * size;
//
//    glm::vec4 padding {};
//    if (data.tokens.count("padding")) {
//        auto tokens = splitValue(data.tokens["padding"], 4);
//        padding = {stringToNum(tokens[0], PercentBehavior::BUFF_HEIGHT),
//                   stringToNum(tokens[1], PercentBehavior::BUFF_WIDTH),
//                   stringToNum(tokens[2], PercentBehavior::BUFF_HEIGHT),
//                   stringToNum(tokens[3], PercentBehavior::BUFF_WIDTH)};
//    }
//
//    else if (data.type == "inventory") {
//        glm::vec4 padding {};
//        if (data.tokens.count("padding")) {
//            auto tokens = splitValue(data.tokens["padding"], 4);
//            padding = {stringToNum(tokens[0], PercentBehavior::BUFF_HEIGHT),
//                       stringToNum(tokens[1], PercentBehavior::BUFF_WIDTH),
//                       stringToNum(tokens[2], PercentBehavior::BUFF_HEIGHT),
//                       stringToNum(tokens[3], PercentBehavior::BUFF_WIDTH)};
//        }
//
//        glm::vec2 innerPadding {};
//        if (data.tokens.count("slot_spacing")) {
//            auto tokens = splitValue(data.tokens["slot_spacing"], 2);
//            innerPadding = {stringToNum(tokens[0], PercentBehavior::BUFF_HEIGHT),
//                            stringToNum(tokens[1], PercentBehavior::BUFF_WIDTH)};
//        }
//
//        auto inv = std::make_shared<GUIInventoryList>(data.key);
//
//        inv->create(glm::vec2(SCALE_MODIFIER), padding * SCALE_MODIFIER, innerPadding * SCALE_MODIFIER, list, defs);
//        inv->setPos(pos);
//        return inv;
//    }
//}
