#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"

extern Logger logger;

// Callback function to handle mouse button events
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Get the cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Get the window dimensions
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        // Calculate the size of each square based on the chessboard size and grid size
        float squareSize = windowWidth < windowHeight ? windowWidth / static_cast<float>(GRID_SIZE) : windowHeight / static_cast<float>(GRID_SIZE);

        // Calculate the margins (in case the chessboard is centered and there are black borders)
        float marginX = (windowWidth - GRID_SIZE * squareSize) / 2.0f;
        float marginY = (windowHeight - GRID_SIZE * squareSize) / 2.0f;

        // Check if the click is within the chessboard area
        if (xpos >= marginX && xpos <= marginX + GRID_SIZE * squareSize &&
            ypos >= marginY && ypos <= marginY + GRID_SIZE * squareSize) {

            // Calculate the grid position (row and column)
            int col = static_cast<int>((xpos - marginX) / squareSize);
            int row = static_cast<int>((ypos - marginY) / squareSize);

            // Convert row and column to chess notation (e.g., 'f3')
            char colChar = 'a' + col;
            int rowNumber = GRID_SIZE - row;

            std::string square = std::string(1, colChar) + std::to_string(rowNumber);

            // Log the square to the terminal and to the log file
            std::cout << "Left mouse button clicked on square " << square << std::endl;
            logger.log(LogLevel::DEBUG, "Left mouse button clicked on square " + square);
        } else {
            // Click was outside the chessboard area
            std::cout << "Click was outside the chessboard area." << std::endl;
            logger.log(LogLevel::DEBUG, "Left mouse button clicked outside the chessboard area.");
        }
    }
}

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
