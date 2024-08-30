#include "piece.h"
#include "config.h"
#include "texture.h"
#include "log.h"

// Initialize the static member for tracking unique IDs
int Piece::nextUID = 1;

extern Logger logger;

Piece::Piece(PieceColor color, const std::string& texturePath, int score)
    : color(color), uid(nextUID++), position{-1, -1}, score(score) {
    // Load the texture for the piece
    texture = loadTexture(texturePath.c_str());
    logger.log(LogLevel::INFO, "Created piece with UID: " + std::to_string(uid) + ", Color: " + 
               (color == PieceColor::WHITE ? "White" : "Black") + 
               ", Texture Path: " + texturePath + ", Score: " + std::to_string(score));
}

std::pair<int, int> Piece::getPosition() const {
    logger.log(LogLevel::FRAME, "Retrieving position for piece with UID: " + std::to_string(uid) + 
                                " -> (" + std::to_string(position.first) + ", " + std::to_string(position.second) + ")");
    return position;
}

void Piece::setPosition(const std::string& pos) {
    if (pos.length() != 2 || pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
        position = {-1, -1}; // Invalid position, piece is off the board
        logger.log(LogLevel::WARNING, "Invalid position string: " + pos + ". Setting piece with UID: " + 
                   std::to_string(uid) + " to off the board.");
    } else {
        int col = pos[0] - 'a'; // Convert 'a' to 'h' into 0 to 7
        int row = 8 - (pos[1] - '1') - 1; // Convert '1' to '8' into 7 to 0
        position = {col, row};
        logger.log(LogLevel::INFO, "Set position for piece with UID: " + std::to_string(uid) + " to (" + 
                   std::to_string(col) + ", " + std::to_string(row) + ")");
    }
}

void Piece::setPosition(int x, int y) {
    position = {x, y};
    logger.log(LogLevel::INFO, "Set position for piece with UID: " + std::to_string(uid) + " to (" + 
               std::to_string(x) + ", " + std::to_string(y) + ")");
}

PieceColor Piece::getColor() const {
    return color;
}

int Piece::getUID() const {
    return uid;
}

int Piece::getScore() const {
    return score;
}

unsigned int Piece::getTexture() const {
    return texture;
}
