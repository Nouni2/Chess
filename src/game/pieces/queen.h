#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(PieceColor color) : Piece(color, 9) {} // The Queen is worth 9 points

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        for (int i = 1; i < 8; ++i) {
            moves.push_back({x + i, y});
            moves.push_back({x - i, y});
            moves.push_back({x, y + i});
            moves.push_back({x, y - i});
            moves.push_back({x + i, y + i});
            moves.push_back({x - i, y - i});
            moves.push_back({x + i, y - i});
            moves.push_back({x - i, y + i});
        }

        return moves;
    }
};

#endif // QUEEN_H
