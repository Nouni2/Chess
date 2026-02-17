#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "game/game_state.h"
#include "config.h"
#include "log.h"

extern Logger logger;
extern GameState gameState;

class Knight : public Piece {
public:
    Knight(PieceColor color)
        : Piece(color, PieceType::KNIGHT, generateTexturePath(color), 3) {  // The Knight is worth 3 points
        logger.log(LogLevel::INFO, "Knight created with UID: " + std::to_string(getUID()) +
                   ", Color: " + (color == PieceColor::WHITE ? "White" : "Black"));
    }

    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const override {
        auto moves = std::vector<std::pair<int, int>>{
            {x + 2, y + 1}, {x + 2, y - 1},
            {x - 2, y + 1}, {x - 2, y - 1},
            {x + 1, y + 2}, {x + 1, y - 2},
            {x - 1, y + 2}, {x - 1, y - 2}
        };

        // Filter out illegal moves
        moves.erase(std::remove_if(moves.begin(), moves.end(),
            [&](const std::pair<int, int>& move) {
                return !isMovementLegal(move.first, move.second, gameState.pieces);
            }), moves.end());

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Knight with UID: " + std::to_string(getUID()) +
                   " and color: " + (getColor() == PieceColor::WHITE ? "White" : "Black") +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "knight.png";
        logger.log(LogLevel::INFO, "Generated texture path for Knight: " + texturePath);
        return texturePath;
    }
};

#endif // KNIGHT_H
