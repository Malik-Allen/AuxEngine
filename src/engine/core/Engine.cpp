// MIT License, Copyright (c) 2019 Malik Allen

#include "engine/core/Engine.h"

#include "engine/core/App.h"
#include "engine/core/DebugLog.h"
#include "engine/core/EngineClock.h"
#include "engine/core/EngineConfig.h"
#include "engine/devices/GLFW/GLFWInputHandler.h"
#include "engine/devices/GLFW/GLFWWindowHandler.h"

#include <chrono>
#include <fstream>
#include <string>
#include <thread>

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
        canTick_(true),
        isRunning_(false),
        config_(nullptr),
        clock_(std::make_unique<EngineClock>()),
        windowHandler_(nullptr),
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

    void Engine::Update(const float deltaTime)
    {
        windowHandler_->ProcessEvents();
        inputHandler_.Update(deltaTime);
        app_->Update(deltaTime);

        if (inputHandler_.IsKeyDown(Key::Escape))
        {
            isRunning_ = false;
        }
    }

    void Engine::Start(const char* outputDir)
    {
        DEBUG_INIT(outputDir, AsciiLogoRaw);
        DEBUG_LOG(LOG::INFO, "Waking up...");

        isRunning_ = false;

        config_ = std::make_unique<EngineConfig>(outputDir);
        canTick_ = config_->CanTick();

        if (canTick_)
        {
            clock_->SetFPS(config_->GetMaxFPS());

            windowHandler_ = std::make_unique<GLFWWindowHandler>();
            if (!windowHandler_->InitializeWindow(config_->GetWindowWidth(), config_->GetWindowHeight(), config_->GetEngineName()))
            {
                return;
            }

            if (!inputHandler_.Initialize(windowHandler_.get()))
            {
                return;
            }
        }

        isRunning_ = true;

        DEBUG_LOG(LOG::INFO, "Wake up protocol complete!");
    }

    bool Engine::LoadApp(App* app)
    {
        if(!app)
        {
            return false;
        }
        app_.reset(app);
        return app_->Enter();
    }

    void Engine::Run()
    {
        if (canTick_)
        {
            while (isRunning_)
            {
                clock_->UpdateFrameTicks();
                Update(clock_->GetDeltaTime());
                std::this_thread::sleep_for(std::chrono::milliseconds(clock_->GetSleepTime(clock_->GetFPS()))); // TODO: Replace sleep with Busy-Wait.
            }

            if (!isRunning_)
            {
                Shutdown();
            }
        }
    }

    void Engine::Shutdown()
    {
        DEBUG_LOG(LOG::INFO, "Shutting down...");

        isRunning_ = false;

        if(app_)
        {
            app_->Exit();
            app_.reset();
        }

        if(windowHandler_)
        {
            windowHandler_->Shutdown();
            windowHandler_.reset();
        }

        if(config_)
        {
            config_.reset();
        }

        DEBUG_LOG(LOG::INFO, "Night, night.");
    }
}
