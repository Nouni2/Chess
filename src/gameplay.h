#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include "game/pieces/piece.h"

extern std::vector<Piece*> pieces;  // Declare the global pieces vector

void setupPieces(std::vector<Piece*>& pieces);
void drawAllPieces(unsigned int shaderProgram, const std::vector<Piece*>& pieces);
void handleMove(Piece* piece, int x, int y);

struct LastMove {
    int startX;
    int startY;
    int endX;
    int endY;
    Piece* piece;  // Pointer to the piece that moved
    bool wasDoubleStep;  // True if the last move was a pawn's double step

    LastMove() : startX(-1), startY(-1), endX(-1), endY(-1), piece(nullptr), wasDoubleStep(false) {}
};

extern LastMove lastMove;

#endif // GAMEPLAY_H
