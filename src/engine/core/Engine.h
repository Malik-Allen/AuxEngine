// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUXENGINE_H
#define AUXENGINE_H

#include "Singleton.h"

namespace  AuxEngine
{
    class EngineClock;
    class IWindowHandler;
    class InputHandler;
    class IApp;

    class Engine : public Singleton<Engine>
    {
        friend class Singleton;

        Engine();

    public:
        Engine( const Engine& ) = delete;
        Engine& operator=( const Engine& ) = delete;
        Engine( Engine&& ) = delete;
        Engine& operator = ( Engine&& ) = delete;

        ~Engine() override = default;

    private:
        bool m_isRunning;
        std::unique_ptr<EngineClock> m_clock;
        std::unique_ptr<IWindowHandler> m_windowHandler;
        InputHandler& m_inputHandler;
        std::unique_ptr<IApp> m_app;

        void Update( const float deltaTime );

    public:
        void Start();
        bool LoadApp( IApp* app );
        void Run();
        bool IsRunning() const { return m_isRunning; }
        void Shutdown();

        InputHandler& GetInputHandler() const { return m_inputHandler; }
        const EngineClock& GetClock() const { return *m_clock; }
    };
}

#endif // !AUXENGINE_H