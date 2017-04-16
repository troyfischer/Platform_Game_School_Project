#ifndef Music_hpp
#define Music_hpp

#include <stdio.h>
#include <string>
#include <SDL2_mixer/SDL_mixer.h>

class Music
{
    /* The class allows intuitive use of the SDL2 Mixer library */
private:
    Mix_Music *_music;
    Mix_Chunk *_sound;
public:
    /*-------------Constructor/Destructor------------------*/
    Music(std::string filePath);
    ~Music();
    
    void playMusic(); //plays music
    void pauseMusic(); //pauses music
    void endMusic(); //ends music
    void playSound(); //plays sound
};

#endif /* Music_hpp */
