#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sound {
public:
    Sound();
    ~Sound();

    bool load(const std::string& filepath);
    void play() const;

private:
    Mix_Chunk* soundEffect;
};

#endif // SOUND_H
