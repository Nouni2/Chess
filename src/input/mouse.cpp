#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"
#include "game/pieces/piece.h"
#include "game/game_state.h"
#include "game/gameplay/gameplay_log.h"
#include "game/logic/logic.h"
#include "game/pieces/pawn.h"
#include "memory.h"  // Include memory for storing moves
#include <iostream>
#include <vector>
#include <algorithm>

extern Logger logger;
extern GameState gameState;
extern Memory gameMemory;

// Function to find a piece at a given position
Piece* findPieceAtPosition(int col, int row, const std::vector<std::unique_ptr<Piece>>& pieces) {
    for (auto& piece : pieces) {
        auto [pieceCol, pieceRow] = piece->getPosition();
        if (pieceCol == col && pieceRow == row) {
            return piece.get();
        }
    }
    return nullptr;
}

// Callback function to handle mouse button events
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        float squareSize = windowWidth < windowHeight ? windowWidth / static_cast<float>(GRID_SIZE) : windowHeight / static_cast<float>(GRID_SIZE);
        float marginX = (windowWidth - GRID_SIZE * squareSize) / 2.0f;
        float marginY = (windowHeight - GRID_SIZE * squareSize) / 2.0f;

        if (xpos >= marginX && xpos <= marginX + GRID_SIZE * squareSize &&
            ypos >= marginY && ypos <= marginY + GRID_SIZE * squareSize) {

            int col = static_cast<int>((xpos - marginX) / squareSize);
            int row = static_cast<int>((ypos - marginY) / squareSize);

            if (gameState.selectedPiece == nullptr) {
                gameState.selectedPiece = findPieceAtPosition(col, row, gameState.pieces);
                if (gameState.selectedPiece && isTurnValid(gameState.selectedPiece->getColor())) {
                    gameState.selectedPieceOldPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    gameState.legalMoves = gameState.selectedPiece->getLegalMoves(col, row);

                    // Log selected piece info
                    std::string pieceColor = (gameState.selectedPiece->getColor() == PieceColor::WHITE) ? "White" : "Black";
                    logger.log(LogLevel::DEBUG, "Selected " + pieceColor + " " + getPieceTypeName(gameState.selectedPiece) + " with UID: " + std::to_string(gameState.selectedPiece->getUID()) +
                               " at position: " + gameState.selectedPieceOldPosition);
                    gameplayLogger.log(LogLevel::POSITION, "Selected " + pieceColor + " " + getPieceTypeName(gameState.selectedPiece) + " with UID: " + std::to_string(gameState.selectedPiece->getUID()) +
                                       " at position: " + gameState.selectedPieceOldPosition);
                }
            } else {
                // Check if the selected move is legal
                bool isLegalMove = std::find(gameState.legalMoves.begin(), gameState.legalMoves.end(), std::make_pair(col, row)) != gameState.legalMoves.end();

                if (isLegalMove) {
                    // Store the move in memory before moving the piece
                    std::string finalPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    gameMemory.addMove(gameMemory.getMoveHistory().size() / 2 + 1, gameState.selectedPiece->getUID(), isTurnValid(PieceColor::WHITE), gameState.selectedPieceOldPosition, finalPosition);

                    // Check for en passant capture
                    if (gameState.selectedPiece->getType() == PieceType::PAWN) {
                        if (abs(col - (gameState.selectedPieceOldPosition[0] - 'a')) == 1 && abs(row - (8 - (gameState.selectedPieceOldPosition[1] - '0'))) == 1) {
                            static_cast<Pawn*>(gameState.selectedPiece)->performEnPassant(col, row);
                        }
                    }

                    // Move the piece
                    movePiece(gameState.selectedPiece, col, row);
                }

                gameState.selectedPiece = nullptr;
                gameState.selectedPieceOldPosition.clear();
                gameState.legalMoves.clear();
            }
        }
    }
}

void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
