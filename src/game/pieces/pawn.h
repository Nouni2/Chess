#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "config.h"
#include "log.h"

extern Logger logger;
extern std::vector<Piece*> pieces;  // Extern declaration of the pieces vector

class Pawn : public Piece {
public:
    Pawn(PieceColor color)
        : Piece(color, generateTexturePath(color), 1) {  // The Pawn is worth 1 point
        logger.log(LogLevel::INFO, "Pawn created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black"));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        int direction = (getColor() == PieceColor::WHITE) ? 1 : -1;  // Positive for white (up), negative for black (down)

        // Forward move: Check if the move is within board limits
        if (isMovementLegal(x, y - direction, pieces)) {
            moves.push_back({x, y - direction});
        }

        // Double forward move if on starting position
        if ((getColor() == PieceColor::WHITE && y == 6) || (getColor() == PieceColor::BLACK && y == 1)) {
            if (isMovementLegal(x, y - 2 * direction, pieces)) {
                moves.push_back({x, y - 2 * direction});
            }
        }

        // Capture moves
        /*
        bool canCapture = false;  // This will be set by game logic later

        if (canCapture) {
            if (isMovementLegal(x + 1, y - direction, pieces)) {
                moves.push_back({x + 1, y - direction});
            }
            if (isMovementLegal(x - 1, y - direction, pieces)) {
                moves.push_back({x - 1, y - direction});
            }
        }
        */

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Pawn with UID: " + std::to_string(getUID()) +
                   ", Color: " + (getColor() == PieceColor::WHITE ? "White" : "Black") +
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
