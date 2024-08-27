#include "config.h"

// Shader paths
const char* VERTEX_SHADER_PATH = "shaders/vertex_shader.glsl";
const char* FRAGMENT_SHADER_PATH = "shaders/fragment_shader.glsl";

// Define the resolution and whether shadows are used
const bool USE_SHADOW = true;  // True for shadowed pieces
const int RESOLUTION = 256;    // Use 256px resolution; change as needed

// Base path for textures
#if USE_SHADOW
const char* BASE_TEXTURE_PATH = "assets/With Shadow/";
#else
const char* BASE_TEXTURE_PATH = "assets/No shadow/";
#endif

// Construct full paths for textures
const char* LIGHT_SQUARE_TEXTURE_PATH = "assets/With Shadow/256px/square_gray_light.png";
const char* DARK_SQUARE_TEXTURE_PATH = "assets/With Shadow/256px/square_gray_dark.png";

// Texture path for the piece
const char* PIECE_TEXTURE_PATH = "assets/With Shadow/256px/w_queen.png";

// Piece placement
const int PIECE_POSITION_X = 4; // Column e (0-based index)
const int PIECE_POSITION_Y = 3; // Row 4 (0-based index)

// Chessboard grid size
const int GRID_SIZE = 8; // 8x8 chessboard
