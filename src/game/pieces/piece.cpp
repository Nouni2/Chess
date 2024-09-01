#include "piece.h"
#include "config.h"
#include "texture.h"
#include "log.h"
#include "mouse.h"
#include "sound.h"
#include "game/logic/logic.h"
#include "game/logic/capture.h" 
#include "game/gameplay/gameplay_log.h"
#include "sandbox.h"  // Include for sandbox mode logic


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
bool Piece::isMovementLegal(int x, int y, const std::vector<Piece*>& pieces) const {

    // Check if the move is within the board boundaries
    bool isWithinBoard = x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
    if (!isWithinBoard) {
        return false;
    }

    // Check if the piece is a knight
    std::string pieceType = typeid(*this).name();
    bool isKnight = pieceType.find("Knight") != std::string::npos;
    bool isPawn = pieceType.find("Pawn") != std::string::npos;

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


std::vector<Piece*> Piece::capturedPiecesWhite;
std::vector<Piece*> Piece::capturedPiecesBlack;

void Piece::destroyPiece(const std::vector<Piece*>& pieces) {
    for (auto& piece : pieces) {
        if (piece->getUID() == this->uid) {
            std::pair<int, int> position = piece->getPosition();

            // Move the piece off the board
            piece->setPosition(-1, -1);

            // Add the piece to the appropriate captured pieces vector
            if (piece->getColor() == PieceColor::WHITE) {
                capturedPiecesWhite.push_back(piece);
                logger.log(LogLevel::INFO, "White piece captured and added to Black's collection.");
            } else {
                capturedPiecesBlack.push_back(piece);
                logger.log(LogLevel::INFO, "Black piece captured and added to White's collection.");
            }

            gameplayLogger.log(LogLevel::POSITION, "Piece captured: UID " + std::to_string(uid) +
                                                 ", Color: " + (piece->getColor() == PieceColor::WHITE ? "White" : "Black") +
                                                 ", Position: (" + std::to_string(position.first) + ", " + std::to_string(position.second) + ")");

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
            break;
        }
    }
}