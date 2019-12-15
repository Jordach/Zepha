//
// Created by aurailus on 05/02/19.
//

#include "GameGui.h"
#include "components/compound/GUIInventoryList.h"

GameGui::GameGui(glm::vec2 bufferSize, LocalDefs& defs, Renderer& renderer) :
    menuRoot(std::make_shared<GUIContainer>("__luaroot")),
    handList(std::make_shared<GUIInventoryList>("hand")),
    builder(list, hand, defs, menuRoot),
    renderer(renderer),
    win(bufferSize),
    list(60, 12),
    hand(1, 1),
    defs(defs) {

    auto crosshair = std::make_shared<GUIRect>("crosshair");
    crosshair->create({22, 22}, {}, defs.textures["crosshair"]);
    crosshair->setPos({bufferSize.x / 2 - 11, bufferSize.y / 2 - 9});
    builtIn.add(crosshair);

    auto viginette = std::make_shared<GUIRect>("viginette");
    viginette->create(bufferSize, {}, defs.textures["viginette"]);
    builtIn.add(viginette);

    add(menuRoot);

    handList->create({3, 3}, {}, {}, hand, hand, defs);
    add(handList);
}

void GameGui::update(double delta) {
    Drawable::update(delta);

    handList->setPos((renderer.window.getMousePos() - glm::ivec2(24)) / 3 * 3);

    renderer.window.setCursorHand(menuRoot->mouseActivity(renderer.window.getMousePos()));
    if (renderer.window.input.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
        menuRoot->triggerClick(renderer.window.getMousePos());
}

void GameGui::winResized(glm::ivec2 win) {
    this->win = win;

    builtIn.get<GUIRect>("crosshair")->setPos({win.x / 2 - 11, win.y / 2 - 9});
    builtIn.get<GUIRect>("viginette")->setScale(win);

    builder.build(win);
}

void GameGui::setMenu(const std::string& menu, const std::map<std::string, std::function<void(glm::ivec2)>>& callbacks) {
    menuState = "menu"; //TODO: Implement the menu state properly
    builder.setGui(menu, callbacks);
    builder.build(win);
}

void GameGui::closeMenu() {
    builder.clear();
    menuState = "";
}

const std::string &GameGui::getMenuState() {
    return menuState;
}

void GameGui::setVisible(bool visible) {
    GUIComponent::setVisible(visible);
    builtIn.setVisible(visible);
}

void GameGui::drawViginette(Renderer &renderer) {
    builtIn.draw(renderer);
}
