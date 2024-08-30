#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window);
Piece* findPieceAtPosition(int col, int row);

#endif // MOUSE_H
