// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUXENGINE_H
#define AUXENGINE_H

#include "Singleton.h"

namespace AuxEngine
{
    class EngineClock;
    class WindowHandler;
    class InputHandler;
    class App;

    class Engine : public Singleton<Engine>
    {
        friend class Singleton;

        Engine();

    public:
        Engine( const Engine& ) = delete;
        Engine& operator=( const Engine& ) = delete;
        Engine( Engine&& ) = delete;
        Engine& operator = ( Engine&& ) = delete;

        ~Engine() override;

    private:
        bool isRunning_;
        std::unique_ptr<EngineClock> clock_;
        std::unique_ptr<WindowHandler> windowHandler_;
        InputHandler& inputHandler_;
        std::unique_ptr<App> app_;

        void Update( const float deltaTime );

    public:
        void Start();
        bool LoadApp( App* app );
        void Run();
        bool IsRunning() const { return isRunning_; }
        void Shutdown();

        InputHandler& GetInputHandler() const { return inputHandler_; }
        const EngineClock& GetClock() const { return *clock_; }
    };
}

#endif // !AUXENGINE_H