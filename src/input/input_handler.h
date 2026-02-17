#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GLFW/glfw3.h>

// Declare global parameters to be adjusted
extern float boardScale;
extern float translateCorrectionX;
extern float translateCorrectionY;
extern bool enableInput; // Boolean to enable/disable input handling

// Function to handle key input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // INPUT_HANDLER_H
