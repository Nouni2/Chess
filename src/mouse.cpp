#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"
#include "game/pieces/piece.h"  
#include "game/gameplay/gameplay_log.h"
#include "gameplay.h"
#include <iostream>
#include <vector>
#include <algorithm>

extern Logger logger;
extern std::vector<Piece*> pieces;

Piece* selectedPiece = nullptr;
std::string selectedPieceOldPosition;
std::vector<std::pair<int, int>> legalMoves;

// Function to find a piece at a given position
Piece* findPieceAtPosition(int col, int row) {
    for (auto& piece : pieces) {
        auto [pieceCol, pieceRow] = piece->getPosition();
        if (pieceCol == col && pieceRow == row) {
            return piece;
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

            if (selectedPiece == nullptr) {
                selectedPiece = findPieceAtPosition(col, row);
                if (selectedPiece) {
                    selectedPieceOldPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    legalMoves = selectedPiece->getLegalMoves(col, row);

                    // Log selected piece info
                    logger.log(LogLevel::DEBUG, "Selected " + getPieceTypeName(selectedPiece) + " with UID: " + std::to_string(selectedPiece->getUID()) +
                                                " at position: " + selectedPieceOldPosition);
                    gameplayLogger.log(LogLevel::POSITION, "Selected " + getPieceTypeName(selectedPiece) + " with UID: " + std::to_string(selectedPiece->getUID()) +
                                                    " at position: " + selectedPieceOldPosition);
                }
            } else {
                bool isLegalMove = std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(col, row)) != legalMoves.end();

                if (isLegalMove) {
                    std::string newPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    selectedPiece->setPosition(col, row);
                    logMove(selectedPiece, selectedPieceOldPosition, newPosition);
                }

                selectedPiece = nullptr;
                selectedPieceOldPosition.clear();
                legalMoves.clear();
            }
        }
    }
}

void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
