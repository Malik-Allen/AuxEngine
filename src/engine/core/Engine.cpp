// MIT License, Copyright (c) 2019 Malik Allen

#include "engine/core/Engine.h"

#include "engine/core/App.h"
#include "engine/core/EngineClock.h"
#include "engine/core/EngineConfig.h"
#include "engine/core/DebugLog.h"
#include "engine/devices/GLFW/GLFWInputHandler.h"
#include "engine/devices/GLFW/GLFWWindowHandler.h"

#include <string>

namespace  AuxEngine
{
    Engine::Engine() :
        m_isRunning( false ),
        m_clock( std::make_unique<EngineClock>() ),
        m_windowHandler( nullptr ),
        m_inputHandler(GLFWInputHandler::Get()),
        m_app(std::make_unique<IApp>())
    {}

    void Engine::Update( const float deltaTime )
    {
        m_windowHandler->ProcessEvents();
        m_inputHandler.Update(deltaTime);
        m_app->Update(deltaTime);

        if (m_inputHandler.IsKeyDown(Key::Escape))
        {
            m_isRunning = false;
        }
    }

    void Engine::Start()
    {
        DEBUG_INIT();

        DEBUG_LOG(LOG::INFO, "Waking up...");

        EngineConfig& engineConfig = EngineConfig::Get();

        const std::string name = engineConfig.GetEngineName();
        const int width = engineConfig.GetWindowWidth();
        const unsigned int height = engineConfig.GetWindowHeight();
        const unsigned int fps = engineConfig.GetMaxFPS();
        
        m_isRunning = false;

        m_clock->SetFPS(fps);

        m_windowHandler = std::make_unique<GLFWWindowHandler>();
        if (!m_windowHandler->InitializeWindow(width, height, name))
        {
            return;
        }

        if (!m_inputHandler.Initialize(m_windowHandler.get()))
        {
            return;
        }

        m_isRunning = true;

        DEBUG_LOG(LOG::INFO, "Wake up protocol complete!");
    }

    bool Engine::LoadApp( IApp* app )
    {
        if( !app )
        {
            return false;
        }
        m_app.reset( app );
        return m_app->Enter();
    }

    void Engine::Run()
    {
        while( m_isRunning )
        {
            m_clock->UpdateFrameTicks();
            Update( m_clock->GetDeltaTime() );
            Sleep( m_clock->GetSleepTime( m_clock->GetFPS() ) );    // TODO: Not optimal and should be replaced with a better sleep function
        }

        if( !m_isRunning )
        {
            Shutdown();
        }
    }

    void Engine::Shutdown()
    {
        DEBUG_LOG(LOG::INFO, "Shutting down...");

        m_isRunning = false;

        if( m_app )
        {
            m_app->Exit();
            m_app.reset();
        }

        if( m_windowHandler )
        {
            m_windowHandler->Shutdown();
            m_windowHandler.reset();
        }

        DEBUG_LOG(LOG::INFO, "Night, night.");

    }
}
