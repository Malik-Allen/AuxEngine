// MIT License, Copyright (c) 2025 Malik Allen

#include "EngineClock.h"

#include <chrono>

namespace AuxEngine
{
	EngineClock::EngineClock() 
        : prevTicks_(0)
        , currentTicks_(0)
        , fps_(30)
    {
        Reset();
    }

    unsigned int EngineClock::GetFPS() const
    {
        return fps_;
    }

    void EngineClock::SetFPS(unsigned int fps)
    {
        fps_ = fps;
    }

    void EngineClock::Reset()
    {
        prevTicks_ = currentTicks_ = GetCurrentTimeInMilliSeconds();
    }

    void EngineClock::UpdateFrameTicks()
    {
        prevTicks_ = currentTicks_;
        currentTicks_ = GetCurrentTimeInMilliSeconds();
    }

    float EngineClock::GetDeltaTime() const
    {
        return static_cast<float>(currentTicks_ - prevTicks_) * MILLISECONDS_TO_SECONDS;	// Conversion to seconds
    }
    unsigned int EngineClock::GetSleepTime(const unsigned int fps)
    {
        const unsigned int milliSecsPerFrame = SECONDS_TO_MILLISECONDS / fps;

        if (milliSecsPerFrame == 0)
        {
            return 0;
        }

        const unsigned int sleepTime = milliSecsPerFrame - GetCurrentTimeInMilliSeconds();

        if (sleepTime > milliSecsPerFrame)
        {
            return milliSecsPerFrame;
        }

        return sleepTime;
    }

    int EngineClock::GetCurrentTicks() const
    {
        return  currentTicks_;
    }

    unsigned int EngineClock::GetCurrentTimeInMicroSeconds()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto micros = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch();
        return static_cast<unsigned int>(micros.count());
    }

    unsigned int EngineClock::GetCurrentTimeInMilliSeconds()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto millis = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch();
        return static_cast<unsigned int>(millis.count());
    }
}