// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_ENGINECLOCK_H
#define AUX_ENGINECLOCK_H

#ifndef MILLISECONDS_TO_SECONDS
#define MILLISECONDS_TO_SECONDS (1 / 1000.0f)
#endif

#ifndef SECONDS_TO_MILLISECONDS
#define SECONDS_TO_MILLISECONDS (1000 / 1)
#endif

#ifndef MICROSECONDS_TO_SECONDS
#define MICROSECONDS_TO_SECONDS (1 / 1000000.0f)
#endif

#ifndef SECONDS_TO_MICROSECONDS
#define SECONDS_TO_MICROSECONDS (1000000 / 1)
#endif

#ifndef MILLISECONDS_TO_MICROSECONDS
#define MILLISECONDS_TO_MICROSECONDS (1000 / 1)
#endif

#ifndef MICROSECONDS_TO_MILLISECONDS
#define MICROSECONDS_TO_MILLISECONDS (1 / 1000.0f)
#endif

namespace AuxEngine
{
    class EngineClock
    {
    public:
        EngineClock();
        EngineClock(const EngineClock&) = delete;
        EngineClock(EngineClock&&) = delete;
        EngineClock& operator=(const EngineClock&) = delete;
        EngineClock& operator=(EngineClock&&) = delete;
        ~EngineClock() = default;

        unsigned int GetFPS() const;
        void SetFPS(unsigned int fps);

        void Reset();
        void UpdateFrameTicks();
        float GetDeltaTime() const;
        unsigned int GetSleepTime(const unsigned int fps);
        int GetCurrentTicks() const; // Current time in milliseconds

    private:
        unsigned int prevTicks_;
        unsigned int currentTicks_;
        unsigned int fps_;

    public:
        unsigned int GetCurrentTimeInMicroSeconds() const;
        unsigned int GetCurrentTimeInMilliSeconds() const;
    };
}

#endif // !AUX_ENGINECLOCK_H