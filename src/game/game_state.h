#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <memory>
#include <utility>
#include "game/pieces/piece.h"

struct GameState {
    std::vector<std::unique_ptr<Piece>> pieces;

    // Captured pieces (non-owning pointers into the pieces vector)
    std::vector<Piece*> capturedWhite;
    std::vector<Piece*> capturedBlack;

    // Turn tracking
    bool isWhiteTurn = true;

    // Selection state
    Piece* selectedPiece = nullptr;
    std::string selectedPieceOldPosition;
    std::vector<std::pair<int, int>> legalMoves;

    // Last move tracking
    struct LastMove {
        int startX = -1;
        int startY = -1;
        int endX = -1;
        int endY = -1;
        Piece* piece = nullptr;
        bool wasDoubleStep = false;
    } lastMove;
};

#endif // GAME_STATE_H
