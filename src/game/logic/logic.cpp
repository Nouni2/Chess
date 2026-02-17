#include "game/logic/logic.h"
#include "game/game_state.h"
#include "log.h"
#include "mouse.h"
#include "config.h"
#include "sandbox.h"
#include "game/logic/capture.h"
#include "game/pieces/pawn.h"

extern Logger logger;
extern Logger gameplayLogger;
extern GameState gameState;

void switchTurn() {
    if (!sandboxMode || !ignoreTurns) {
        gameState.isWhiteTurn = !gameState.isWhiteTurn;
    }
    std::string currentPlayer = gameState.isWhiteTurn ? "White" : "Black";

    // Update the visibility of legal moves based on the turn
    if (!sandboxMode) {
        if (gameState.isWhiteTurn) {
            showWhiteLegalMoves = true;
            showBlackLegalMoves = false;
        } else {
            showWhiteLegalMoves = false;
            showBlackLegalMoves = true;
        }
    }

    logger.log(LogLevel::INFO, "Turn switched. It's now " + currentPlayer + "'s turn.");
}

bool isTurnValid(PieceColor color) {
    if (sandboxMode && ignoreTurns) {
        return true;
    }
    return (gameState.isWhiteTurn && color == PieceColor::WHITE) || (!gameState.isWhiteTurn && color == PieceColor::BLACK);
}

void movePiece(Piece* piece, int x, int y) {
    if (piece && isTurnValid(piece->getColor())) {
        // Check if the move is legal or sandbox mode allows ignoring movement restrictions
        std::vector<std::pair<int, int>> legalMoves = piece->getLegalMoves(piece->getPosition().first, piece->getPosition().second);
        if (std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(x, y)) != legalMoves.end() || (sandboxMode && ignorePieceMovementRestrictions)) {

            // Handle en passant capture if a pawn is involved
            if (piece->getType() == PieceType::PAWN) {
                int direction = (piece->getColor() == PieceColor::WHITE) ? 1 : -1;
                Piece* potentialCapturePawn = findPieceAtPosition(x, y + direction, gameState.pieces);

                if (potentialCapturePawn && potentialCapturePawn->getType() == PieceType::PAWN && potentialCapturePawn->getColor() != piece->getColor()) {
                    if (static_cast<Pawn*>(piece)->isEnPassantCapture(piece->getPosition().first, piece->getPosition().second, direction)) {
                        // Perform en passant capture
                        static_cast<Pawn*>(piece)->performEnPassant(x, y);

                        // Move the pawn to the new position after capturing en passant
                        piece->setPosition(x, y);
                        logger.log(LogLevel::INFO, "En passant capture by piece with UID: " + std::to_string(piece->getUID()) +
                                                   " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
                        gameplayLogger.log(LogLevel::POSITION, "En passant capture: Piece UID " + std::to_string(piece->getUID()) +
                                                        " moved to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

                        switchTurn();
                        return;
                    }
                }
            }

            // Check if the target square is occupied by an opponent's piece
            Piece* targetPiece = findPieceAtPosition(x, y, gameState.pieces);
            if (targetPiece && targetPiece->getColor() != piece->getColor()) {
                // Capture the opponent's piece
                capturePiece(piece, targetPiece);
            } else {
                // Move the piece to the new position
                piece->setPosition(x, y);
                logger.log(LogLevel::INFO, "Moved piece with UID: " + std::to_string(piece->getUID()) +
                                           " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
                gameplayLogger.log(LogLevel::POSITION, "Moved piece UID: " + std::to_string(piece->getUID()) +
                                                    " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
            }

            // Update the last move
            gameState.lastMove.startX = piece->getPosition().first;
            gameState.lastMove.startY = piece->getPosition().second;
            gameState.lastMove.endX = x;
            gameState.lastMove.endY = y;
            gameState.lastMove.piece = piece;
            gameState.lastMove.wasDoubleStep = (piece->getType() == PieceType::PAWN && abs(y - piece->getPosition().second) == 2);

            switchTurn();
        } else {
            logger.log(LogLevel::WARNING, "Invalid move attempt for piece with UID: " + std::to_string(piece->getUID()));
        }
    } else {
        std::string playerColor = piece->getColor() == PieceColor::WHITE ? "White" : "Black";
        logger.log(LogLevel::WARNING, playerColor + " tried to move during " + (gameState.isWhiteTurn ? "White" : "Black") + "'s turn.");
    }
}
