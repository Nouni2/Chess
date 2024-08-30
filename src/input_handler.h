#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GLFW/glfw3.h>

// Declare global parameters to be adjusted
extern float param_1;
extern float param_2;
extern float param_3;
extern bool enableInput; // Boolean to enable/disable input handling

// Function to handle key input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // INPUT_HANDLER_H
