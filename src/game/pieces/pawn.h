#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(PieceColor color) : Piece(color, 1) {}  // The Pawn is worth 1 point

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        int direction = (color == PieceColor::WHITE) ? 1 : -1;

        // Forward move
        moves.push_back({x, y + direction});

        // Double forward move if on starting position
        if ((color == PieceColor::WHITE && y == 1) || (color == PieceColor::BLACK && y == 6)) {
            moves.push_back({x, y + 2 * direction});
        }

        // Capture moves
        moves.push_back({x + 1, y + direction});
        moves.push_back({x - 1, y + direction});

        return moves;
    }
};

#endif // PAWN_H
