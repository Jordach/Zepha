//
// Created by aurailus on 09/04/19.
//

#include <glfw3.h>
#include "InputManager.h"

InputManager::InputManager() {
    for (bool &key : keysDown) {
        key = false;
    }

    for (bool &key : keysPressed) {
        key = false;
    }

    for (bool &key : keysReleased) {
        key = false;
    }
}

void InputManager::update(bool* keys) {
    for (bool &key : keysPressed) {
        key = false;
    }

    for (bool &key : keysReleased) {
        key = false;
    }

    for (int i = 0; i < 1024; i++) {
        bool key = keys[i];

        if (key) {
            if (!keysDown[i]) keysPressed[i] = true;
            keysDown[i] = true;
        }
        else {
            if (!keysReleased[i]) keysReleased[i] = true;
            keysDown[i] = false;
        }
    }

    leftPressed = false;
    leftReleased = false;

    rightPressed = false;
    rightReleased = false;
}

void InputManager::updateLeftMouse(bool down) {
    if (down) {
        if (!leftPressed) leftPressed = true;
        leftDown = true;
    }
    else {
        if (!leftReleased) leftReleased = true;
        leftDown = false;
    }
}

void InputManager::updateRightMouse(bool down){
    if (down) {
        if (!rightPressed) rightPressed = true;
        rightDown = true;
    }
    else {
        if (!rightReleased) rightReleased = true;
        rightDown = false;
    }
}

bool InputManager::isKeyDown(int key) {
    return keysDown[key];
}

bool InputManager::isKeyPressed(int key) {
    return keysPressed[key];
}

bool InputManager::isKeyReleased(int key) {
    return keysReleased[key];
}

bool InputManager::isMouseDown(int button) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) return leftDown;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) return rightDown;
    return false;
}

bool InputManager::isMousePressed(int button) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) return leftPressed;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) return rightPressed;
    return false;
}

bool InputManager::isMouseReleased(int button){
    if (button == GLFW_MOUSE_BUTTON_LEFT) return leftReleased;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) return rightReleased;
    return false;
}