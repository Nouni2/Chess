#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility> // for std::pair

enum class PieceColor { WHITE, BLACK };

class Piece {
public:
    Piece(PieceColor color, int score) : color(color), score(score) {}
    virtual ~Piece() = default;

    virtual std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const = 0;
    PieceColor getColor() const { return color; }
    int getScore() const { return score; }  // Getter for the score

protected:
    PieceColor color;
    int score;  // Score attribute for each piece
};

#endif // PIECE_H
