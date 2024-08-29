#include <GLFW/glfw3.h>
#include "log.h"

extern Logger logger;

// Callback function to handle mouse button events
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Get the cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Log the mouse click and position to the terminal
        std::cout << "Left mouse button clicked at position (" << xpos << ", " << ypos << ")" << std::endl;

        // Log the mouse click and position to the log file with DEBUG severity
        logger.log(LogLevel::DEBUG, "Left mouse button clicked at position (" + std::to_string(xpos) + ", " + std::to_string(ypos) + ")");
    }
}

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
