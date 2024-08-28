#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

void initializeRenderer(unsigned int shaderProgram, GLFWwindow* window);
void resizeRenderer(unsigned int shaderProgram, int windowWidth, int windowHeight);
void setViewport(GLFWwindow* window);

#endif
