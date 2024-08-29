#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "config.h"
#include "log.h"

extern Logger logger;

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

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Queen with UID: " + std::to_string(getUID()) + 
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
