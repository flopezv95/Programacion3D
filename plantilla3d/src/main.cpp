#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GL/glew.h" 
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "../project/Shaders.h"
#include "../project/Buffer.h"
#include <vector>
#include "../glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "../glm/gtc/type_ptr.hpp" // glm::value_ptr

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

glm::mat4 calculateMatrix(float angle);

//Soy Maluma baby

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}
	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica1", nullptr, nullptr);
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
	glm::vec3 color1(0.0f, 1.0f, 1.0f);
	std::vector<Vertex> myVertex;
	myVertex.push_back({ glm::vec3(-1.0f, -1.0f, 0.0f), color1 });
	myVertex.push_back({ glm::vec3(1.0f, -1.0f, 0.0f), color1 });
	myVertex.push_back({ glm::vec3(0.0f,  1.0f, 0.0f), color1 });
	std::vector<GLuint> indices = { 0, 1, 2 };
	
	Buffer *myBuffer = new Buffer(myVertex, indices);
	Shader *myShader = new Shader("data/vertex.glsl", "data/fragment.glsl");
	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader->use();
		angle += (32*deltaTime);
		myShader->setMatrix(myShader->getLocation("mvp"), calculateMatrix(angle));

		myBuffer->draw(myShader);
		glUseProgram(0);
		
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}

glm::mat4 calculateMatrix(float angle)
{
	glm::mat4 proj = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	return  proj * view * model;
}