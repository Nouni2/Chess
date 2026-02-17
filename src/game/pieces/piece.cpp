#include "piece.h"
#include "config.h"
#include "texture.h"
#include "log.h"
#include "mouse.h"
#include "sound.h"

// Initialize the static member for tracking unique IDs
int Piece::nextUID = 1;

extern Logger logger;

Piece::Piece(PieceColor color, PieceType type, const std::string& texturePath, int score)
    : color(color), type(type), uid(nextUID++), position{-1, -1}, score(score) {
    // Load the texture for the piece
    texture = loadTexture(texturePath);
    logger.log(LogLevel::INFO, "Created piece with UID: " + std::to_string(uid) + ", Color: " +
               (color == PieceColor::WHITE ? "White" : "Black") +
               ", Texture Path: " + texturePath + ", Score: " + std::to_string(score));
}

PieceType Piece::getType() const {
    return type;
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
    static Sound moveSound;
    static bool soundLoaded = false;

    if (!soundLoaded) {
        if (moveSound.load("assets/soundfx/move.wav")) {
            logger.log(LogLevel::INFO, "Move sound loaded successfully.");
        } else {
            logger.log(LogLevel::ERROR, "Failed to load move sound.");
        }
        soundLoaded = true;
    }

    position = {x, y};
    logger.log(LogLevel::INFO, "Set position for piece with UID: " + std::to_string(uid) + " to (" +
               std::to_string(x) + ", " + std::to_string(y) + ")");

    // Play the move sound
    moveSound.play();
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

// Method to check if the movement is legal
bool Piece::isMovementLegal(int x, int y, const std::vector<std::unique_ptr<Piece>>& pieces) const {

    // Check if the move is within the board boundaries
    bool isWithinBoard = x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
    if (!isWithinBoard) {
        return false;
    }

    bool isKnight = (type == PieceType::KNIGHT);
    bool isPawn = (type == PieceType::PAWN);

    if (isPawn) {
        // Determine the direction of movement
        int direction = (getColor() == PieceColor::WHITE) ? 1 : -1;

        // Check if the move is a forward move
        if (x == position.first) {
            // Forward move: check if the square is occupied
            Piece* occupyingPiece = findPieceAtPosition(x, y, pieces);
            if (occupyingPiece) {
                return false; // Path is blocked
            }
        } else if (abs(x - position.first) == 1 && y == position.second + direction) {
            // Diagonal move: check if the square is occupied by an opponent's piece
            Piece* occupyingPiece = findPieceAtPosition(x, y, pieces);
            if (!occupyingPiece || occupyingPiece->getColor() == this->getColor()) {
                return false; // Can't capture in this case
            }
        } else {
            // Invalid pawn move
            return false;
        }
    } else if (!isKnight) {
        // Determine the direction of movement for other pieces
        int dx = (x > position.first) ? 1 : (x < position.first) ? -1 : 0;
        int dy = (y > position.second) ? 1 : (y < position.second) ? -1 : 0;

        // Check all squares in the path between the current position and the destination
        int currentX = position.first + dx;
        int currentY = position.second + dy;
        while (currentX != x || currentY != y) {
            if (findPieceAtPosition(currentX, currentY, pieces)) {
                return false; // Path is blocked
            }
            currentX += dx;
            currentY += dy;
        }
    }

    // Check if the square is occupied
    Piece* occupyingPiece = findPieceAtPosition(x, y, pieces);

    // Check if the square is empty or occupied by an opponent's piece
    bool isSquareEmpty = (occupyingPiece == nullptr);
    bool isCaptureMove = false;

    if (!isSquareEmpty) {
        if (occupyingPiece->getColor() == this->getColor()) {
            // Square is occupied by a piece of the same color, so the move is illegal
            return false;
        } else {
            // Square is occupied by an opponent's piece, so it can be a capture move
            isCaptureMove = true;
        }
    }

    // Placeholder for checking if the move puts the king in check
    bool doesNotPutKingInCheck = true; // Will be implemented later
    return (isSquareEmpty || isCaptureMove) && doesNotPutKingInCheck;
}
