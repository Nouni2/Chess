#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility> // for std::pair
#include <string>

enum class PieceColor { WHITE, BLACK };

class Piece {
public:
    Piece(PieceColor color, const std::string& texturePath, int score);
    virtual ~Piece() = default;

    virtual std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const = 0;

    PieceColor getColor() const;
    int getUID() const;
    int getScore() const; // New getter for the score
    std::pair<int, int> getPosition() const;
    void setPosition(const std::string& pos);
    void setPosition(int x, int y);

    unsigned int getTexture() const;

protected:
    static int nextUID; // Static member to keep track of UIDs
    int uid; // Unique ID for the piece
    PieceColor color;
    std::pair<int, int> position; // Current position on the board (-1,-1) if captured
    unsigned int texture; // OpenGL texture ID for the piece
    int score; // Score attribute for each piece
};

#endif // PIECE_H
