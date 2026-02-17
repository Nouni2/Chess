#include "gameplay_log.h"
#include "log.h"
#include <fstream>
#include <iostream>
#include <string>

// Define the gameplay logger instance
Logger gameplayLogger("logs/gameplay.log");

void initializeLogs() {
    std::ofstream backendLogFile("logs/gameplay.log", std::ios::trunc);

    if (!backendLogFile) {
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to create the gameplay log file.");
        std::cerr << "Failed to create the gameplay log file." << std::endl;
        return;
    }

    // Log the initialization message
    backendLogFile << "Gameplay Position Log Initialized\n";
    backendLogFile.close();

    gameplayLogger.log(LogLevel::INFO, "Gameplay log initialized.");
}

// Function to get a piece type as a string
std::string getPieceTypeName(const Piece* piece) {
    switch (piece->getType()) {
        case PieceType::KING:   return "King";
        case PieceType::QUEEN:  return "Queen";
        case PieceType::BISHOP: return "Bishop";
        case PieceType::KNIGHT: return "Knight";
        case PieceType::ROOK:   return "Rook";
        case PieceType::PAWN:   return "Pawn";
    }
    return "UnknownPiece";
}

// Function to log the creation and initial position of a piece
void logPieceCreation(const Piece* piece, const std::string& position) {
    std::string pieceType = getPieceTypeName(piece);
    std::string pieceColor = (piece->getColor() == PieceColor::WHITE) ? "White" : "Black";
    int pieceUID = piece->getUID();

    // Log using the POSITION log level
    gameplayLogger.log(LogLevel::POSITION, pieceColor + " " + pieceType + " with UID " + std::to_string(pieceUID) + " created at " + position);
}

// Function to log a move
void logMove(const Piece* piece, const std::string& oldPosition, const std::string& newPosition) {
    std::string pieceType = getPieceTypeName(piece);
    std::string pieceColor = (piece->getColor() == PieceColor::WHITE) ? "White" : "Black";
    int pieceUID = piece->getUID();

    // Log using the POSITION log level
    gameplayLogger.log(LogLevel::POSITION, pieceColor + " " + pieceType + " with UID " + std::to_string(pieceUID) + " moved from " + oldPosition + " to " + newPosition);
}

// Function to log the initial positions of all pieces after setup
void logPiecePositions(const std::vector<std::unique_ptr<Piece>>& pieces) {
    for (const auto& piece : pieces) {
        auto [col, row] = piece->getPosition();
        if (col != -1 && row != -1) { // Valid position
            char colChar = 'a' + col;
            int rowNumber = 8 - row;
            std::string position = std::string(1, colChar) + std::to_string(rowNumber);

            // Log the creation and initial position of each piece
            logPieceCreation(piece.get(), position);
        }
    }
    gameplayLogger.log(LogLevel::INFO, "Initial piece positions logged.");
}
