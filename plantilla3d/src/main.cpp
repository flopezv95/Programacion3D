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

glm::mat4 calculateMatrix();

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}
	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica1", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	if (glewInit() != GLEW_OK) {
		std::cout << "could not initialize glew" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	
	glm::vec3 vertex1(-1.0f, -1.0f, 0.0f);
	glm::vec3 vertex2(1.0f, -1.0f, 0.0f);
	glm::vec3 vertex3(0.0f, 1.0f, 0.0f);
	
	glm::vec3 color1(1.0f, 1.0f, 1.0f);
	glm::vec3 color2(1.0f, 1.0f, 1.0f);
	glm::vec3 color3(1.0f, 1.0f, 1.0f);
	
	Vertex point1(vertex1, color1);
	Vertex point2(vertex2, color2);
	Vertex point3(vertex3, color3);
	
	std::vector<Vertex> myVertex;
	myVertex.push_back(point3);
	myVertex.push_back(point2);
	myVertex.push_back(point1);
	
	std::vector<unsigned int> indices = {0, 1, 2};

	Buffer myBuffer(myVertex, indices);
	Shader myShader("data/vertex.glsl", "data/fragment.glsl");
	unsigned int idMatrix = myShader.getMatrix("mvp");
	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		//myShader.setMatrix(idMatrix, calculateMatrix());
		
		myBuffer.draw(myShader);
		glUseProgram(0);
		
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}

glm::mat4 calculateMatrix()
{
	glm::mat4 proj = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 1, 1000);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	model = glm::rotate(model, glm::radians(32.0f), glm::vec3(0, 1, 0));
	return  proj * view * model;
}