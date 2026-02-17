#include "gameplay.h"
#include "game/pieces/king.h"
#include "game/pieces/queen.h"
#include "game/pieces/bishop.h"
#include "game/pieces/knight.h"
#include "game/pieces/rook.h"
#include "game/pieces/pawn.h"
#include "draw.h"
#include "log.h"
#include "game/gameplay/gameplay_log.h"

extern Logger logger;

void setupPieces(std::vector<std::unique_ptr<Piece>>& pieces) {
    logger.log(LogLevel::INFO, "Setting up pieces...");

    // Setup white pieces
    pieces.push_back(std::make_unique<Rook>(PieceColor::WHITE));    pieces.back()->setPosition("a1");
    pieces.push_back(std::make_unique<Knight>(PieceColor::WHITE));  pieces.back()->setPosition("b1");
    pieces.push_back(std::make_unique<Bishop>(PieceColor::WHITE));  pieces.back()->setPosition("c1");
    pieces.push_back(std::make_unique<Queen>(PieceColor::WHITE));   pieces.back()->setPosition("d1");
    pieces.push_back(std::make_unique<King>(PieceColor::WHITE));    pieces.back()->setPosition("e1");
    pieces.push_back(std::make_unique<Bishop>(PieceColor::WHITE));  pieces.back()->setPosition("f1");
    pieces.push_back(std::make_unique<Knight>(PieceColor::WHITE));  pieces.back()->setPosition("g1");
    pieces.push_back(std::make_unique<Rook>(PieceColor::WHITE));    pieces.back()->setPosition("h1");

    for (char col = 'a'; col <= 'h'; ++col) {
        std::string position(1, col);
        position += '2';
        pieces.push_back(std::make_unique<Pawn>(PieceColor::WHITE));
        pieces.back()->setPosition(position);
    }

    // Setup black pieces
    pieces.push_back(std::make_unique<Rook>(PieceColor::BLACK));    pieces.back()->setPosition("a8");
    pieces.push_back(std::make_unique<Knight>(PieceColor::BLACK));  pieces.back()->setPosition("b8");
    pieces.push_back(std::make_unique<Bishop>(PieceColor::BLACK));  pieces.back()->setPosition("c8");
    pieces.push_back(std::make_unique<Queen>(PieceColor::BLACK));   pieces.back()->setPosition("d8");
    pieces.push_back(std::make_unique<King>(PieceColor::BLACK));    pieces.back()->setPosition("e8");
    pieces.push_back(std::make_unique<Bishop>(PieceColor::BLACK));  pieces.back()->setPosition("f8");
    pieces.push_back(std::make_unique<Knight>(PieceColor::BLACK));  pieces.back()->setPosition("g8");
    pieces.push_back(std::make_unique<Rook>(PieceColor::BLACK));    pieces.back()->setPosition("h8");

    for (char col = 'a'; col <= 'h'; ++col) {
        std::string position(1, col);
        position += '7';
        pieces.push_back(std::make_unique<Pawn>(PieceColor::BLACK));
        pieces.back()->setPosition(position);
    }

    logger.log(LogLevel::INFO, "All pieces placed on the board.");
}

void drawAllPieces(unsigned int shaderProgram, const std::vector<std::unique_ptr<Piece>>& pieces) {
    for (const auto& piece : pieces) {
        drawPiece(shaderProgram, *piece);
    }
}
