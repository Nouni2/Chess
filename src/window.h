#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow* createWindow(int width, int height, const char* title);
void updateWindow(GLFWwindow* window);

#endif
