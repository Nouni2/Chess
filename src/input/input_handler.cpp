#include "input_handler.h"
#include "renderer.h" // Include to access the resizeRenderer function
#include <GLFW/glfw3.h>
#include "log.h"      // Include for logging
#include <iostream>   // Include for console output

extern Logger logger;  // Use the global logger

// Initialize the parameters
float param_1 = 0.08f; // Scaling factor
float param_2 = 7.4f;    // X translation correction factor
float param_3 = 7.2f;    // Y translation correction factor
bool enableInput = false; // Boolean to enable/disable input handling

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Check if input is enabled
    if (!enableInput) return;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Log the key press
        logger.log(LogLevel::INFO, "Key pressed: " + std::to_string(key));

        switch (key) {
            case GLFW_KEY_MINUS:
                param_1 -= 0.0001f;
                logger.log(LogLevel::DEBUG, "Decreased param_1 (Scaling Factor) to " + std::to_string(param_1));
                break;
            case GLFW_KEY_EQUAL:
                param_1 += 0.0001f;
                logger.log(LogLevel::DEBUG, "Increased param_1 (Scaling Factor) to " + std::to_string(param_1));
                break;
            case GLFW_KEY_UP:
                param_3 += 0.1f;
                logger.log(LogLevel::DEBUG, "Increased param_3 (Y Translation Correction) to " + std::to_string(param_3));
                break;
            case GLFW_KEY_DOWN:
                param_3 -= 0.1f;
                logger.log(LogLevel::DEBUG, "Decreased param_3 (Y Translation Correction) to " + std::to_string(param_3));
                break;
            case GLFW_KEY_LEFT:
                param_2 -= 0.1f;
                logger.log(LogLevel::DEBUG, "Decreased param_2 (X Translation Correction) to " + std::to_string(param_2));
                break;
            case GLFW_KEY_RIGHT:
                param_2 += 0.1f;
                logger.log(LogLevel::DEBUG, "Increased param_2 (X Translation Correction) to " + std::to_string(param_2));
                break;
            case GLFW_KEY_ENTER:
                // Log the current parameter values to the log file
                logger.log(LogLevel::INFO, "Current parameter values:");
                logger.log(LogLevel::INFO, "param_1 (Scaling Factor): " + std::to_string(param_1));
                logger.log(LogLevel::INFO, "param_2 (X Translation Correction): " + std::to_string(param_2));
                logger.log(LogLevel::INFO, "param_3 (Y Translation Correction): " + std::to_string(param_3));

                // Print the current parameter values to the console
                std::cout << "Current parameter values:\n";
                std::cout << "param_1 (Scaling Factor): " << param_1 << "\n";
                std::cout << "param_2 (X Translation Correction): " << param_2 << "\n";
                std::cout << "param_3 (Y Translation Correction): " << param_3 << "\n";
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
