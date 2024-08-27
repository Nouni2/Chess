#include "renderer.h"
#include "config.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void initializeRenderer(unsigned int shaderProgram) {
    // Create an initial orthographic projection matrix
    int windowWidth = 800, windowHeight = 800; // Initial window size
    resizeRenderer(shaderProgram, windowWidth, windowHeight);
}

void resizeRenderer(unsigned int shaderProgram, int windowWidth, int windowHeight) {
    // Determine aspect ratio
    float aspectRatio = static_cast<float>(windowWidth) / windowHeight;

    float orthoSize = GRID_SIZE / 2.0f;

    // Adjust the projection matrix to maintain aspect ratio
    glm::mat4 projection;
    if (aspectRatio >= 1.0f) {
        // Width is greater or equal to height
        projection = glm::ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio, -orthoSize, orthoSize, -1.0f, 1.0f);
    } else {
        // Height is greater than width
        projection = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspectRatio, orthoSize / aspectRatio, -1.0f, 1.0f);
    }

    glUseProgram(shaderProgram);
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
