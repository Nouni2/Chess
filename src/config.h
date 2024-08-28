#ifndef CONFIG_H
#define CONFIG_H

extern const int RESOLUTION; 

// Shader paths
extern const char* VERTEX_SHADER_PATH;
extern const char* FRAGMENT_SHADER_PATH;

// Texture paths for the chessboard squares
extern const char* LIGHT_SQUARE_TEXTURE_PATH;
extern const char* DARK_SQUARE_TEXTURE_PATH;

// Texture path for the piece
extern const char* PIECE_TEXTURE_PATH;

// Piece placement
extern const int PIECE_POSITION_X;
extern const int PIECE_POSITION_Y;

// Chessboard grid size
extern const int GRID_SIZE;

#endif // CONFIG_H
