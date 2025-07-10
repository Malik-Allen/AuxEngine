// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_ENGINECONFIG
#define AUX_ENGINECONFIG

#include "engine/parsers/IniParser.h"

#include <string>

namespace  AuxEngine
{
    class EngineConfig
    {
        EngineConfig(const EngineConfig&) = delete;
        EngineConfig(EngineConfig&&) = delete;
        EngineConfig& operator=(const EngineConfig&) = delete;
        EngineConfig& operator=(EngineConfig&&) = delete;
    public:
        explicit EngineConfig(const std::string& outputDir);
        ~EngineConfig() = default;

        // Engine settings
        bool CanTick();

        // Window settings
        std::string GetEngineName();
        int GetWindowWidth();
        int GetWindowHeight();

        // Graphics settings
        int GetMaxFPS();

    private:
        IniParser iniParser_;
    };
}

#endif