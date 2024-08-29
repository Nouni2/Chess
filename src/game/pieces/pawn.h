#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "config.h"
#include "log.h"

extern Logger logger;

class Pawn : public Piece {
public:
    Pawn(PieceColor color)
        : Piece(color, generateTexturePath(color), 1) {  // The Pawn is worth 1 point
        logger.log(LogLevel::INFO, "Pawn created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black"));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        int direction = (getColor() == PieceColor::WHITE) ? 1 : -1;

        // Forward move
        moves.push_back({x, y + direction});

        // Double forward move if on starting position
        if ((getColor() == PieceColor::WHITE && y == 1) || (getColor() == PieceColor::BLACK && y == 6)) {
            moves.push_back({x, y + 2 * direction});
        }

        // Capture moves
        moves.push_back({x + 1, y + direction});
        moves.push_back({x - 1, y + direction});

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Pawn with UID: " + std::to_string(getUID()) +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "pawn.png";
        logger.log(LogLevel::INFO, "Generated texture path for Pawn: " + texturePath);
        return texturePath;
    }
};

#endif // PAWN_H
