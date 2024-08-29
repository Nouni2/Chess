#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>

void drawChessboard(unsigned int shaderProgram, unsigned int boardTextures[2]);
void drawPiece(unsigned int shaderProgram, unsigned int pieceTexture, const std::string& location);

#endif // CHESSBOARD_H
