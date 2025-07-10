// MIT License, Copyright (c) 2025 Malik Allen

#include "engine/core/EngineConfig.h"

#include "engine/core/DebugLog.h"
#include "engine/core/FileUtils.h"
#include "engine/parsers/IniParser.h"

namespace  AuxEngine
{
	static const std::string ConfigFileName("config/AuxEngine.ini");
	static const std::string EngineSection("Engine");
	static const std::string WindowSection("Window");
	static const std::string GraphicsSection("Graphics");

	EngineConfig::EngineConfig(const std::string& outputDir)
		: iniParser_("")
	{
		const std::string configFile = outputDir + ConfigFileName;
		FileUtils::CreateIniFile(configFile, { EngineSection, WindowSection, GraphicsSection });
		iniParser_ = IniParser(configFile);
		iniParser_.Read();
	}

	bool EngineConfig::CanTick()
	{
		return iniParser_.GetBoolean(EngineSection, "tickEnabled", true);
	}

	std::string EngineConfig::GetEngineName()
	{
		return iniParser_.GetString(WindowSection, "name", "DefaultEngineName");
	}

	int EngineConfig::GetWindowWidth()
	{
		return iniParser_.GetInteger(WindowSection, "width", 256);
	}

	int EngineConfig::GetWindowHeight()
	{
		return iniParser_.GetInteger(WindowSection, "height", 256);
	}

	int EngineConfig::GetMaxFPS()
	{
		return iniParser_.GetInteger(GraphicsSection, "maxFPS", 30);
	}
}