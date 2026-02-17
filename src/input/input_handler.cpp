#include "input_handler.h"
#include "renderer.h" // Include to access the resizeRenderer function
#include <GLFW/glfw3.h>
#include "log.h"      // Include for logging
#include <iostream>   // Include for console output

extern Logger logger;  // Use the global logger

// Initialize the parameters
float boardScale = 0.08f; // Scaling factor
float translateCorrectionX = 7.4f;    // X translation correction factor
float translateCorrectionY = 7.2f;    // Y translation correction factor
bool enableInput = false; // Boolean to enable/disable input handling

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Check if input is enabled
    if (!enableInput) return;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Log the key press
        logger.log(LogLevel::INFO, "Key pressed: " + std::to_string(key));

        switch (key) {
            case GLFW_KEY_MINUS:
                boardScale -= 0.0001f;
                logger.log(LogLevel::DEBUG, "Decreased boardScale (Scaling Factor) to " + std::to_string(boardScale));
                break;
            case GLFW_KEY_EQUAL:
                boardScale += 0.0001f;
                logger.log(LogLevel::DEBUG, "Increased boardScale (Scaling Factor) to " + std::to_string(boardScale));
                break;
            case GLFW_KEY_UP:
                translateCorrectionY += 0.1f;
                logger.log(LogLevel::DEBUG, "Increased translateCorrectionY (Y Translation Correction) to " + std::to_string(translateCorrectionY));
                break;
            case GLFW_KEY_DOWN:
                translateCorrectionY -= 0.1f;
                logger.log(LogLevel::DEBUG, "Decreased translateCorrectionY (Y Translation Correction) to " + std::to_string(translateCorrectionY));
                break;
            case GLFW_KEY_LEFT:
                translateCorrectionX -= 0.1f;
                logger.log(LogLevel::DEBUG, "Decreased translateCorrectionX (X Translation Correction) to " + std::to_string(translateCorrectionX));
                break;
            case GLFW_KEY_RIGHT:
                translateCorrectionX += 0.1f;
                logger.log(LogLevel::DEBUG, "Increased translateCorrectionX (X Translation Correction) to " + std::to_string(translateCorrectionX));
                break;
            case GLFW_KEY_ENTER:
                // Log the current parameter values to the log file
                logger.log(LogLevel::INFO, "Current parameter values:");
                logger.log(LogLevel::INFO, "boardScale (Scaling Factor): " + std::to_string(boardScale));
                logger.log(LogLevel::INFO, "translateCorrectionX (X Translation Correction): " + std::to_string(translateCorrectionX));
                logger.log(LogLevel::INFO, "translateCorrectionY (Y Translation Correction): " + std::to_string(translateCorrectionY));

                // Print the current parameter values to the console
                std::cout << "Current parameter values:\n";
                std::cout << "boardScale (Scaling Factor): " << boardScale << "\n";
                std::cout << "translateCorrectionX (X Translation Correction): " << translateCorrectionX << "\n";
                std::cout << "translateCorrectionY (Y Translation Correction): " << translateCorrectionY << "\n";
                logger.log(LogLevel::INFO, "Current parameter values printed to console.");
                break;
            default:
                break;
        }

        // Recalculate the projection matrix with updated parameters
        int windowWidth, windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        unsigned int shaderProgram = *(unsigned int*)glfwGetWindowUserPointer(window);
        resizeRenderer(shaderProgram, windowWidth, windowHeight);

        logger.log(LogLevel::INFO, "Projection matrix recalculated with updated parameters.");
    }
}
