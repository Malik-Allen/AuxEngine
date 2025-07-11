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
		static bool DoesFileExist(const std::string& filePath);
		static bool CreateFileAtPath(const std::string& filePath);
		static bool CreateDirectories(const std::string& dirPath);
		static bool CreateUniqueDirectory(const std::string& basePath, const std::string& dirName, std::string& outDir);
		static bool DeleteFileAtPath(const std::string& filePath);
		static bool DeleteDirectory(const std::string& dirPath);
		static std::vector<std::string> GetSubdirectories(const std::string& dirPath);
		static bool DuplicateFile(const std::string& sourceFilePath, const std::string& destFilePath);
		static bool CopyDirectory(const std::string& sourceDirPath, const std::string& destDirPath);
		static bool GetLastWriteTimestamp(const std::string& _path, std::string& outTimeStamp);
		static std::string GetDate();

		static std::string to_lowercase(const std::string& in);
		static std::string to_uppercase(const std::string& in);
		static bool has_extension(const std::string& filePath, const std::string& _ext);

		static bool CreateIniFile(const std::string& filePath, const std::vector<std::string>& sections);
		static bool CreateCsvFile(const std::string& filePath, const std::vector<std::string>& headers);

		static std::string GetExecutableDirectory();
		static std::string GetLocalAppDataDirectory(const std::string& appName);
	};
}

#endif // !AUXENGINE_FILEUTILS_H