#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include "game/pieces/piece.h"

extern std::vector<Piece*> pieces;  // Declare the global pieces vector

void setupPieces(std::vector<Piece*>& pieces);
void drawAllPieces(unsigned int shaderProgram, const std::vector<Piece*>& pieces);
void handleMove(Piece* piece, int x, int y);

#endif // GAMEPLAY_H
