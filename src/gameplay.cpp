#include "gameplay.h"
#include "game/pieces/queen.h"
#include "draw.h"
#include "log.h"

extern Logger logger;

void setupPieces(std::vector<Piece*>& pieces) {
    logger.log(LogLevel::INFO, "Setting up pieces...");

    // Create and position the white queen
    Queen* whiteQueen = new Queen(PieceColor::WHITE);
    whiteQueen->setPosition("d1");
    pieces.push_back(whiteQueen);
    logger.log(LogLevel::INFO, "White queen placed at d1.");

    // Create and position the black queen
    Queen* blackQueen = new Queen(PieceColor::BLACK);
    blackQueen->setPosition("d8");
    pieces.push_back(blackQueen);
    logger.log(LogLevel::INFO, "Black queen placed at d8.");
}

void drawAllPieces(unsigned int shaderProgram, const std::vector<Piece*>& pieces) {
    for (const auto& piece : pieces) {
        drawPiece(shaderProgram, *piece);
    }
}
