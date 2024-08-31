#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include "game/pieces/piece.h"

extern Piece* selectedPiece;  // Declare the selectedPiece as extern
extern std::vector<std::pair<int, int>> legalMoves;

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window);
Piece* findPieceAtPosition(int col, int row, const std::vector<Piece*>& pieces);
#endif // MOUSE_H
