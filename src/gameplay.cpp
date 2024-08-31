#include "gameplay.h"
#include "game/pieces/king.h"
#include "game/pieces/queen.h"
#include "game/pieces/bishop.h"
#include "game/pieces/knight.h"
#include "game/pieces/rook.h"
#include "game/pieces/pawn.h"
#include "draw.h"
#include "log.h"
#include "game/gameplay/gameplay_log.h"  // Include for logging positions

std::vector<Piece*> pieces;  // Define the global pieces vector

extern Logger logger;

void setupPieces(std::vector<Piece*>& pieces) {
    logger.log(LogLevel::INFO, "Setting up pieces...");

    // Setup white pieces
    pieces.push_back(new Rook(PieceColor::WHITE));    pieces.back()->setPosition("a1");
    pieces.push_back(new Knight(PieceColor::WHITE));  pieces.back()->setPosition("b1");
    pieces.push_back(new Bishop(PieceColor::WHITE));  pieces.back()->setPosition("c1");
    pieces.push_back(new Queen(PieceColor::WHITE));   pieces.back()->setPosition("d1");
    pieces.push_back(new King(PieceColor::WHITE));    pieces.back()->setPosition("e1");
    pieces.push_back(new Bishop(PieceColor::WHITE));  pieces.back()->setPosition("f1");
    pieces.push_back(new Knight(PieceColor::WHITE));  pieces.back()->setPosition("g1");
    pieces.push_back(new Rook(PieceColor::WHITE));    pieces.back()->setPosition("h1");

    for (char col = 'a'; col <= 'h'; ++col) {
        std::string position(1, col);
        position += '2';
        pieces.push_back(new Pawn(PieceColor::WHITE));
        pieces.back()->setPosition(position);
    }

    // Setup black pieces
    pieces.push_back(new Rook(PieceColor::BLACK));    pieces.back()->setPosition("a8");
    pieces.push_back(new Knight(PieceColor::BLACK));  pieces.back()->setPosition("b8");
    pieces.push_back(new Bishop(PieceColor::BLACK));  pieces.back()->setPosition("c8");
    pieces.push_back(new Queen(PieceColor::BLACK));   pieces.back()->setPosition("d8");
    pieces.push_back(new King(PieceColor::BLACK));    pieces.back()->setPosition("e8");
    pieces.push_back(new Bishop(PieceColor::BLACK));  pieces.back()->setPosition("f8");
    pieces.push_back(new Knight(PieceColor::BLACK));  pieces.back()->setPosition("g8");
    pieces.push_back(new Rook(PieceColor::BLACK));    pieces.back()->setPosition("h8");

    for (char col = 'a'; col <= 'h'; ++col) {
        std::string position(1, col);
        position += '7';
        pieces.push_back(new Pawn(PieceColor::BLACK));
        pieces.back()->setPosition(position);
    }

    logger.log(LogLevel::INFO, "All pieces placed on the board.");
    logPiecePositions(pieces);  // Log the initial positions of all pieces
}

void drawAllPieces(unsigned int shaderProgram, const std::vector<Piece*>& pieces) {
    for (const auto& piece : pieces) {
        drawPiece(shaderProgram, *piece);
    }
}
