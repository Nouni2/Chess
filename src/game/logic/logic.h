#ifndef LOGIC_H
#define LOGIC_H

#include "game/pieces/piece.h"
#include <vector>

// Function to switch turns
void switchTurn();

// Function to check if the turn is valid for the given piece color
bool isTurnValid(PieceColor color);

// Function to move a piece, considering turn and legality
void movePiece(Piece* piece, int x, int y);

#endif // LOGIC_H
