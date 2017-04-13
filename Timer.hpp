#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Timer
{
private:
    bool _run;
    
    float _startTime;
    float _currentTime;
public:
    Timer();
    void startTimer();
    void runTimer();
    float getTimeElapsed();
    void stopTimer();
    void resetTimer();
    float getTimeBetweenFrames();
};

#endif /* Timer_hpp */
