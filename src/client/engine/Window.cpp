//
// Created by aurailus on 26/11/18.
//

#include "Window.h"

Window::Window() : Window(800, 600) {};

Window::Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;

    centerX = width / 2;
    centerY = height / 2;

    mouseLocked = true;
    mouseDown = false;

    resized = false;

    for (bool &key : keys) {
        key = false;
    }
}

int Window::initialize() {
    //Initialize GLFW
    if (!glfwInit()) {
        printf("GLFW init failed");
        glfwTerminate();
        return 1;
    }

    //Version 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Compatibility - No Backwards compat, only forwards
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //TODO: Fix msaa for texture altases.
    //MSAA
//    glfwWindowHint(GLFW_SAMPLES, 16);
//    glEnable(GL_MULTISAMPLE);

    //VSync 1 = On, 0 = Off
    glfwSwapInterval(0);

    //Create the window
    mainWindow = glfwCreateWindow(width, height, "Zeus Alpha", nullptr, nullptr);

    if (!mainWindow) {
        printf("GLFW window failed");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to our window
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    //Initialize GLEW
    GLenum error;
    if ((error = glewInit()) != GLEW_OK) {
        printf("GLEW init failed.");
        fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    //Setup viewport (draw) size
    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(mainWindow, this);
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetWindowSizeCallback(mainWindow, handleResize);
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMaximizeWindow(mainWindow);

    return 0;
}

void Window::update() {
    double mouseX, mouseY;
    if (glfwGetWindowAttrib(mainWindow, GLFW_FOCUSED) == GL_FALSE) {
        mouseLocked = false;
        deltaX = 0;
        deltaY = 0;
    }
    else {
        glfwGetCursorPos(mainWindow, &mouseX, &mouseY);

        if (!mouseLocked) {
            //Allow user to grab window edges without locking the mouse
            if (mouseX > 128 && mouseY > 128 && mouseX < bufferWidth - 128 && mouseY < bufferHeight - 128) mouseLocked = true;
        }
        else {
            deltaX = mouseX - centerX;
            deltaY = centerY - mouseY;
            glfwSetCursorPos(mainWindow, centerX, centerY);
        }
    }

    mouseDown = glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

double Window::getDeltaX() {
    return deltaX;
}

double Window::getDeltaY() {
    return deltaY;
}

bool Window::mouseIsDown() {
    return mouseDown;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void Window::handleKeys(GLFWwindow* glfwWindow, int key, int code, int action, int mode) {
    auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(glfwWindow, GL_TRUE);
    }

    if (key > 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            window->keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            window->keys[key] = false;
        }
    }
}

void Window::handleResize(GLFWwindow *glfwWindow, int width, int height) {
    auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

    glfwGetFramebufferSize(glfwWindow, &window->bufferWidth, &window->bufferHeight);
    glViewport(0, 0, window->bufferWidth, window->bufferHeight);
    window->resized = true;
}
#pragma clang diagnostic pop

Window::~Window() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

GLfloat Window::getBufferWidth() {
    return bufferWidth;
}

GLfloat  Window::getBufferHeight() {
    return bufferHeight;
}

bool Window::getShouldClose() {
    return (bool)glfwWindowShouldClose(mainWindow);
}

bool *Window::getKeysArray() {
    return keys;
}

void Window::swapBuffers() {
    glfwSwapBuffers(mainWindow);
}