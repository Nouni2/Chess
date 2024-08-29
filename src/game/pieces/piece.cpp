#include "piece.h"
#include "config.h"
#include "texture.h"

// Initialize the static member for tracking unique IDs
int Piece::nextUID = 1;

Piece::Piece(PieceColor color, const std::string& texturePath)
    : color(color), uid(nextUID++), position{-1, -1} {
    // Load the texture for the piece
    texture = loadTexture(texturePath.c_str());
}

std::pair<int, int> Piece::getPosition() const {
    return position;
}

void Piece::setPosition(const std::string& pos) {
    if (pos.length() != 2 || pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
        position = {-1, -1}; // Invalid position, piece is off the board
    } else {
        int col = 7 - (pos[0] - 'a'); // Convert 'a' to 'h' into 0 to 7
        int row = 7 - (pos[1] - '1'); // Convert '1' to '8' into 7 to 0
        position = {col, row};
    }
}

void Piece::setPosition(int x, int y) {
    position = {x, y};
}

PieceColor Piece::getColor() const {
    return color;
}

int Piece::getUID() const {
    return uid;
}

unsigned int Piece::getTexture() const {
    return texture;
}
