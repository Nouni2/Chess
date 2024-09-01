#include "sound.h"
#include "log.h"  // Include the logger header
#include <iostream>

extern Logger logger;  // Use the existing logger instance

Sound::Sound() : soundEffect(nullptr) {
    // Initialize SDL2_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        logger.log(LogLevel::ERROR, "SDL_mixer could not initialize! Error: " + std::string(Mix_GetError()));
    } else {
        logger.log(LogLevel::INFO, "SDL_mixer initialized successfully.");
    }
}

Sound::~Sound() {
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
        logger.log(LogLevel::INFO, "Sound effect freed.");
    }
    Mix_Quit();
    logger.log(LogLevel::INFO, "SDL_mixer quit.");
}

bool Sound::load(const std::string& filepath) {
    soundEffect = Mix_LoadWAV(filepath.c_str());
    if (!soundEffect) {
        std::cerr << "Failed to load sound: " << filepath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        logger.log(LogLevel::ERROR, "Failed to load sound: " + filepath + " Error: " + std::string(Mix_GetError()));
        return false;
    }
    logger.log(LogLevel::INFO, "Sound loaded successfully: " + filepath);
    return true;
}

void Sound::play() const {
    if (soundEffect) {
        Mix_PlayChannel(-1, soundEffect, 0);
        logger.log(LogLevel::INFO, "Sound played.");
    } else {
        logger.log(LogLevel::WARNING, "Attempted to play a sound that wasn't loaded.");
    }
}
