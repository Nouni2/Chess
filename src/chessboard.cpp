#include "constants.h"  // Include the constants header
#include "chessboard.h"
#include <GL/glew.h>
#include <vector>

void drawChessboard(GLuint program) {
    int boardSize = 8;
    float squareSize = 2.0f / boardSize;

    std::vector<float> vertices;

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            float x = -1.0f + col * squareSize;
            float y = -1.0f + row * squareSize;

            vertices.insert(vertices.end(), {
                x, y,
                x + squareSize, y,
                x + squareSize, y + squareSize,
                x, y + squareSize
            });
        }
    }

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(program);

    for (int i = 0; i < boardSize * boardSize; ++i) {
        int row = i / boardSize;
        int col = i % boardSize;

        if ((row + col) % 2 == 0) {
            glUniform3f(glGetUniformLocation(program, "squareColor"), WHITE_SQUARE_COLOR.r, WHITE_SQUARE_COLOR.g, WHITE_SQUARE_COLOR.b); // Use constant color
        } else {
            glUniform3f(glGetUniformLocation(program, "squareColor"), BLACK_SQUARE_COLOR.r, BLACK_SQUARE_COLOR.g, BLACK_SQUARE_COLOR.b); // Use constant color
        }

        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
