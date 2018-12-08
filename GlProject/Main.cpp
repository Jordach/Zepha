#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "engine/Window.h"
#include "engine/Camera.h"
#include "engine/graphics/Texture.h"
#include "mesh/BlockModel.h"
#include "engine/graphics/Shader.h"
#include "mesh/MeshGenerator.h"
#include "engine/Entity.h"
#include "engine/Timer.h"
#include "engine/TextureAtlas.h"

Window* window;
Shader* shader;
std::vector<Entity*> entities;
Camera* camera;

TextureAtlas* atlas;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

BlockModel* createBlockModel() {

    Vertex* leftVerts = new Vertex[4] {
            Vertex(new glm::vec3(0.0f, 0.0f, 0.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
            Vertex(new glm::vec3(0.0f, 0.0f, 1.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
            Vertex(new glm::vec3(0.0f, 1.0f, 1.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
            Vertex(new glm::vec3(0.0f, 1.0f, 0.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
    };
    auto* leftInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* leftPart = new MeshPart(leftVerts, 4, leftInds, 6, "default_grass_side", atlas);

    Vertex* rightVerts = new Vertex[4] {
            Vertex(new glm::vec3(1.0f, 0.0f, 0.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 0.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 1.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 0.0f, 1.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
    };
    auto* rightInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* rightPart = new MeshPart(rightVerts, 4, rightInds, 6, "default_grass_side", atlas);

    Vertex* topVerts = new Vertex[4] {
            Vertex(new glm::vec3(0.0f, 1.0f, 0.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
            Vertex(new glm::vec3(0.0f, 1.0f, 1.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 1.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 0.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
    };
    auto* topInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* topPart = new MeshPart(topVerts, 4, topInds, 6, "default_grass_top", atlas);

    Vertex* bottomVerts = new Vertex[4] {
            Vertex(new glm::vec3(0.0f, 0.0f, 0.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 0.0f, 0.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 0.0f, 1.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
            Vertex(new glm::vec3(0.0f, 0.0f, 1.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
    };
    auto* bottomInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* bottomPart = new MeshPart(bottomVerts, 4, bottomInds, 6, "default_dirt", atlas);

    Vertex* frontVerts = new Vertex[4] {
            Vertex(new glm::vec3(0.0f, 0.0f, 1.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
            Vertex(new glm::vec3(1.0f, 0.0f, 1.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 1.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
            Vertex(new glm::vec3(0.0f, 1.0f, 1.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
    };
    auto* frontInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* frontPart = new MeshPart(frontVerts, 4, frontInds, 6, "default_grass_side", atlas);

    Vertex* backVerts = new Vertex[4] {
            Vertex(new glm::vec3(0.0f, 0.0f, 0.0f), nullptr, new glm::vec2(0.0f, 1.0f)),
            Vertex(new glm::vec3(0.0f, 1.0f, 0.0f), nullptr, new glm::vec2(0.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 1.0f, 0.0f), nullptr, new glm::vec2(1.0f, 0.0f)),
            Vertex(new glm::vec3(1.0f, 0.0f, 0.0f), nullptr, new glm::vec2(1.0f, 1.0f)),
    };
    auto* backInds = new unsigned int[6] {
            0, 1, 2, 2, 3, 0
    };

    auto* backPart = new MeshPart(backVerts, 4, backInds, 6, "default_grass_side", atlas);

    return new BlockModel(leftPart, rightPart, topPart, bottomPart, frontPart, backPart, nullptr, true, true);
}

void makeEntities(BlockModel* model) {
	int array[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++) { // NOLINT(modernize-loop-convert)
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_SIZE; k++) {
//				array[i][j][k] = (j < 8) ? 1 : 0;
                array[i][j][k] = (int)round(rand()%2);
			}
		}
	}

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	MeshGenerator mg;
	mg.build(array, model, vertices, indices);

	auto* mesh = new Mesh();
    mesh->create(&vertices, &indices);

	for (int i = -16; i < 16; i++) {
		for (int j = -16; j < 16; j++) {
			auto *chunk = new Entity();
			chunk->create(mesh);
			chunk->setPosition(glm::vec3(i * CHUNK_SIZE, 0, j * CHUNK_SIZE));
			chunk->setScale(1);
			entities.push_back(chunk);
		}
	}
}

int main() {
	Timer boot("Initialization");

    //Window
    window = new Window(1366, 768);
    window->initialize();

    //Create camera
    camera = new Camera(glm::vec3(0.0f, 16.0f, 0.0f), glm::vec3(0, 1, 0), -90.0f, -45.0f, 10.0f, 0.1f);

    //Load Textures
	atlas = new TextureAtlas("../Textures");

    //Create model
    BlockModel* model = createBlockModel();

	//Create entities
    makeEntities(model);

    //Create shader
	shader = new Shader();
	shader->createFromFile("../GlProject/shader/world.vs", "../GlProject/shader/world.fs");

	glm::mat4 projectionMatrix = glm::perspective(45.0f, window->getBufferWidth() / window->getBufferHeight(), 0.1f, 1000.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    boot.elapsed();

	//Game Loop
	while (!window->getShouldClose()) {
	    Timer t("Game Loop");

	    auto now = (GLfloat)glfwGetTime();
	    deltaTime = now - lastTime;
	    lastTime = now;

		//Get & Handle Input
		glfwPollEvents();
		window->update();

		camera->keyControl(window->getKeysArray(), deltaTime);
		camera->mouseControl(window->getDeltaX(), window->getDeltaY());

		//Clear Window
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->useShader();

		glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));

        atlas->getTexture()->use();

		for (auto &entity : entities) {
			glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, glm::value_ptr(entity->getModelMatrix()));
			entity->draw();
        }

        Shader::clearShader();

		//Finish Drawing
		window->swapBuffers();

//		t.elapsedMs();
	}

	return 0;
}