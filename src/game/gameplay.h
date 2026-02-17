#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include <memory>
#include "game/pieces/piece.h"

void setupPieces(std::vector<std::unique_ptr<Piece>>& pieces);
void drawAllPieces(unsigned int shaderProgram, const std::vector<std::unique_ptr<Piece>>& pieces);

#endif // GAMEPLAY_H
