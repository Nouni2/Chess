#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include "game/pieces/piece.h"

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window);
Piece* findPieceAtPosition(int col, int row, const std::vector<std::unique_ptr<Piece>>& pieces);

#endif // MOUSE_H
