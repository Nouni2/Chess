#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    Knight(PieceColor color) : Piece(color, 3) {}  // The Knight is worth 3 points

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        return {
            {x + 2, y + 1}, {x + 2, y - 1},
            {x - 2, y + 1}, {x - 2, y - 1},
            {x + 1, y + 2}, {x + 1, y - 2},
            {x - 1, y + 2}, {x - 1, y - 2}
        };
    }
};

#endif // KNIGHT_H
