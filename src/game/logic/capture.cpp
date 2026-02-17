#include "capture.h"
#include "game/game_state.h"
#include "config.h"
#include "log.h"
#include "sound.h"
#include "game/gameplay/gameplay_log.h"

extern Logger logger;
extern Logger gameplayLogger;
extern GameState gameState;

void capturePiece(Piece* movingPiece, Piece* targetPiece) {
    if (targetPiece && targetPiece->getColor() != movingPiece->getColor()) {
        auto targetPos = targetPiece->getPosition();
        logger.log(LogLevel::INFO, "Capturing enemy piece with UID: " + std::to_string(targetPiece->getUID()));
        gameplayLogger.log(LogLevel::POSITION, "Piece with UID " + std::to_string(movingPiece->getUID()) +
                           " (" + (movingPiece->getColor() == PieceColor::WHITE ? "White" : "Black") +
                           ") captured piece with UID " + std::to_string(targetPiece->getUID()) +
                           " (" + (targetPiece->getColor() == PieceColor::WHITE ? "White" : "Black") +
                           ") at position (" + std::to_string(targetPos.first) + ", " + std::to_string(targetPos.second) + ").");

        // Move the captured piece off the board
        targetPiece->setPosition(-1, -1);

        // Add to appropriate captured list in GameState
        if (targetPiece->getColor() == PieceColor::WHITE) {
            gameState.capturedWhite.push_back(targetPiece);
            logger.log(LogLevel::INFO, "White piece captured and added to Black's collection.");
        } else {
            gameState.capturedBlack.push_back(targetPiece);
            logger.log(LogLevel::INFO, "Black piece captured and added to White's collection.");
        }

        // Move the capturing piece to the captured position
        movingPiece->setPosition(targetPos.first, targetPos.second);

        // Play capture sound
        static Sound captureSound;
        static bool captureSoundLoaded = false;
        if (!captureSoundLoaded) {
            if (captureSound.load("assets/soundfx/capture.wav")) {
                logger.log(LogLevel::INFO, "Capture sound loaded successfully.");
            } else {
                logger.log(LogLevel::ERROR, "Failed to load capture sound.");
            }
            captureSoundLoaded = true;
        }
        captureSound.play();

        logger.log(LogLevel::INFO, "Moved piece with UID: " + std::to_string(movingPiece->getUID()) +
                                   " to position (" + std::to_string(targetPos.first) + ", " + std::to_string(targetPos.second) + ").");
    } else {
        logger.log(LogLevel::ERROR, "Capture failed: No valid enemy piece to capture.");
    }
}
