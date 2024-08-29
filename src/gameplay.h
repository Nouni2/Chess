#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include "game/pieces/piece.h"

void setupPieces(std::vector<Piece*>& pieces);
void drawAllPieces(unsigned int shaderProgram, const std::vector<Piece*>& pieces);

#endif // GAMEPLAY_H
