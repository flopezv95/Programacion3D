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
#include "../project/Material.h"
#include "../project/Texture.h"
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../glm/gtc/type_ptr.hpp" // glm::value_ptr

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
float posZ = 0.0f;
float posX = 0.0f;
float angleToSpin = 0.0f;

int Init(GLFWwindow* win);

static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		posZ += 0.5f;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		posZ -= 0.5f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		posX += 0.5f;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		posX -= 0.5f;
	}

}

static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		angleToSpin = -30.0f;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		angleToSpin = +30.0f;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		angleToSpin = 0.0f;
	}

}

int main() {
	// init glfw

	if (!glfwInit()) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}
	
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica4", nullptr, nullptr);

	if (Init(win)!=0)
	{
		return -1;
	}

	glfwSetKeyCallback(win, inputCallback);
	glfwSetMouseButtonCallback(win, mouseCallback);

	std::shared_ptr<Mesh> myMesh = Mesh::load("data/gunslinger.obj");
	Mesh cowboyMesh;

	std::shared_ptr<Texture> topTexture = Texture::load("data/top.png");

	Material* myMaterial2 = new Material(topTexture);


	cowboyMesh.addBuffer(std::shared_ptr<Buffer>(new Buffer(myMesh.get()->getVertex(), myMesh.get()->getIndex())), *myMaterial2);

	
	Model * modelEntity = new Model(std::shared_ptr<Mesh>(&cowboyMesh));

	Camera* myCamera=new Camera;
	myCamera->setProjection(glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f));
	myCamera->setViewport(glm::ivec4(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	myCamera->setClearColor(glm::vec3(1.0, 0.2, 0.2));

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
		State::modelMatrix = glm::translate(glm::mat4(), glm::vec3(posX, 0.0f, posZ));
		if (myWorld->getNumEntities() > 0)
		{
			myWorld->draw(deltaTime, angleToSpin,true);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	Shader *myShader = new Shader("data/vertex.glsl", "data/fragment.glsl");

	State::defaultShader = std::shared_ptr<Shader>(myShader);
	State::projectionMatrix = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f);
	State::viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	State::modelMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));

	return 0;
}