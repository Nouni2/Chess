#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "shaders.h"
#include "texture.h"
#include "chessboard.h"
#include "renderer.h"

// Window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    unsigned int shaderProgram = *(unsigned int*)glfwGetWindowUserPointer(window);
    resizeRenderer(shaderProgram, width, height);
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    // Calculate initial window size based on the grid size
    int initialWindowSize = GRID_SIZE * 100; // Assume each square is 100 pixels

    GLFWwindow* window = glfwCreateWindow(initialWindowSize, initialWindowSize, "Chessboard", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    unsigned int shaderProgram = loadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    glfwSetWindowUserPointer(window, &shaderProgram);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initializeRenderer(shaderProgram);

    unsigned int boardTextures[2];
    boardTextures[0] = loadTexture(LIGHT_SQUARE_TEXTURE_PATH);
    boardTextures[1] = loadTexture(DARK_SQUARE_TEXTURE_PATH);

    unsigned int pieceTexture = loadTexture(PIECE_TEXTURE_PATH);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the chessboard and the piece at the specified position
        drawChessboard(shaderProgram, boardTextures, pieceTexture);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
