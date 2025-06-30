// MIT License, Copyright (c) 2025 Malik Allen

#include "engine/core/EngineConfig.h"

#include "engine/core/DebugLog.h"
#include "engine/parsers/IniParser.h"

namespace  AuxEngine
{
	static const std::string EngineConfigFile(std::string(AUXENGINE_CONFIG_DIR) + "Engine.ini");
	
	static const std::string WindowSection("Window");
	static const std::string GraphicsSection("Graphics");

	EngineConfig::EngineConfig()
		: iniParser(std::make_unique<IniParser>(EngineConfigFile))
	{
		if (!iniParser->IsOpen())
		{
			DEBUG_LOG(LOG::FATAL, "Failed to open Engine Config file at location: {} Ensure that the Engine.ini is location at the correct file directory", EngineConfigFile);
		}
	}

	std::string EngineConfig::GetEngineName() const
	{
		return iniParser->GetString(WindowSection, "name", "Default Name");
	}

	int EngineConfig::GetWindowWidth() const
	{
		return iniParser->GetInteger(WindowSection, "width", 1920);
	}

	int EngineConfig::GetWindowHeight() const
	{
		return iniParser->GetInteger(WindowSection, "height", 1080);
	}

	int EngineConfig::GetMaxFPS() const
	{
		return iniParser->GetInteger(GraphicsSection, "maxFPS", 120);
	}
}