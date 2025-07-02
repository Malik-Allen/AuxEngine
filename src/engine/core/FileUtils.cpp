// MIT License, Copyright (c) 2025 Malik Allen

#include "FileUtils.h"

#include "DebugLog.h"

#include <filesystem>
#include <fstream>

namespace AuxEngine
{
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

	bool FileUtils::DuplicateDirectory(const std::string& sourceDirPath, const std::string& destDirPath)
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
}