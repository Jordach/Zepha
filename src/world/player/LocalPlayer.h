//
// Created by aurailus on 28/12/18.
//

#pragma once

#include "Player.h"
#include "client/graph/Drawable.h"

#include "util/Target.h"
#include "client/gui/GameGui.h"
#include "world/dim/LocalDimension.h"
#include "client/entity/WireframeEntity.h"

class Input;
class Deserializer;
class LuaGuiElement;
class LocalInventory;
class LocalInventoryRefs;
enum class NetPlayerField;

class LocalPlayer : public virtual DrawableEntity, public Player {
public:
    enum class PlayerControl { FORWARD, LEFT, BACKWARD, RIGHT, JUMP, MOD1, MOD2 };

    LocalPlayer(SubgamePtr game, LocalWorld& world, DimensionPtr dim, Renderer &renderer);

    void update(Input &input, double delta, glm::vec2 mouseDelta);
    virtual void assertField(Packet packet) override;
    virtual void handleAssertion(Deserializer& d) override;

    virtual InventoryPtr getInventory() override;

    virtual void setPos(glm::vec3 pos, bool assert = false) override;
    virtual void setLookOffset(glm::vec3 eyeOffset, bool assert = false) override;
    virtual void setHandList(const std::string& list, bool assert = false) override;
    virtual void setWieldList(const std::string& list, bool assert = false) override;
    virtual void setWieldIndex(unsigned short index, bool assert = false) override;
    virtual void setDim(DimensionPtr dim) override;

    bool isInMenu();
    void showMenu(std::shared_ptr<LuaGuiElement> root);
    void closeMenu();

    void setHud(std::shared_ptr<LuaGuiElement> hud);
    std::shared_ptr<LuaGuiElement> getHud();
    void setHudVisible(bool hudVisible);

    Target& getTarget();

    void draw(Renderer& renderer) override;
    void drawHud(Renderer& renderer);
    void drawMenu(Renderer& renderer);

    ~LocalPlayer();

private:
    bool getKey(Input& input, PlayerControl control);

    void updatePhysics(Input &input, double delta, glm::vec2 mouseDelta);
    void updateCamera();

    void findPointedThing(Input &input);
    void updateWireframe();

    void interact(Input& input, double delta);

    void updateWieldAndHandItems();

    GameGui gameGui;
    DrawableEntity handModel;
    DrawableEntity handItemModel;
    WireframeEntity wireframe;

    Renderer& renderer;

    double breakTime = 0;
    double breakInterval = 0;
    Target target;
};

