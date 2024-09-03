#include "game/logic/logic.h"
#include "gameplay.h"
#include "log.h"
#include "mouse.h"
#include "config.h"  // Include to access showWhiteLegalMoves and showBlackLegalMoves
#include "sandbox.h"  // Include to respect sandbox settings
#include "game/logic/capture.h"
#include "game/pieces/pawn.h"

extern Logger logger;
extern Logger gameplayLogger;
extern std::vector<Piece*> pieces;

// Boolean to track the current turn: true for White, false for Black
bool isWhiteTurn = true;

void switchTurn() {
    if (!sandboxMode || !ignoreTurns) {
        isWhiteTurn = !isWhiteTurn;
    }
    std::string currentPlayer = isWhiteTurn ? "White" : "Black";

    // Update the visibility of legal moves based on the turn
    if (!sandboxMode) {
        if (isWhiteTurn) {
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
    return (isWhiteTurn && color == PieceColor::WHITE) || (!isWhiteTurn && color == PieceColor::BLACK);
}

void movePiece(Piece* piece, int x, int y) {
    if (piece && isTurnValid(piece->getColor())) {
        // Check if the move is legal or sandbox mode allows ignoring movement restrictions
        std::vector<std::pair<int, int>> legalMoves = piece->getLegalMoves(piece->getPosition().first, piece->getPosition().second);
        if (std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(x, y)) != legalMoves.end() || (sandboxMode && ignorePieceMovementRestrictions)) {

            // Handle en passant capture if a pawn is involved
            if (dynamic_cast<Pawn*>(piece)) {
                int direction = (piece->getColor() == PieceColor::WHITE) ? 1 : -1;
                Piece* potentialCapturePawn = findPieceAtPosition(x, y + direction, pieces);

                if (potentialCapturePawn && dynamic_cast<Pawn*>(potentialCapturePawn) && potentialCapturePawn->getColor() != piece->getColor()) {
                    if (dynamic_cast<Pawn*>(piece)->isEnPassantCapture(piece->getPosition().first, piece->getPosition().second, direction)) {
                        // Perform en passant capture
                        dynamic_cast<Pawn*>(piece)->performEnPassant(x, y);

                        // Move the pawn to the new position after capturing en passant
                        piece->setPosition(x, y);
                        logger.log(LogLevel::INFO, "En passant capture by piece with UID: " + std::to_string(piece->getUID()) +
                                                   " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
                        gameplayLogger.log(LogLevel::POSITION, "En passant capture: Piece UID " + std::to_string(piece->getUID()) +
                                                        " moved to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");

                        switchTurn();  // Switch the turn after a successful en passant capture
                        return;  // End the movePiece function to prevent further movement in the same turn
                    }
                }
            }

            // Check if the target square is occupied by an opponent's piece
            Piece* targetPiece = findPieceAtPosition(x, y, pieces);
            if (targetPiece && targetPiece->getColor() != piece->getColor()) {
                // Capture the opponent's piece
                capturePiece(piece, x, y, pieces);
            } else {
                // Move the piece to the new position
                piece->setPosition(x, y);
                logger.log(LogLevel::INFO, "Moved piece with UID: " + std::to_string(piece->getUID()) +
                                           " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
                gameplayLogger.log(LogLevel::POSITION, "Moved piece UID: " + std::to_string(piece->getUID()) +
                                                    " to position (" + std::to_string(x) + ", " + std::to_string(y) + ").");
            }

            // Update the last move
            lastMove.startX = piece->getPosition().first;
            lastMove.startY = piece->getPosition().second;
            lastMove.endX = x;
            lastMove.endY = y;
            lastMove.piece = piece;
            lastMove.wasDoubleStep = (dynamic_cast<Pawn*>(piece) != nullptr && abs(y - piece->getPosition().second) == 2);

            switchTurn();  // Switch the turn after a successful move or capture
        } else {
            logger.log(LogLevel::WARNING, "Invalid move attempt for piece with UID: " + std::to_string(piece->getUID()));
        }
    } else {
        std::string playerColor = piece->getColor() == PieceColor::WHITE ? "White" : "Black";
        logger.log(LogLevel::WARNING, playerColor + " tried to move during " + (isWhiteTurn ? "White" : "Black") + "'s turn.");
    }
}
