#ifndef KING_H
#define KING_H

#include "piece.h"
#include <limits>

class King : public Piece {
public:
    King(PieceColor color) : Piece(color, std::numeric_limits<int>::max()) {} // The King is invaluable

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        return {
            {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
            {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}
        };
    }
};

#endif // KING_H
