#include <GL/glew.h>
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.h"
#include "log.h" // Include the logger

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

    float aspectRatio = static_cast<float>(windowWidth) / windowHeight;
    float orthoSize = GRID_SIZE / 2.0f;

    glm::mat4 projection;
    if (aspectRatio >= 1.0f) {
        projection = glm::ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio, -orthoSize, orthoSize, -1.0f, 1.0f);
    } else {
        projection = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio, -1.0f, 1.0f);
    }

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
