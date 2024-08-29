#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// Extern declarations for the shadow and resolution folder
extern const std::string shadowFolder;
extern const std::string resolutionFolder;

// Shader paths
extern const char* VERTEX_SHADER_PATH;
extern const char* FRAGMENT_SHADER_PATH;

// Texture paths
extern const char* LIGHT_SQUARE_TEXTURE_PATH;
extern const char* DARK_SQUARE_TEXTURE_PATH;
extern const char* PIECE_TEXTURE_PATH;

// Piece placement
extern const int PIECE_POSITION_X;
extern const int PIECE_POSITION_Y;

// Chessboard grid size
extern const int GRID_SIZE;

// Scaling factor for pieces
extern const float PIECE_SCALING_FACTOR;

// Function to log the configuration values
void logConfigValues();

#endif // CONFIG_H
