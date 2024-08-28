#include <GL/glew.h>
#include "renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.h"
#include <SOIL/SOIL.h>  // Ensure SOIL is included for texture loading

void initializeRenderer(unsigned int shaderProgram, GLFWwindow* window) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    resizeRenderer(shaderProgram, windowWidth, windowHeight);

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resizeRenderer(unsigned int shaderProgram, int windowWidth, int windowHeight) {
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
}

void setViewport(GLFWwindow* window) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
}
