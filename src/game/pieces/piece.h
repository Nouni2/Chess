#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility> // for std::pair
#include <string>
#include <algorithm>

enum class PieceColor { WHITE, BLACK };

class Piece {
public:
    Piece(PieceColor color, const std::string& texturePath, int score);
    virtual ~Piece() = default;

    virtual std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const = 0;

    PieceColor getColor() const;
    int getUID() const;
    int getScore() const;
    std::pair<int, int> getPosition() const;

    // Virtual method to set position, allowing overrides for specific piece behaviors like the pawn's double-step
    virtual void setPosition(int x, int y);

    void setPosition(const std::string& pos);
    unsigned int getTexture() const;

    void destroyPiece(const std::vector<Piece*>& pieces); // Method to handle piece destruction

    static std::vector<Piece*> capturedPiecesWhite; // White pieces captured by Black
    static std::vector<Piece*> capturedPiecesBlack; // Black pieces captured by White

protected:
    bool isMovementLegal(int x, int y, const std::vector<Piece*>& pieces) const;

    static int nextUID; // Static member to keep track of UIDs
    int uid; // Unique ID for the piece
    PieceColor color;
    std::pair<int, int> position; // Current position on the board (-1,-1) if captured
    unsigned int texture; // OpenGL texture ID for the piece
    int score; // Score attribute for each piece
};

#endif // PIECE_H
