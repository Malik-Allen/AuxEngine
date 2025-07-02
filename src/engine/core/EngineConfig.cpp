// MIT License, Copyright (c) 2025 Malik Allen

#include "engine/core/EngineConfig.h"

#include "engine/core/DebugLog.h"
#include "engine/parsers/IniParser.h"

namespace  AuxEngine
{
	static const std::string EngineConfigFile(std::string(AUXENGINE_CONFIG_DIR) + "AuxEngine.ini");
	
	static const std::string WindowSection("Window");
	static const std::string GraphicsSection("Graphics");

	EngineConfig::EngineConfig()
		: iniParser(std::make_unique<IniParser>())
	{
		if (!iniParser->LoadFile(EngineConfigFile))
		{
			DEBUG_LOG(LOG::WARNING, "Failed to open Engine Config file at location: {}", EngineConfigFile);
		}
	}

	std::string EngineConfig::GetEngineName() const
	{
		return iniParser->GetString(WindowSection, "name");
	}

	int EngineConfig::GetWindowWidth() const
	{
		return iniParser->GetInteger(WindowSection, "width");
	}

	int EngineConfig::GetWindowHeight() const
	{
		return iniParser->GetInteger(WindowSection, "height");
	}

	int EngineConfig::GetMaxFPS() const
	{
		return iniParser->GetInteger(GraphicsSection, "maxFPS");
	}
}