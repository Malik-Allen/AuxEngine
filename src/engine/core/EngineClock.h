// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_ENGINECLOCK_H
#define AUX_ENGINECLOCK_H

#include "HighResTimer.h"

namespace  AuxEngine
{
    class EngineClock : public HighResTimer
    {
    public:
        EngineClock( const EngineClock& ) = delete;
        EngineClock& operator=( const EngineClock& ) = delete;
        EngineClock( EngineClock&& ) = delete;
        EngineClock& operator=( EngineClock&& ) = delete;

        EngineClock() :
            HighResTimer(),
            prevTicks_( 0 ),
            currentTicks_( 0 ),
            fps_( 120 )
        {
            Reset();
        }

        ~EngineClock() override = default;

        unsigned int GetFPS() const { return fps_; }
        void SetFPS( unsigned int fps ) { fps_ = fps; }

        void Reset()
        {
            prevTicks_ = currentTicks_ = HighResTimer::GetCurrentTimeInMilliSeconds();
        }

        void UpdateFrameTicks()
        {
            prevTicks_ = currentTicks_;
            currentTicks_ = HighResTimer::GetCurrentTimeInMilliSeconds();
        }

        float GetDeltaTime() const
        {
            return static_cast< float >( currentTicks_ - prevTicks_ ) * MILLISECONDS_TO_SECONDS;	// Conversion to seconds
        }

        unsigned int GetSleepTime( const unsigned int fps )
        {
            const unsigned int milliSecsPerFrame = SECONDS_TO_MILLISECONDS / fps;

            if( milliSecsPerFrame == 0 )
            {
                return 0;
            }

            const unsigned int sleepTime = milliSecsPerFrame - HighResTimer::GetCurrentTimeInMilliSeconds();

            if( sleepTime > milliSecsPerFrame )
            {
                return milliSecsPerFrame;
            }

            return sleepTime;
        }

        // Current time in milliseconds
        int GetCurrentTicks() const
        {
            return  currentTicks_;
        }

    private:
        unsigned int prevTicks_;
        unsigned int currentTicks_;
        unsigned int fps_;
    };
}

#endif // !AUX_ENGINECLOCK_H