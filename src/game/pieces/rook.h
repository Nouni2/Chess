#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(PieceColor color) : Piece(color, 5) {}  // The Rook is worth 5 points

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        for (int i = 1; i < 8; ++i) {
            moves.push_back({x + i, y});
            moves.push_back({x - i, y});
            moves.push_back({x, y + i});
            moves.push_back({x, y - i});
        }

        return moves;
    }
};

#endif // ROOK_H
