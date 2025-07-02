// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUXENGINE_FILEUTILS_H
#define AUXENGINE_FILEUTILS_H

#include <string>
#include <vector>

namespace AuxEngine
{
	class FileUtils
	{
		FileUtils() = delete;
		FileUtils(const FileUtils&) = delete;
		FileUtils(FileUtils&&) = delete;
		FileUtils& operator=(const FileUtils&) = delete;
		FileUtils& operator = (FileUtils&&) = delete;
		~FileUtils() = delete;

	public:
		static bool CreateFileAtPath(const std::string& filePath);
		static bool CreateDirectories(const std::string& dirPath);
		static bool DeleteFileAtPath(const std::string& filePath);
		static std::vector<std::string> GetSubdirectories(const std::string& dirPath);
		static bool DuplicateFile(const std::string& sourceFilePath, const std::string& destFilePath);
		static bool DuplicateDirectory(const std::string& sourceDirPath, const std::string& destDirPath);
	};
}

#endif // !AUXENGINE_FILEUTILS_H