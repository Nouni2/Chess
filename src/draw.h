#ifndef DRAW_H
#define DRAW_H

#include "game/pieces/piece.h"

void drawChessboard(unsigned int shaderProgram, unsigned int boardTextures[2], const std::vector<std::pair<int, int>>& legalMoves);
void drawPiece(unsigned int shaderProgram, const Piece& piece);

#endif // DRAW_H
