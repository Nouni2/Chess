#include <GL/glew.h>
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.h"
#include "log.h" // Include the logger
#include "input_handler.h"

extern Logger logger;  // Use the global logger

void initializeRenderer(unsigned int shaderProgram, GLFWwindow* window) {
    logger.log(LogLevel::INFO, "Initializing renderer.");

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    resizeRenderer(shaderProgram, windowWidth, windowHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    logger.log(LogLevel::DEBUG, "Alpha blending enabled.");
}

void resizeRenderer(unsigned int shaderProgram, int windowWidth, int windowHeight) {
    logger.log(LogLevel::INFO, "Resizing renderer.");

    // Calculate the aspect ratio of the window
    float aspectRatio = static_cast<float>(windowWidth) / windowHeight;
    float orthoSize = GRID_SIZE / 2.0f;

    glm::mat4 projection;

    if (aspectRatio >= 1.0f) {
        // Window is wider than it is tall, adjust the width to maintain aspect ratio
        projection = glm::ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio, -orthoSize, orthoSize, -1.0f, 1.0f);
    } else {
        // Window is taller than it is wide, adjust the height to maintain aspect ratio
        projection = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio, -1.0f, 1.0f);
    }

    // Calculate the scaling factor to ensure the chessboard fits the window
    float scaleX = static_cast<float>(windowWidth) / GRID_SIZE;
    float scaleY = static_cast<float>(windowHeight) / GRID_SIZE;
    float scale = boardScale * std::min(scaleX, scaleY);  // Maintain aspect ratio by using the smaller scale factor

    // Apply the scaling matrix
    glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));

    // Calculate translation to center the chessboard
    float translateX = (windowWidth - (GRID_SIZE * scale)) / 2.0f;
    float translateY = (windowHeight - (GRID_SIZE * scale)) / 2.0f;

    // Normalize translation values to the [-1, 1] range expected by the orthographic projection
    translateX = translateX / (windowWidth / 2.0f);
    translateY = translateY / (windowHeight / 2.0f);

    // Apply the translation matrix to center the chessboard
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-translateX / translateCorrectionX, -translateY / translateCorrectionY, 0.0f));

    // Combine the translation, scaling, and projection matrices
    projection = translationMatrix * scalingMatrix * projection;

    // Set the projection matrix in the shader
    glUseProgram(shaderProgram);
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    logger.log(LogLevel::DEBUG, "Projection matrix set for shader program ID: " + std::to_string(shaderProgram));
}










void setViewport(GLFWwindow* window) {
    logger.log(LogLevel::INFO, "Setting viewport.");

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    logger.log(LogLevel::DEBUG, "Viewport set to: " + std::to_string(windowWidth) + "x" + std::to_string(windowHeight));
}

