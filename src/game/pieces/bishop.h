#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(PieceColor color) : Piece(color, 3) {} // The Bishop is worth 3 points

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        for (int i = 1; i < 8; ++i) {
            moves.push_back({x + i, y + i});
            moves.push_back({x - i, y - i});
            moves.push_back({x + i, y - i});
            moves.push_back({x - i, y + i});
        }

        return moves;
    }
};

#endif // BISHOP_H
