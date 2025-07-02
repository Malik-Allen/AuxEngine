// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_HIGHRESTIMER_H
#define AUX_HIGHRESTIMER_H

#include <Windows.h>

#ifndef MILLISECONDS_TO_SECONDS
#define MILLISECONDS_TO_SECONDS (1 / 1000.0f)
#endif // !MILLISECONDS_TO_SECONDS

#ifndef SECONDS_TO_MILLISECONDS
#define SECONDS_TO_MILLISECONDS (1000 / 1)
#endif // !SECONDS_TO_MILLISECONDS

#ifndef MICROSECONDS_TO_SECONDS
#define MICROSECONDS_TO_SECONDS (1 / 1000000.0f)
#endif // !MICROSECONDS_TO_SECONDS

#ifndef SECONDS_TO_MICROSECONDS
#define SECONDS_TO_MICROSECONDS (1000000 / 1)
#endif // !SECONDS_TO_MICROSECONDS

#ifndef MILLISECONDS_TO_MICROSECONDS
#define MILLISECONDS_TO_MICROSECONDS (1000 / 1)
#endif // !MILLISECONDS_TO_MICROSECONDS

#ifndef MICROSECONDS_TO_MILLISECONDS
#define MICROSECONDS_TO_MILLISECONDS (1 / 1000.0f)
#endif // !MICROSECONDS_TO_MILLISECONDS

namespace  AuxEngine
{
    class HighResTimer
    {
    public:
        HighResTimer( const HighResTimer& ) = delete;
        HighResTimer& operator=( const HighResTimer& ) = delete;
        HighResTimer( HighResTimer&& ) = delete;
        HighResTimer& operator=( HighResTimer&& ) = delete;

        HighResTimer() :
            frequency_(),
            currentTicks_()
        {
            QueryPerformanceFrequency( &frequency_ );
            QueryPerformanceCounter( &currentTicks_ );
        }

        virtual ~HighResTimer() = default;

        unsigned int GetCurrentTimeInMicroSeconds()
        {
            QueryPerformanceCounter( &currentTicks_ );			        // Retrieves the current value of the performance counter 'Ticks'
            currentTicks_.QuadPart *= SECONDS_TO_MICROSECONDS;		// Conversion to microseconds to avoid a loss of percision when divinding by frequency
            currentTicks_.QuadPart /= frequency_.QuadPart;	        // Division by 'Ticks-per-second'

            return static_cast< unsigned int >( currentTicks_.QuadPart );
        }

        unsigned int GetCurrentTimeInMilliSeconds()
        {
            QueryPerformanceCounter( &currentTicks_ );
            currentTicks_.QuadPart *= SECONDS_TO_MILLISECONDS;
            currentTicks_.QuadPart /= frequency_.QuadPart;

            return static_cast< unsigned int >( currentTicks_.QuadPart );
        }

    private:
        LARGE_INTEGER frequency_;	// 'Ticks-per-second' 
        LARGE_INTEGER currentTicks_;

        //**IMPORTANT: LARGE_INTEGER is a union that has member value called 'QuadPart' which stores a 64bit signed int
        // 'QuadPart' should be used for a compiler with support for 64-bit integers, where as 'HighPart' and 'LowPart' should be used otherwise.
    };
}

#endif // !AUX_HIGHRESTIMER_H