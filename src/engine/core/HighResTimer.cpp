// MIT License, Copyright (c) 2019 Malik Allen

#include "HighResTimer.h"

#include <chrono>

namespace AuxEngine
{
	HighResTimer::HighResTimer() 
    {
    }

    AuxEngine::HighResTimer::~HighResTimer()
    {
    }

    unsigned int AuxEngine::HighResTimer::GetCurrentTimeInMicroSeconds()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto micros = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch();
        return static_cast<unsigned int>(micros.count());
    }

    unsigned int AuxEngine::HighResTimer::GetCurrentTimeInMilliSeconds()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto millis = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch();
        return static_cast<unsigned int>(millis.count());
    }
}