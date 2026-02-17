#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include <utility> // for std::pair
#include <string>
#include <algorithm>

enum class PieceColor { WHITE, BLACK };
enum class PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };

class Piece {
public:
    Piece(PieceColor color, PieceType type, const std::string& texturePath, int score);
    virtual ~Piece() = default;

    virtual std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const = 0;

    PieceType getType() const;
    PieceColor getColor() const;
    int getUID() const;
    int getScore() const;
    std::pair<int, int> getPosition() const;

    // Virtual method to set position, allowing overrides for specific piece behaviors like the pawn's double-step
    virtual void setPosition(int x, int y);

    void setPosition(const std::string& pos);
    unsigned int getTexture() const;

protected:
    bool isMovementLegal(int x, int y, const std::vector<std::unique_ptr<Piece>>& pieces) const;

    static int nextUID; // Static member to keep track of UIDs
    int uid; // Unique ID for the piece
    PieceColor color;
    PieceType type;
    std::pair<int, int> position; // Current position on the board (-1,-1) if captured
    unsigned int texture; // OpenGL texture ID for the piece
    int score; // Score attribute for each piece
};

#endif // PIECE_H
