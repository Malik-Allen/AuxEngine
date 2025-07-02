// MIT License, Copyright (c) 2019 Malik Allen

#include "engine/core/Engine.h"

#include "engine/core/App.h"
#include "engine/core/EngineClock.h"
#include "engine/core/EngineConfig.h"
#include "engine/core/DebugLog.h"
#include "engine/devices/GLFW/GLFWInputHandler.h"
#include "engine/devices/GLFW/GLFWWindowHandler.h"

#include <fstream>
#include <string>

namespace  AuxEngine
{
    static const std::string AsciiLogoRaw = R"(~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                       %%                     #@                                                    
                      @@@                    @@@                                                    
                     #@@@        %@%%     %@@@@@                                                    
                      @@@@@@@@@@@@@@@@@@@@@@@@%                                                     
                      %@@@@@@@@@@@@@@@@@@@@@@                                                       
                         %@@@@@@@@@@@@@@@@%                                                         
                          %@@@@@@@@@@@@@@@@@@@@#                                                    
                         @@@@@@@@@@@@@@@@@@%@@@@@@@                                                 
                        %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#                                            
                        @@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@@@@@%                             
                       @@@@@@@@@%@@@@@@@@@%@@@%@@@@@@@@@@@@@@@@@@@@@@@@@@@         %%               
                      %@@@@@@@@@@@@%%#* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       @@@               
                      %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     @@@@#              
                       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@%    @@@@#              
                       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@%   #@@@               
                        %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@* @@@%  @@@                
                         @@@@@@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@%@@@@@@@@@@@@%  %@@@@@%                 
                          %@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@%@@@@@@@@@@@@%                         
                          @@%@@@@@@@@@@@@@@@@@@@@@@@@@#%@@@@@@@%@@@@@@@@@@@@                        
                         @@@@@%@@@@@@@@@@@@@@%         @@@@@@@@@   @@@@@@@@@#                       
                         @@@@@@  %@@@% @@@@@@           %@@@@@@@     %@@@@@@%                       
                         %@@@@%         @@@@%            @@@@@@        %@@@@@                       
                        #@@@@%          @@@@@          %@@@@@*          @@@@@@                      
                       @@@@@@          %@@@@%         @@@@@@            @@@@@@                      
                      @@@@@@%         @@@@@@        %@@@@@%           %@@@@@@                       
                      %%@%@%         @%%@@%%       %%%%%%             @@@@@%#
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Aux Engine (c) 2025, Malik Allen
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   
)";

    Engine::Engine() :
        isRunning_( false ),
        clock_( std::make_unique<EngineClock>() ),
        windowHandler_( nullptr ),
        inputHandler_(GLFWInputHandler::Get()),
        app_(std::make_unique<App>())
    {}

    Engine::~Engine()
    {
		if (isRunning_)
		{
			Shutdown();
		}
    }

    void Engine::Update( const float deltaTime )
    {
        windowHandler_->ProcessEvents();
        inputHandler_.Update(deltaTime);
        app_->Update(deltaTime);

        if (inputHandler_.IsKeyDown(Key::Escape))
        {
            isRunning_ = false;
        }
    }

    void Engine::Start()
    {
        DEBUG_INIT(AsciiLogoRaw);

        DEBUG_LOG(LOG::INFO, "Waking up...");

        EngineConfig& engineConfig = EngineConfig::Get();

        const std::string name = engineConfig.GetEngineName();
        const int width = engineConfig.GetWindowWidth();
        const unsigned int height = engineConfig.GetWindowHeight();
        const unsigned int fps = engineConfig.GetMaxFPS();
        
        isRunning_ = false;

        clock_->SetFPS(fps);

        windowHandler_ = std::make_unique<GLFWWindowHandler>();
        if (!windowHandler_->InitializeWindow(width, height, name))
        {
            return;
        }

        if (!inputHandler_.Initialize(windowHandler_.get()))
        {
            return;
        }

        isRunning_ = true;

        DEBUG_LOG(LOG::INFO, "Wake up protocol complete!");
    }

    bool Engine::LoadApp( App* app )
    {
        if( !app )
        {
            return false;
        }
        app_.reset( app );
        return app_->Enter();
    }

    void Engine::Run()
    {
        while( isRunning_ )
        {
            clock_->UpdateFrameTicks();
            Update( clock_->GetDeltaTime() );
            Sleep( clock_->GetSleepTime( clock_->GetFPS() ) );    // TODO: Not optimal and should be replaced with a better sleep function
        }

        if( !isRunning_ )
        {
            Shutdown();
        }
    }

    void Engine::Shutdown()
    {
        DEBUG_LOG(LOG::INFO, "Shutting down...");

        isRunning_ = false;

        if( app_ )
        {
            app_->Exit();
            app_.reset();
        }

        if( windowHandler_ )
        {
            windowHandler_->Shutdown();
            windowHandler_.reset();
        }

        DEBUG_LOG(LOG::INFO, "Night, night.");

    }
}
