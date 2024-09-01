#include "draw.h"
#include <GL/glew.h>
#include "config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm> // Required for std::find_if
#include "log.h"
#include "game/pieces/piece.h"
#include "mouse.h"  // Include the mouse.h for interaction with mouse events

extern Logger logger;

void drawChessboard(unsigned int shaderProgram, unsigned int boardTextures[2], const std::vector<std::pair<int, int>>& legalMoves) {
    static bool firstCall = true;
    static unsigned int VAO, VBO, EBO;

    if (firstCall) {
        logger.log(LogLevel::TRACE, "drawChessboard function called for the first time.");
        firstCall = false;

        float squareSize = 1.0f / GRID_SIZE;
        float halfSquareSize = squareSize / 2.0f;

        float squareVertices[] = {
            -halfSquareSize, -halfSquareSize, 0.0f, 0.0f, 0.0f,
             halfSquareSize, -halfSquareSize, 0.0f, 1.0f, 0.0f,
             halfSquareSize,  halfSquareSize, 0.0f, 1.0f, 1.0f,
            -halfSquareSize,  halfSquareSize, 0.0f, 0.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

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

        for (int i = 0; i < 2; i++) {
            glBindTexture(GL_TEXTURE_2D, boardTextures[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glBindVertexArray(0);
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int textureIndex = (i + j) % 2;
            glBindTexture(GL_TEXTURE_2D, boardTextures[textureIndex]);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            // Apply horizontal mirroring directly in the offset calculation
            float x = (GRID_SIZE - 1 - j) * (1.0f / GRID_SIZE) - 0.5f;
            float y = i * (1.0f / GRID_SIZE) - 0.5f;

            glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);

            // Highlight legal moves only if showLegalMoves is true
            bool isHighlighted = false;
            if (showLegalMoves) {
                auto it = std::find_if(legalMoves.begin(), legalMoves.end(), [&](const std::pair<int, int>& move) {
                    return move.first == j && move.second == i;
                });
                isHighlighted = it != legalMoves.end();
            }

            glUniform1i(glGetUniformLocation(shaderProgram, "highlight"), isHighlighted ? 1 : 0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }

    glBindVertexArray(0);
}

void drawPiece(unsigned int shaderProgram, const Piece& piece) {
    static bool firstCall = true;
    if (firstCall) {
        logger.log(LogLevel::TRACE, "drawPiece function called for the first time.");
        firstCall = false;
    }

    std::pair<int, int> position = piece.getPosition();
    int col = GRID_SIZE - 1 - position.first;
    int row = position.second;

    float squareSize = 1.0f / GRID_SIZE;
    float halfSquareSize = squareSize / 2.0f;

    float scaleFactor = PIECE_SCALING_FACTOR;

    float squareVertices[] = {
        -halfSquareSize * scaleFactor, -halfSquareSize * scaleFactor, 0.0f, 0.0f, 0.0f,
         halfSquareSize * scaleFactor, -halfSquareSize * scaleFactor, 0.0f, 1.0f, 0.0f,
         halfSquareSize * scaleFactor,  halfSquareSize * scaleFactor, 0.0f, 1.0f, 1.0f,
        -halfSquareSize * scaleFactor,  halfSquareSize * scaleFactor, 0.0f, 0.0f, 1.0f,
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

    glBindTexture(GL_TEXTURE_2D, piece.getTexture());
    logger.log(LogLevel::FRAME, "Bound piece texture for drawing chess piece: " + std::to_string(piece.getTexture()));

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotation"), 1, GL_FALSE, &rotationMatrix[0][0]);
    logger.log(LogLevel::FRAME, "Set rotation matrix for chess piece.");

    // Adjust the offset to reflect the corrected piece position
    float x = col * squareSize - 0.5f;
    float y = row * squareSize - 0.5f;
    glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);
    logger.log(LogLevel::FRAME, std::string("Set uniform 'offset' for chess piece at position: (") + 
           std::to_string(col) + ", " + std::to_string(row) + ")");

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    logger.log(LogLevel::FRAME, "Drew chess piece at position: (" + std::to_string(col) + 
               ", " + std::to_string(row) + ")");

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    logger.log(LogLevel::FRAME, "Deleted VAO, VBO, and EBO after drawing the chess piece.");
}
