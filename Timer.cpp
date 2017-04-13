
#include "Timer.hpp"

Timer::Timer()
{
    _run = false;
}

void Timer::startTimer()
{
    _run = true;
    _startTime = SDL_GetTicks();
}

void Timer::runTimer()
{
    if (_run)
    {
        _currentTime = SDL_GetTicks();
    }
}

float Timer::getTimeElapsed()
{
    return (_currentTime - _startTime) / 1000.0f;
}

void Timer::stopTimer()
{
    _run = false;
}

void Timer::resetTimer()
{
    _startTime = SDL_GetTicks();
}

float Timer::getTimeBetweenFrames()
{
    float previousTime = _currentTime;
    return (_currentTime - previousTime) / 1000.0f;
}
