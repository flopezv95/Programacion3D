//
//  main.cpp
//  3DProgrammingTemplate
//
//  Created by Ingrid Guerrero on 5/13/19.
//  Copyright © 2019 Ingrid Guerrero. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Buffer.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, false);
    //glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Practica1", nullptr, nullptr);
    if (!win) {
        std::cout << "could not create opengl window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);
    
    glewExperimental = GL_TRUE;
    
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        glfwDestroyWindow(win);
        glfwTerminate();
        return -1;
    }
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_SCISSOR_TEST);
    
    
    glm::vec3 color1(1.0f, 1.0f, 1.0f);
//    glm::vec3 color2(1.0f, 1.0f, 1.0f);
//    glm::vec3 color3(1.0f, 1.0f, 1.0f);
    //Esto no sirve
//    Vertex point1(vertex1, color1);
//    Vertex point2(vertex2, color2);
//    Vertex point3(vertex3, color3);
    
    std::vector<Vertex> myVertex;
    myVertex.push_back({glm::vec3(-1.0f, -1.0f, 0.0f), color1});
    myVertex.push_back({glm::vec3(1.0f, -1.0f, 0.0f), color1});
    myVertex.push_back({glm::vec3(0.0f,  1.0f, 0.0f), color1});
    
    std::vector<GLuint> indices = {0, 1, 2};
    
    Buffer *myBuffer = new Buffer(myVertex, indices);
    Shader *myShader = new Shader("Resource/vertex.glsl", "Resource/fragment.glsl");
    //unsigned int idMatrix = myShader.getMatrix("mvp");
    // main loop
    float angle = 0;
    double lastTime = glfwGetTime();
    while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
        
        
        
        // get delta time
        float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();
        
        // get window size
        int screenWidth, screenHeight;
        glfwGetWindowSize(win, &screenWidth, &screenHeight);
        //myShader.setMatrix(idMatrix, calculateMatrix());
        
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        myShader->use();
        
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
        
        myShader->setMatrix(myShader->getLocation("mvp"), model);
        
        myBuffer->draw(myShader);
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

