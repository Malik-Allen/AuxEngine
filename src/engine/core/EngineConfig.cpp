// MIT License, Copyright (c) 2025 Malik Allen

#include "engine/core/EngineConfig.h"

#include "engine/core/DebugLog.h"
#include "engine/parsers/IniParser.h"

namespace  AuxEngine
{
	static const std::string engineConfigFile(std::string(AUXENGINE_CONFIG_DIR) + "AuxEngine.ini");
	
	static const std::string windowSection("Window");
	static const std::string graphicsSection("Graphics");

	EngineConfig::EngineConfig()
		: iniParser_(std::make_unique<IniParser>())
	{
		if (!iniParser_->LoadFile(engineConfigFile))
		{
			DEBUG_LOG(LOG::WARNING, "Failed to open Engine Config file at location: {}", engineConfigFile);
		}
	}

	std::string EngineConfig::GetEngineName() const
	{
		return iniParser_->GetString(windowSection, "name");
	}

	int EngineConfig::GetWindowWidth() const
	{
		return iniParser_->GetInteger(windowSection, "width");
	}

	int EngineConfig::GetWindowHeight() const
	{
		return iniParser_->GetInteger(windowSection, "height");
	}

	int EngineConfig::GetMaxFPS() const
	{
		return iniParser_->GetInteger(graphicsSection, "maxFPS");
	}
}