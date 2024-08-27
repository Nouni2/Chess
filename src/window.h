#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow* initWindow(int width, int height, const char* title);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif // WINDOW_H
