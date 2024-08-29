#include "chessboard.h"
#include <GL/glew.h>
#include "config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "log.h"  // Include the logger

extern Logger logger;  // Use the global logger

void drawChessboard(unsigned int shaderProgram, unsigned int boardTextures[2], unsigned int pieceTexture) {
    static bool firstCall = true;
    if (firstCall) {
        logger.log(LogLevel::TRACE, "drawChessboard function called for the first time.");
        firstCall = false;
    }

    // Adjust the size of each square to fit the grid size properly
    float squareSize = 1.0f / GRID_SIZE;
    float halfSquareSize = squareSize / 2.0f;

    float squareVertices[] = {
        // positions                      // texture coords
        -halfSquareSize, -halfSquareSize, 0.0f, 0.0f, 0.0f,
         halfSquareSize, -halfSquareSize, 0.0f, 1.0f, 0.0f,
         halfSquareSize,  halfSquareSize, 0.0f, 1.0f, 1.0f,
        -halfSquareSize,  halfSquareSize, 0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the chessboard (GRID_SIZE x GRID_SIZE grid)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int textureIndex = (i + j) % 2; // Alternate between light and dark squares
            glBindTexture(GL_TEXTURE_2D, boardTextures[textureIndex]);
            logger.log(LogLevel::FRAME, "Bound texture for square (" + std::to_string(i) + 
                       ", " + std::to_string(j) + "): " + std::to_string(boardTextures[textureIndex]));

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            float x = j * squareSize - 0.5f; // Center the grid
            float y = i * squareSize - 0.5f; // Center the grid

            glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);
            logger.log(LogLevel::FRAME, "Set uniform 'offset' for square (" + 
                       std::to_string(i) + ", " + std::to_string(j) + "): (" + 
                       std::to_string(x) + ", " + std::to_string(y) + ", 0.0)");

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            logger.log(LogLevel::FRAME, "Drew square (" + std::to_string(i) + 
                       ", " + std::to_string(j) + ") with texture: " + std::to_string(boardTextures[textureIndex]));
        }
    }

    // Draw the chess piece on the specified position
    glBindTexture(GL_TEXTURE_2D, pieceTexture);
    logger.log(LogLevel::FRAME, "Bound piece texture for drawing chess piece: " + std::to_string(pieceTexture));

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotation"), 1, GL_FALSE, &rotationMatrix[0][0]);
    logger.log(LogLevel::FRAME, "Set rotation matrix for chess piece.");

    float x = PIECE_POSITION_X * squareSize - 0.5f;
    float y = PIECE_POSITION_Y * squareSize - 0.5f;
    glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);
    logger.log(LogLevel::FRAME, "Set uniform 'offset' for chess piece at position: (" + 
               std::to_string(PIECE_POSITION_X) + ", " + std::to_string(PIECE_POSITION_Y) + ")");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    logger.log(LogLevel::FRAME, "Drew chess piece at position: (" + std::to_string(PIECE_POSITION_X) + 
               ", " + std::to_string(PIECE_POSITION_Y) + ")");

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    logger.log(LogLevel::FRAME, "Deleted VAO, VBO, and EBO after drawing.");
}
