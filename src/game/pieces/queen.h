#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "config.h"
#include "log.h"

extern Logger logger;
extern std::vector<Piece*> pieces;  // Extern declaration of the pieces vector

class Queen : public Piece {
public:
    Queen(PieceColor color)
        : Piece(color, generateTexturePath(color), 9) { // The queen is worth 9 points
        logger.log(LogLevel::INFO, "Queen created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black") +
                   ", Score: " + std::to_string(getScore()));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        std::vector<std::pair<int, int>> moves;

        for (int i = 1; i < GRID_SIZE; ++i) {
            if (isMovementLegal(x + i, y, pieces)) moves.push_back({x + i, y});
            if (isMovementLegal(x - i, y, pieces)) moves.push_back({x - i, y});
            if (isMovementLegal(x, y + i, pieces)) moves.push_back({x, y + i});
            if (isMovementLegal(x, y - i, pieces)) moves.push_back({x, y - i});
            if (isMovementLegal(x + i, y + i, pieces)) moves.push_back({x + i, y + i});
            if (isMovementLegal(x - i, y - i, pieces)) moves.push_back({x - i, y - i});
            if (isMovementLegal(x + i, y - i, pieces)) moves.push_back({x + i, y - i});
            if (isMovementLegal(x - i, y + i, pieces)) moves.push_back({x - i, y + i});
        }

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Queen with UID: " + std::to_string(getUID()) +
                   " and color: " + (getColor() == PieceColor::WHITE ? "White" : "Black") +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "queen.png";
        logger.log(LogLevel::INFO, "Generated texture path for Queen: " + texturePath);
        return texturePath;
    }
};

#endif // QUEEN_H
