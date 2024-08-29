#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "config.h"

class Queen : public Piece {
public:
    Queen(PieceColor color) 
        : Piece(color, generateTexturePath(color)) {} // Initialize with the correct texture path

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        // Queen can move in any direction (straight and diagonal)
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

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        return "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "queen.png";
    }
};

#endif // QUEEN_H
