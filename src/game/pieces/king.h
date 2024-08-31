#ifndef KING_H
#define KING_H

#include "piece.h"
#include "config.h"
#include "log.h"
#include <limits>
#include <algorithm>

extern Logger logger;
extern std::vector<Piece*> pieces;  // Extern declaration of the pieces vector

class King : public Piece {
public:
    King(PieceColor color)
        : Piece(color, generateTexturePath(color), std::numeric_limits<int>::max()) { // The King is invaluable
        logger.log(LogLevel::INFO, "King created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black"));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        auto moves = std::vector<std::pair<int, int>>{
            {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
            {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}
        };

        // Filter out illegal moves
        moves.erase(std::remove_if(moves.begin(), moves.end(),
            [&](const std::pair<int, int>& move) {
                return !isMovementLegal(move.first, move.second, pieces);
            }), moves.end());

        logger.log(LogLevel::DEBUG, "Calculated legal moves for King with UID: " + std::to_string(getUID()) +
                   ", Color: " + (getColor() == PieceColor::WHITE ? "White" : "Black") +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "king.png";
        logger.log(LogLevel::INFO, "Generated texture path for King: " + texturePath);
        return texturePath;
    }
};

#endif // KING_H
