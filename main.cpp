#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "shaders.h"
#include "texture.h"
#include "chessboard.h"
#include "renderer.h"
#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    resizeRenderer(glGetUniformLocation(*(unsigned int*)glfwGetWindowUserPointer(window), "projection"), width, height);
    setViewport(window);
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = createWindow(800, 800, "Chessboard");
    if (!window) return -1;

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) return -1;

    unsigned int shaderProgram = loadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    glfwSetWindowUserPointer(window, &shaderProgram);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initializeRenderer(shaderProgram, window);

    unsigned int boardTextures[2];
    boardTextures[0] = loadTexture(LIGHT_SQUARE_TEXTURE_PATH);
    boardTextures[1] = loadTexture(DARK_SQUARE_TEXTURE_PATH);

    unsigned int pieceTexture = loadTexture(PIECE_TEXTURE_PATH);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawChessboard(shaderProgram, boardTextures, pieceTexture);

        updateWindow(window);
    }

    glfwTerminate();
    return 0;
}
