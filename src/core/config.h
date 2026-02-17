#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// Extern declarations for the shadow and resolution folder
extern const std::string shadowFolder;
extern const std::string resolutionFolder;

extern const int RESOLUTION;

extern bool showFPS;

// Shader paths
extern const std::string VERTEX_SHADER_PATH;
extern const std::string FRAGMENT_SHADER_PATH;

// Texture paths
extern const std::string LIGHT_SQUARE_TEXTURE_PATH;
extern const std::string DARK_SQUARE_TEXTURE_PATH;
extern const std::string PIECE_TEXTURE_PATH;

// Piece placement
extern const int PIECE_POSITION_X;
extern const int PIECE_POSITION_Y;

// Chessboard grid size
extern const int GRID_SIZE;

// Scaling factor for pieces
extern const float PIECE_SCALING_FACTOR;
extern const float CAPTURED_PIECE_SCALING_FACTOR;

// Booleans to control the display of legal moves for each player
extern bool showWhiteLegalMoves;
extern bool showBlackLegalMoves;


// Global sandbox mode control
extern bool sandboxMode;


// Function to log the configuration values
void logConfigValues();

#endif // CONFIG_H
