# OpenGL Chess Game

This project is a chess game rendered using OpenGL, built to run on any system that supports OpenGL and C++. It features full gameplay, including legal move enforcement, check detection, and piece capturing, with graphical rendering and sound effects.

---

## Table of Contents

- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Building the Project](#building-the-project)
- [Running the Project](#running-the-project)
- [Project Features](#project-features)
- [Contributing](#contributing)
- [License](#license)

---

## Project Structure

The project is organized into the following directory structure:

```
├── assets/                      # Contains textures, sound effects, and other assets
│   ├── With Shadow/             # Chess pieces with shadow effects (available in multiple resolutions)
│   ├── No Shadow/               # Chess pieces without shadow effects (available in multiple resolutions)
│   └── soundfx/                 # Sound effects for moves, captures, and other game events
├── fonts/                       # Font files for rendering text
├── logs/                        # Log files for debugging and gameplay history
├── src/                         # Source files for game logic, rendering, and utilities
│   ├── game/                    # Core game logic and chess piece management
│   │   ├── logic/               # Move logic, turn management, capture system
│   │   │   ├── capture.cpp
│   │   │   ├── capture.h
│   │   │   ├── logic.cpp
│   │   │   ├── logic.h
│   │   └── pieces/              # Classes for individual chess pieces
│   │       ├── piece.cpp
│   │       ├── piece.h
│   │       ├── pawn.h
│   │       ├── king.h
│   │       ├── queen.h
│   │       ├── rook.h
│   │       ├── bishop.h
│   │       ├── knight.h
│   ├── renderer.cpp             # Rendering engine for the chessboard and pieces
│   ├── renderer.h               # Header for renderer functions
│   ├── sound.cpp                # Sound management (move, capture, etc.)
│   ├── viewer.cpp               # Viewing and camera logic for rendering perspective
│   ├── viewer.h                 # Header for viewer/camera functions
│   ├── shaders.cpp              # Shader management for OpenGL
│   ├── shaders.h                # Header for shader management
│   ├── stb_image.h              # Image loader for textures
│   ├── texture.cpp              # Texture loading and management
│   ├── texture.h                # Header for texture functions
│   ├── memory.cpp               # Memory management for move history and undo
│   ├── memory.h                 # Header for memory management
│   ├── log.cpp                  # Logging system for debugging and gameplay logs
│   ├── log.h                    # Header for log functions
│   ├── gameplay.cpp             # Main gameplay loop and logic
│   ├── gameplay.h               # Header for gameplay functions
│   ├── input_handler.cpp        # Input handling (mouse, keyboard) for gameplay interactions
│   ├── input_handler.h          # Header for input handling
│   ├── mouse.cpp                # Mouse input logic and piece selection
│   ├── draw.cpp                 # Drawing functions for rendering board and pieces
│   ├── draw.h                   # Header for drawing functions
│   ├── sound.h                  # Header for sound management
│   ├── window.cpp               # Window creation and management using GLFW
│   ├── window.h                 # Header for window functions
│   ├── config.cpp               # Game configuration and settings handling
│   ├── config.h                 # Header for configuration functions
├── main.cpp                     # Entry point of the chess game
├── .gitignore                   # Git ignore file for ignoring build outputs and IDE-specific files
└── README.md                    # Project documentation

```

---

## Dependencies

To build and run this project, the following libraries are required:

- **GLEW** - OpenGL Extension Wrangler Library
- **GLFW** - A library for handling windows and input
- **SOIL** - Simple OpenGL Image Library
- **FreeType** - For font rendering
- **SDL2** - Simple DirectMedia Layer for multimedia handling
- **SDL2_mixer** - SDL extension for audio effects
- **OpenGL** - Graphics API

### Install Dependencies

You can install the required libraries using the following command on a Linux-based system (or an equivalent package manager for your OS):

```bash
sudo apt update
sudo apt install libglew-dev libglfw3-dev libsoil-dev libfreetype6-dev libsdl2-dev libsdl2-mixer-dev
```

---

## Building the Project

To build and run this chess game, you can refer to [this OpenGL template](https://github.com/Nouni2/OpenGL-Linux-Template-Project.git), which provides a comprehensive setup for OpenGL projects. Follow the instructions in the template to configure your environment.

### Build Command

Ensure that the following build command is set in the `.vscode/tasks.json` file:

```json
{
    "label": "build chess",
    "type": "shell",
    "command": "g++ -I./src $(find ./src -name \"*.cpp\") main.cpp -o chess_board -lGLEW -lglfw -lGL -lSOIL -lfreetype -lSDL2 -lSDL2_mixer -std=c++17",
    "group": {
        "kind": "build",
        "isDefault": true
    },
    "problemMatcher": ["$gcc"],
    "detail": "Task for building the chess project"
}
```

This will compile all the source files inside the `src/` directory, link the required libraries, and generate the `chess_board` executable.

---

## Running the Project

Once built, the chess game can be run from the terminal using the following command:

```bash
./chess_board
```

Alternatively, if you're using Visual Studio Code, you can run it by pressing `F5` to start the game in debug mode.

---

## Project Features

### 1. Graphics
- **OpenGL Rendering**: The game board and pieces are rendered using OpenGL.
- **Multiple Resolutions**: Piece textures are provided in 128px, 256px, 512px, and 1024px sizes.
- **Shadow and No Shadow**: Two sets of textures are available, one with shadows and one without.

### 2. Sound Effects
- **Move Sound**: A sound is played when a piece is moved.
- **Capture Sound**: A distinct sound is played when a piece is captured.
- **Check Notification Sound**: Audio feedback is provided when a king is in check.
- **Promotion and Castling**: Special sounds for pawn promotion and castling.

### 3. Logging
- **Gameplay Logging**: All moves are logged in `logs/gameplay.log`.
- **Memory Logging**: Track the history of moves in `logs/memory.log`.
- **Debug Logging**: General debug information is logged in `logs/debug.log`.

---

## Contributing

Contributions to the project are welcome. To contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request, ensuring that your code follows the project's conventions and passes all tests.

