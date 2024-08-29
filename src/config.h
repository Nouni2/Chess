#ifndef CONFIG_H
#define CONFIG_H

extern const char* VERTEX_SHADER_PATH;
extern const char* FRAGMENT_SHADER_PATH;

extern const bool USE_SHADOW;
extern const int RESOLUTION;

extern const char* BASE_TEXTURE_PATH;
extern const char* LIGHT_SQUARE_TEXTURE_PATH;
extern const char* DARK_SQUARE_TEXTURE_PATH;
extern const char* PIECE_TEXTURE_PATH;

extern const int PIECE_POSITION_X;
extern const int PIECE_POSITION_Y;

extern const int GRID_SIZE;

void logConfigValues();  // Declare the function to log configuration values

#endif // CONFIG_H
