#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "config.h"
#include "log.h"

extern Logger logger;

class Rook : public Piece {
public:
    Rook(PieceColor color)
        : Piece(color, generateTexturePath(color), 5) {  // The Rook is worth 5 points
        logger.log(LogLevel::INFO, "Rook created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black"));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        for (int i = 1; i < 8; ++i) {
            moves.push_back({x + i, y});
            moves.push_back({x - i, y});
            moves.push_back({x, y + i});
            moves.push_back({x, y - i});
        }

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Rook with UID: " + std::to_string(getUID()) +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "rook.png";
        logger.log(LogLevel::INFO, "Generated texture path for Rook: " + texturePath);
        return texturePath;
    }
};

#endif // ROOK_H
