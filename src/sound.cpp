#include "sound.h"

Sound::Sound() {
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    music = Mix_LoadMUS("assets/sounds/12am.mp3");

    chunks.clear();
    chunks.resize(100);

    Mix_Volume(-1, 20);

    chunks[0] = Mix_LoadWAV("assets/sounds/rifle.wav");
    chunks[1] = Mix_LoadWAV("assets/sounds/laser.wav");
    chunks[2] = Mix_LoadWAV("assets/sounds/pistol.wav");
    chunks[3] = Mix_LoadWAV("assets/sounds/reload.wav");
    chunks[4] = Mix_LoadWAV("assets/sounds/minigun.wav");
    chunks[5] = Mix_LoadWAV("assets/sounds/54_hp_dead.wav");
    chunks[6] = Mix_LoadWAV("assets/sounds/m4A1.wav");
    chunks[7] = Mix_LoadWAV("assets/sounds/58_wea_vehminigun.wav");
    chunks[8] = Mix_LoadWAV("assets/sounds/71_wea_rail_alt2.wav");
    chunks[9] = Mix_LoadWAV("assets/sounds/83_wea_lmg.wav");
    chunks[10] = Mix_LoadWAV("assets/sounds/dist_02.wav");
    chunks[11] = Mix_LoadWAV("assets/sounds/281_wea_ditzy_cs_ik.wav");
    chunks[12] = Mix_LoadWAV("assets/sounds/87_wea_glhf.wav");
    chunks[13] = Mix_LoadWAV("assets/sounds/66_wea_revolver5.wav");
    chunks[14] = Mix_LoadWAV("assets/sounds/89_wea_energy.wav");
    chunks[15] = Mix_LoadWAV("assets/sounds/262_explode2.wav");
    chunks[16] = Mix_LoadWAV("assets/sounds/62_wea_shotgun.wav");

    cerr << Mix_GetError() << '\n';
}

void Sound::playMusic() {
    Mix_PlayMusic(music, -1);
}

void Sound::playChunks(int id, int channel) {
    if (Mix_Playing(1) == 0) {
        //Mix_PlayChannel(channel, chunks[id], channel);
        Mix_PlayChannel(channel, chunks[id], 0);
    }
}

void Sound::release() {

}
