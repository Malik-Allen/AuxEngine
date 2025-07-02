// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUX_ENGINECONFIG
#define AUX_ENGINECONFIG

#include "engine/core/Singleton.h"

#include <string>

namespace  AuxEngine
{
    class IniParser;

    class EngineConfig : public Singleton<EngineConfig>
    {
    public:
        EngineConfig(const EngineConfig&) = delete;
        EngineConfig& operator=(const EngineConfig&) = delete;
        EngineConfig(EngineConfig&&) = delete;
        EngineConfig& operator=(EngineConfig&&) = delete;

        EngineConfig();
        ~EngineConfig() override = default;

        // Window settings
        std::string GetEngineName() const;
        int GetWindowWidth() const;
        int GetWindowHeight() const;

        // Graphics settings
        int GetMaxFPS() const;

    private:
        std::unique_ptr<IniParser> iniParser_;
    };
}

#endif