#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GL/glew.h" 
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "../project/Buffer.h"
#include "../project/State.h"
#include "../project/Mesh.h"
#include "../project/Model.h"
#include "../project/Camera.h"
#include "../project/World.h"
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../glm/gtc/type_ptr.hpp" // glm::value_ptr

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int Init(GLFWwindow* win);

int main() {
	// init glfw

	if (!glfwInit()) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica1", nullptr, nullptr);


	if (Init(win)!=0)
	{
		return -1;
	}

	Mesh myMesh;

	glm::vec3 color1(0.0f, 1.0f, 1.0f);
	std::vector<Vertex> myVertex;
	myVertex.push_back({ glm::vec3(-1.0f, -1.0f, 0.0f), color1 });
	myVertex.push_back({ glm::vec3(1.0f, -1.0f, 0.0f), color1 });
	myVertex.push_back({ glm::vec3(0.0f,  1.0f, 0.0f), color1 });

	std::vector<GLuint> indices = { 0, 1, 2 };

	myMesh.addBuffer(std::shared_ptr<Buffer>(new Buffer(myVertex, indices)));

	Model * modelEntity = new Model(std::shared_ptr<Mesh>(&myMesh));

	Camera* myCamera=new Camera;
	myCamera->setProjection(glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f));
	myCamera->setViewport(glm::ivec4(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	myCamera->setClearColor(glm::vec3(0.2, 0.2, 0.2));

	World* myWorld = new World;
	myWorld->addEntity(std::shared_ptr<Model>(modelEntity));
	myWorld->addEntity(std::shared_ptr<Camera>(myCamera));

	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();
		if (myWorld->getNumEntities() > 0)
		{
			myWorld->draw(deltaTime, 32.0f);
		}
		glUseProgram(0);
		
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}


int Init(GLFWwindow* win)
{

	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(win);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "could not initialize glew" << std::endl;
		return -1;
	}

	
	Shader *myShader = new Shader("data/vertex.glsl", "data/fragment.glsl");

	State::defaultShader = std::shared_ptr<Shader>(myShader);
	State::projectionMatrix = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f);
	State::viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	State::modelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));

	return 0;
}