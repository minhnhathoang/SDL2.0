#include "sound.h"

Sound::Sound() {
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    chunks.clear();
    chunks.resize(14);

    Mix_Volume(-1, 50);

    chunks[0] = Mix_LoadWAV("assets/sounds/rifle.wav");
    chunks[1] = Mix_LoadWAV("assets/sounds/laser.wav");
    chunks[2] = Mix_LoadWAV("assets/sounds/pistol.wav");
    chunks[3] = Mix_LoadWAV("assets/sounds/reload.wav");
    chunks[4] = Mix_LoadWAV("assets/sounds/minigun.wav");
    chunks[5] = Mix_LoadWAV("assets/sounds/m4a1.wav");
    chunks[6] = Mix_LoadWAV("assets/sounds/lgun.wav");
    chunks[7] = Mix_LoadWAV("assets/sounds/energy.wav");
    chunks[8] = Mix_LoadWAV("assets/sounds/explode.wav");
    chunks[9] = Mix_LoadWAV("assets/sounds/grenade.wav");
    chunks[10] = Mix_LoadWAV("assets/sounds/alert.wav");
    chunks[11] = Mix_LoadWAV("assets/sounds/bomb.wav");
    chunks[12] = Mix_LoadWAV("assets/sounds/ak47.wav");
    chunks[13] = Mix_LoadWAV("assets/sounds/pick.wav");

    cerr << Mix_GetError() << '\n';
}

void Sound::playMusic() {
    if (music == nullptr) {
        return;
    }
    Mix_PlayMusic(music, -1);
}

void Sound::playChunks(int id, int channel) {
    if (id >= chunks.size()) {
        logSDLError(".wav has been loaded");
    }
    for (int i = 1; i < 8; ++i) {
        if (Mix_Playing(i) == 0) {
            Mix_PlayChannel(i, chunks[id], 0);
            return;
        }
    }
    Mix_PlayChannel(randInt(1, 8), chunks[id], 0);
}

void Sound::release() {
    for (auto it = chunks.begin(); it != chunks.end(); ) {
        Mix_FreeChunk(*it);
        chunks.erase(it);
    }
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}
