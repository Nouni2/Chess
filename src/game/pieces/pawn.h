#ifndef PAWN_H
#define PAWN_H

#include "game/pieces/piece.h"
#include "config.h"
#include "log.h"
#include "gameplay.h"  // Include for gameplay management
#include "game/logic/capture.h" // Include for capture logic
#include "mouse.h" // Include for findPieceAtPosition
#include "memory.h"  // Include for accessing the game memory
#include "game/logic/logic.h" // Include logic for turn management
#include "game/gameplay/gameplay_log.h" // Include for gameplay logging

extern Logger logger;
extern std::vector<Piece*> pieces;  // Extern declaration of the pieces vector
extern Logger gameplayLogger;  // Extern declaration of the gameplay logger
extern Memory gameMemory;  // Extern declaration of the game memory object

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

        // Forward move: Check if the move is within board limits and the path is not blocked
        if (isMovementLegal(x, y - direction, pieces) && !findPieceAtPosition(x, y - direction, pieces)) {
            moves.push_back({x, y - direction});
        }

        // Double forward move if on starting position
        if ((getColor() == PieceColor::WHITE && y == 6) || (getColor() == PieceColor::BLACK && y == 1)) {
            if (isMovementLegal(x, y - 2 * direction, pieces) && !findPieceAtPosition(x, y - direction, pieces) && !findPieceAtPosition(x, y - 2 * direction, pieces)) {
                moves.push_back({x, y - 2 * direction});
            }
        }

        // Capture moves
        if (isCapturePossible(x - 1, y - direction)) {
            moves.push_back({x - 1, y - direction});
        }
        if (isCapturePossible(x + 1, y - direction)) {
            moves.push_back({x + 1, y - direction});
        }

        // Handle en passant
        if (isEnPassantCapture(x, y, direction)) {
            if (findPieceAtPosition(x + 1, y, pieces)) {
                moves.push_back({x + 1, y - direction});
            } else if (findPieceAtPosition(x - 1, y, pieces)) {
                moves.push_back({x - 1, y - direction});
            }
        }

        logger.log(LogLevel::DEBUG, "Calculated legal moves for Pawn with UID: " + std::to_string(getUID()) +
                   ", Color: " + (getColor() == PieceColor::WHITE ? "White" : "Black") +
                   " from position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

        return moves;
    }

    // Perform en passant capture if applicable
    void performEnPassant(int x, int y) {
        int direction = (getColor() == PieceColor::WHITE) ? 1 : -1;
        Piece* targetPawn = findPieceAtPosition(x, y + direction, pieces);
        if (targetPawn && dynamic_cast<Pawn*>(targetPawn)) {
            targetPawn->setPosition(-1, -1);  // Remove the captured pawn from the board
            logger.log(LogLevel::INFO, "En passant: Captured pawn with UID: " + std::to_string(targetPawn->getUID()));
            gameplayLogger.log(LogLevel::POSITION, "En passant capture performed by pawn with UID: " + std::to_string(getUID()) +
                               " at position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

            // Update the capturing pawn's position to reflect the en passant move
            setPosition(x, y);

            // Switch turn after performing en passant
            switchTurn();  // This is a function in the game logic that switches the turn
        }
    }

    // Make isEnPassantCapture public so it can be accessed outside the class
    bool isEnPassantCapture(int x, int y, int direction) const {
        if ((getColor() == PieceColor::WHITE && y == 3) || (getColor() == PieceColor::BLACK && y == 4)) {
            Piece* leftPawn = findPieceAtPosition(x - 1, y, pieces);
            Piece* rightPawn = findPieceAtPosition(x + 1, y, pieces);

            auto lastMove = gameMemory.getLastMove();

            // For White Pawns
            if (getColor() == PieceColor::WHITE) {
                if (leftPawn && dynamic_cast<Pawn*>(leftPawn) && leftPawn->getColor() == PieceColor::BLACK) {
                    if (lastMove.pieceUID == leftPawn->getUID() &&
                        lastMove.initialLocation[1] == '7' &&
                        lastMove.finalLocation[1] == '5') {
                        return true;
                    }
                }

                if (rightPawn && dynamic_cast<Pawn*>(rightPawn) && rightPawn->getColor() == PieceColor::BLACK) {
                    if (lastMove.pieceUID == rightPawn->getUID() &&
                        lastMove.initialLocation[1] == '7' &&
                        lastMove.finalLocation[1] == '5') {
                        return true;
                    }
                }
            }

            // For Black Pawns
            if (getColor() == PieceColor::BLACK) {
                if (leftPawn && dynamic_cast<Pawn*>(leftPawn) && leftPawn->getColor() == PieceColor::WHITE) {
                    if (lastMove.pieceUID == leftPawn->getUID() &&
                        lastMove.initialLocation[1] == '2' &&
                        lastMove.finalLocation[1] == '4') {
                        return true;
                    }
                }

                if (rightPawn && dynamic_cast<Pawn*>(rightPawn) && rightPawn->getColor() == PieceColor::WHITE) {
                    if (lastMove.pieceUID == rightPawn->getUID() &&
                        lastMove.initialLocation[1] == '2' &&
                        lastMove.finalLocation[1] == '4') {
                        return true;
                    }
                }
            }
        }

        return false;
    }

private:
    static std::string generateTexturePath(PieceColor color) {
        // Generate the correct texture path based on the piece color
        std::string colorPrefix = (color == PieceColor::WHITE) ? "w_" : "b_";
        std::string texturePath = "assets/" + shadowFolder + "/" + resolutionFolder + "/" + colorPrefix + "pawn.png";
        logger.log(LogLevel::INFO, "Generated texture path for Pawn: " + texturePath);
        return texturePath;
    }

    bool isCapturePossible(int targetX, int targetY) const {
        Piece* targetPiece = findPieceAtPosition(targetX, targetY, pieces);
        return targetPiece && targetPiece->getColor() != getColor();
    }
};

#endif // PAWN_H
