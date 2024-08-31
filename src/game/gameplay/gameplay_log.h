#ifndef GAMEPLAY_LOG_H
#define GAMEPLAY_LOG_H

#include <string>
#include <vector>
#include "game/pieces/piece.h"
#include "log.h"  // Include the log header to use the Logger class

// Declare the gameplay logger instance
extern Logger gameplayLogger;

// Initialize the gameplay log files
void initializeLogs();

// Log the positions of all pieces
void logPiecePositions(const std::vector<Piece*>& pieces);

// Log a piece creation with its initial position
void logPieceCreation(const Piece* piece, const std::string& position);

// Log a move from one position to another
void logMove(const Piece* piece, const std::string& oldPosition, const std::string& newPosition);

// Function to get a piece type as a string
std::string getPieceTypeName(const Piece* piece);

#endif // GAMEPLAY_LOG_H
