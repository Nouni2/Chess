#ifndef CAPTURE_H
#define CAPTURE_H

#include <vector>
#include "game/pieces/piece.h"

void capturePiece(Piece* movingPiece, int targetX, int targetY, std::vector<Piece*>& pieces);

#endif // CAPTURE_H
