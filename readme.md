# OpenGL Chess

This project is a simple chess game rendered using OpenGL.

## Project Structure

- **main.cpp**: The main entry point of the application.
- **src/**: Contains the source files for the project.
  - **window.cpp**: Handles window creation.
  - **shader.cpp**: Manages shader compilation and linking.
  - **chessboard.cpp**: Contains the logic to render the chessboard.
  - **constants.h**: Defines color constants for the chessboard squares.
  
- **shaders/**: Contains the vertex and fragment shaders.

## Dependencies

- **GLEW**
- **GLFW**
- **OpenGL**

## Building the Project

To build the project, use the following command:

```bash
g++ -I./src main.cpp src/*.cpp -o chess_board -lGLEW -lglfw -lGL
```

## License

This project is currently under development.
```
