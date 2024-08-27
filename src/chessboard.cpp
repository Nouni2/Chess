#include "chessboard.h"
#include <GL/glew.h>
#include "config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void drawChessboard(unsigned int shaderProgram, unsigned int boardTextures[2], unsigned int pieceTexture) {
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

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            float x = j * squareSize - 0.5f; // Center the grid
            float y = i * squareSize - 0.5f; // Center the grid

            glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }

    // Draw the chess piece on the specified position
    glBindTexture(GL_TEXTURE_2D, pieceTexture);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotation"), 1, GL_FALSE, &rotationMatrix[0][0]);

    float x = PIECE_POSITION_X * squareSize - 0.5f;
    float y = PIECE_POSITION_Y * squareSize - 0.5f;
    glUniform3f(glGetUniformLocation(shaderProgram, "offset"), x, y, 0.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
