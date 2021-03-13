#ifndef __sound__h
#define __sound__h

#include "header.h"

class Sound {

public:
    Sound();


private:

    Mix_Music* bMusic;
    Mix_Chunk* samples[5];
};


#endif // __sound_h
