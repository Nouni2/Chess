#include "config.h"
#include "log.h"

// Extern declaration of the logger
extern Logger logger;

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

void logConfigValues() {
    logger.log(LogLevel::DEBUG, "USE_SHADOW: " + std::string(USE_SHADOW ? "True" : "False"));
    logger.log(LogLevel::DEBUG, "RESOLUTION: " + std::to_string(RESOLUTION));

    logger.log(LogLevel::INFO, "Light Square Texture Path: " + std::string(LIGHT_SQUARE_TEXTURE_PATH));
    logger.log(LogLevel::INFO, "Dark Square Texture Path: " + std::string(DARK_SQUARE_TEXTURE_PATH));
    logger.log(LogLevel::INFO, "Piece Texture Path: " + std::string(PIECE_TEXTURE_PATH));

    logger.log(LogLevel::INFO, "Piece Position: (" + std::to_string(PIECE_POSITION_X) + ", " + std::to_string(PIECE_POSITION_Y) + ")");
    logger.log(LogLevel::INFO, "Chessboard Grid Size: " + std::to_string(GRID_SIZE));
}
