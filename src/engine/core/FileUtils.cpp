// MIT License, Copyright (c) 2025 Malik Allen

#include "FileUtils.h"

#include "engine/core/DebugLog.h"
#include "engine/parsers/CsvWriter.h"
#include "engine/parsers/IniParser.h"

#include <filesystem>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>  // SHGetKnownFolderPath
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
#elif __APPLE__
#include <mach-o/dyld.h>
#else // Linux
#include <unistd.h>
#endif

namespace AuxEngine
{
	static const std::string IniExt(".ini");
	static const std::string CsvExt(".csv");
	static const std::string TxtExt(".txt");

	bool FileUtils::DoesFileExist(const std::string& filePath)
	{
		std::filesystem::path path(filePath);
		return std::filesystem::exists(filePath);
	}

	bool FileUtils::CreateFileAtPath(const std::string& filePath)
	{
		std::filesystem::path path(filePath);
		if (path.has_parent_path()) 
		{
			std::filesystem::create_directories(path.parent_path());	// Ensure parent directories exist.
		}

		std::ofstream file(path, std::ios::app);
		if (!file) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create file {}", filePath);
			return false;
		}
		return true;
	}

	bool FileUtils::CreateDirectories(const std::string& dirPath)
	{
		if (!std::filesystem::create_directories(dirPath))
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create directory {}", dirPath);
			return false;
		}
		return true;
	}

	bool FileUtils::CreateUniqueDirectory(const std::string& basePath, const std::string& dirName, std::string& outDir)
	{
		std::filesystem::path targetPath = basePath + "/" + dirName;

		int counter = 1;
		while (std::filesystem::exists(targetPath)) 
		{
			std::ostringstream oss;
			oss << dirName << " (" << counter << ")";
			targetPath = basePath + "/" + oss.str();
			++counter;
		}

		if (std::filesystem::create_directory(targetPath)) 
		{
			outDir = targetPath.string();
			return true;
		}
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create unique directory {} / {}", basePath, dirName);
			return false;
		}
	}

	bool FileUtils::DeleteFileAtPath(const std::string& filePath)
	{
		std::error_code err;
		bool result = std::filesystem::remove(filePath, err);
		if (err)
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to remove file {} ErrMsg:{} ", filePath, err.message());
		}
		return result;
	}

	bool FileUtils::DeleteDirectory(const std::string& dirPath)
	{
		std::error_code err;
		bool result = std::filesystem::remove_all(dirPath, err);
		if (err)
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to remove directory {} ErrMsg:{} ", dirPath, err.message());
		}
		return result;
	}

	std::vector<std::string> FileUtils::GetDirectoryFiles(const std::string& dirPath)
	{
		std::vector<std::string> files;
		if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath))
		{
			for (const auto& entry : std::filesystem::directory_iterator(dirPath))
			{
				if (!entry.is_directory())
				{
					files.push_back(entry.path().filename().string());
				}
			}
		}
		return files;
	}

	std::vector<std::string> FileUtils::GetSubdirectories(const std::string& dirPath)
	{
		std::vector<std::string> subDirs;
		if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath)) 
		{
			for (const auto& entry : std::filesystem::directory_iterator(dirPath)) 
			{
				if (entry.is_directory()) 
				{
					subDirs.push_back(entry.path().filename().string());
				}
			}
		}
		return subDirs;
	}

	bool FileUtils::DuplicateFile(const std::string& sourceFilePath, const std::string& destFilePath)
	{
		std::error_code err;

		std::filesystem::path source(sourceFilePath);
		std::filesystem::path destination(destFilePath);

		// Create parent directories for destination if they don't exist
		if (destination.has_parent_path()) 
		{
			std::filesystem::create_directories(destination.parent_path(), err);
			if (err) 
			{
				DEBUG_LOG(LOG::ERRORLOG, "Failed to create destination file {} ErrMsg: {}", destFilePath, err.message());
				return false;
			}
		}

		// Copy the file, overwrite if exists
		std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing, err);
		if (err) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to copy file {} to destination {} ErrMsg: {}", sourceFilePath, destFilePath, err.message());
			return false;
		}

		return true;
	}

	bool FileUtils::CopyDirectory(const std::string& sourceDirPath, const std::string& destDirPath)
	{
		std::error_code err;

		std::filesystem::path sourcePath(sourceDirPath);
		std::filesystem::path destinationPath(destDirPath);

		if (!std::filesystem::exists(sourcePath) || !std::filesystem::is_directory(sourcePath)) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to find src directory {} ErrMsg: {}", sourceDirPath, err.message());
			return false;
		}

		// Create destination directory if it doesn't exist
		std::filesystem::create_directories(destinationPath, err);
		if (err) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create destination directory {} ErrMsg: {}", destDirPath, err.message());
			return false;
		}

		for (auto const& entry : std::filesystem::recursive_directory_iterator(sourcePath)) 
		{
			const auto& path = entry.path();
			auto relativePath = std::filesystem::relative(path, sourcePath);
			auto targetPath = destinationPath / relativePath;

			if (entry.is_directory()) 
			{
				std::filesystem::create_directories(targetPath, err);
				if (err) 
				{
					DEBUG_LOG(LOG::ERRORLOG, "Failed to create target directory {} ErrMsg: {}", targetPath.string(), err.message());
					return false;
				}
			}
			else if (entry.is_regular_file()) 
			{
				std::filesystem::copy_file(path, targetPath, std::filesystem::copy_options::overwrite_existing, err);
				if (err) 
				{
					DEBUG_LOG(LOG::ERRORLOG, "Failed to copy file {} to target file {} ErrMsg: {}", path.string(), targetPath.string(), err.message());
					return false;
				}
			}
			else 
			{
				// Nothing else is handled!
				DEBUG_LOG(LOG::WARNING, "Failed to copy unknown file {} to target file {} ErrMsg: {}", path.string(), targetPath.string(), err.message());
			}
		}
		return true;
	}

	bool FileUtils::GetLastWriteTimestamp(const std::string& _path, std::string& outTimeStamp)
	{
		std::filesystem::path path(_path);

		if (!std::filesystem::exists(path)) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to get last write timestamp. No path exists at {}", path.string());
			return false;
		}

		auto fileTime = std::filesystem::last_write_time(path);

		// Convert to system_clock time_point
		auto timePoint = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
		const std::time_t time = std::chrono::system_clock::to_time_t(timePoint);

		std::ostringstream oss;
		oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
		outTimeStamp = oss.str();
		return true;
	}

	std::string FileUtils::GetDate()
	{
		const auto now = std::chrono::system_clock::now();
		const auto timePoint = std::chrono::clock_cast<std::chrono::system_clock>(now);
		const std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
		std::ostringstream oss;
		oss << std::put_time(std::localtime(&time), "%Y-%m-%d");
		return oss.str();
	}

	std::string FileUtils::to_lowercase(const std::string& in)
	{
		std::string out = in;
		std::transform(out.begin(), out.end(), out.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return out;
	}

	std::string FileUtils::to_uppercase(const std::string& in)
	{
		std::string out = in;
		std::transform(out.begin(), out.end(), out.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return out;
	}

	bool FileUtils::has_extension(const std::string& filePath, const std::string& _ext)
	{
		std::filesystem::path path(filePath);
		std::string ext = to_lowercase(path.extension().string());

		std::string targetExt = to_lowercase(_ext);
		if (!targetExt.empty() && targetExt[0] != '.') 
		{
			targetExt = '.' + targetExt;
		}

		return ext == targetExt;
	}

	bool FileUtils::CreateIniFile(const std::string& filePath, const std::vector<std::string>& sections)
	{
		if (!has_extension(filePath, IniExt))
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create ini file {} ErrMsg: File does not have ext: {}!", filePath, IniExt);
			return false;
		}

		if (sections.empty())
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create ini file {} ErrMsg: Sections are empty!", filePath);
			return false;
		}

		if (!CreateFileAtPath(filePath))
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create ini file {}", filePath);
			return false;
		}

		IniParser parser(filePath);
		parser.Read();	// If the exists, load all of its existing data, not to lose it.

		for (const auto& sec : sections)
		{
			parser.AddSection(sec);
		}

		if (!parser.Write())
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to save sections to ini file {}", filePath);
			return false;
		}

		return true;
	}

	bool FileUtils::CreateCsvFile(const std::string& filePath, const std::vector<std::string>& headers)
	{
		if (!has_extension(filePath, CsvExt))
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create csv file {} ErrMsg: File does not have ext: {}!", filePath, CsvExt);
			return false;
		}

		if (headers.empty())
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create csv file {} ErrMsg: Headers are empty!", filePath);
			return false;
		}

		if (!CreateFileAtPath(filePath))
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create csv file {}", filePath);
			return false;
		}

		// Open output file stream
		std::ofstream file(filePath);
		if (!file.is_open()) 
		{
			DEBUG_LOG(LOG::ERRORLOG, "Failed to create csv file. Could not write headers {}", filePath);
			return false;
		}

		auto writer = AuxEngine::CsvWriter<std::ofstream, true>::FromCsv(file);
		writer << headers;
		file.close();
		return true;
	}

#ifdef _WIN32
	std::string FileUtils::GetExecutableDirectory() {
		char path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		return std::filesystem::path(path).parent_path().string();
	}
#elif __APPLE__
	std::string FileUtils::GetExecutableDirectory() {
		char path[1024];
		uint32_t size = sizeof(path);
		if (_NSGetExecutablePath(path, &size) == 0)
			return std::filesystem::path(path).parent_path().string();
		else
			return {};
	}
#else // Linux
	std::string FileUtils::GetExecutableDirectory() {
		char result[1024];
		ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
		return std::filesystem::path(std::string(result, (count > 0) ? count : 0)).parent_path().string();
	}
#endif

	std::string FileUtils::GetLocalAppDataDirectory(const std::string& appName)
	{
		std::string path;
#ifdef _WIN32
		PWSTR widePath = nullptr;
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &widePath))) {
			char ansiPath[MAX_PATH];
			wcstombs(ansiPath, widePath, MAX_PATH);
			path = ansiPath;
			CoTaskMemFree(widePath);
		}
#elif __APPLE__
		const char* home = getenv("HOME");
		if (home)
			path = std::string(home) + "/Library/Application Support";
#else // Linux
		const char* xdg = getenv("XDG_DATA_HOME");
		if (xdg)
			path = xdg;
		else {
			const char* home = getenv("HOME");
			if (home)
				path = std::string(home) + "/.local/share";
		}
#endif
		if (!path.empty() && !appName.empty())
		{
			path += "/" + appName;
		}
		return path;
	}
}