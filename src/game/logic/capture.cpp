#include "capture.h"
#include "game/pieces/piece.h"
#include "config.h"
#include "log.h"
#include "gameplay.h"  // Include gameplay logging

extern Logger logger;
extern Logger gameplayLogger;

void capturePiece(Piece* movingPiece, int targetX, int targetY, std::vector<Piece*>& pieces) {
    // Find the enemy piece at the target position
    Piece* targetPiece = nullptr;
    for (auto& piece : pieces) {
        if (piece->getPosition().first == targetX && piece->getPosition().second == targetY) {
            targetPiece = piece;
            break;
        }
    }

    // Assume that targetPiece is a valid enemy piece because this function should only be called when a capture is legal
    if (targetPiece && targetPiece->getColor() != movingPiece->getColor()) {
        logger.log(LogLevel::INFO, "Capturing enemy piece with UID: " + std::to_string(targetPiece->getUID()));
        gameplayLogger.log(LogLevel::POSITION, "Piece with UID " + std::to_string(movingPiece->getUID()) + 
                           " (" + (movingPiece->getColor() == PieceColor::WHITE ? "White" : "Black") + 
                           ") captured piece with UID " + std::to_string(targetPiece->getUID()) + 
                           " (" + (targetPiece->getColor() == PieceColor::WHITE ? "White" : "Black") + 
                           ") at position (" + std::to_string(targetX) + ", " + std::to_string(targetY) + ").");

        // Perform the capture by moving the capturing piece to the captured piece's position
        targetPiece->destroyPiece(pieces);  // Remove the captured piece from the board
        movingPiece->setPosition(targetX, targetY);  // Move the capturing piece to the captured position

        // Log the successful capture and movement
        logger.log(LogLevel::INFO, "Moved piece with UID: " + std::to_string(movingPiece->getUID()) +
                                   " to position (" + std::to_string(targetX) + ", " + std::to_string(targetY) + ").");
    } else {
        // This should not happen if the function is called correctly
        logger.log(LogLevel::ERROR, "Capture failed: No valid enemy piece to capture at position (" + 
                                    std::to_string(targetX) + ", " + std::to_string(targetY) + ").");
    }
}
