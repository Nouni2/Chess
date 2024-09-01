#include "config.h"
#include "log.h"



// Extern declaration of the logger
extern Logger logger;

// Shader paths
const char* VERTEX_SHADER_PATH = "shaders/vertex_shader.glsl";
const char* FRAGMENT_SHADER_PATH = "shaders/fragment_shader.glsl";

// Boolean to control the display of legal moves
bool showLegalMoves = true;

// Define the resolution and whether shadows are used
const bool USE_SHADOW = true;  // True for shadowed pieces
const int RESOLUTION = 512;    // Use 512px resolution; change as needed
const float PIECE_SCALING_FACTOR = 0.8f; // Adjust the scaling factor (1.0 is the standard size)

// Determine the shadow folder and resolution folder
const std::string shadowFolder = USE_SHADOW ? "With Shadow" : "No Shadow";
const std::string resolutionFolder = std::to_string(RESOLUTION) + "px";

// Construct full paths for textures
const std::string lightSquareTexture = "assets/" + shadowFolder + "/" + resolutionFolder + "/square_gray_light.png";
const std::string darkSquareTexture = "assets/" + shadowFolder + "/" + resolutionFolder + "/square_gray_dark.png";
const std::string pieceTexture = "assets/" + shadowFolder + "/" + resolutionFolder + "/w_queen.png";

// Convert these paths to const char*
const char* LIGHT_SQUARE_TEXTURE_PATH = lightSquareTexture.c_str();
const char* DARK_SQUARE_TEXTURE_PATH = darkSquareTexture.c_str();
const char* PIECE_TEXTURE_PATH = pieceTexture.c_str();

// Piece placement
const int PIECE_POSITION_X = 4; // Column e (0-based index)
const int PIECE_POSITION_Y = 3; // Row 4 (0-based index)

// Chessboard grid size
const int GRID_SIZE = 8; // 8x8 chessboard

void logConfigValues() {
    logger.log(LogLevel::DEBUG, "USE_SHADOW: " + std::string(USE_SHADOW ? "True" : "False"));
    logger.log(LogLevel::DEBUG, "RESOLUTION: " + std::to_string(RESOLUTION));
    logger.log(LogLevel::DEBUG, "PIECE_SCALING_FACTOR: " + std::to_string(PIECE_SCALING_FACTOR));

    logger.log(LogLevel::INFO, "Light Square Texture Path: " + lightSquareTexture);
    logger.log(LogLevel::INFO, "Dark Square Texture Path: " + darkSquareTexture);
    logger.log(LogLevel::INFO, "Piece Texture Path: " + pieceTexture);

    logger.log(LogLevel::INFO, "Piece Position: (" + std::to_string(PIECE_POSITION_X) + ", " + std::to_string(PIECE_POSITION_Y) + ")");
    logger.log(LogLevel::INFO, "Chessboard Grid Size: " + std::to_string(GRID_SIZE));
}
