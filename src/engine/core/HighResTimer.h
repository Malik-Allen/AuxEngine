// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_HIGHRESTIMER_H
#define AUX_HIGHRESTIMER_H

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


namespace AuxEngine
{
    class HighResTimer
    {
    public:
        HighResTimer();
        HighResTimer( const HighResTimer& ) = delete;
        HighResTimer( HighResTimer&& ) = delete;
        HighResTimer& operator=(const HighResTimer&) = delete;
        HighResTimer& operator=(HighResTimer&&) = delete;
        virtual ~HighResTimer();

        unsigned int GetCurrentTimeInMicroSeconds();
        unsigned int GetCurrentTimeInMilliSeconds();
    };
}

#endif // !AUX_HIGHRESTIMER_H