﻿// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_DEBUGLOG_H
#define AUX_DEBUGLOG_H

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

enum class LOG : unsigned short
{
	NONE = 0,
	FATAL = 1,
	ERRORLOG = 2,
	WARNING = 3,
	TRACE = 4,
	INFO = 5
};

constexpr static const char* ToString( LOG logType )
{
	switch( logType )
	{
	case LOG::NONE:			return "NONE";
	case LOG::FATAL:		return "FATAL ERROR";
	case LOG::ERRORLOG:		return "ERROR";
	case LOG::WARNING:		return "WARNING";
	case LOG::TRACE:		return "TRACE";
	case LOG::INFO:			return "INFO";
	default:				return "UNKNOWN";
	}
}

	/* Creates brand new output file inside ofthe passed output directory. With an initial message for the output file. */
#define DEBUG_INIT(outputDir, initMessage) ( AuxEngine::DebugLog::DebugLogInit(outputDir, initMessage) )

/* Logs error to output log */
#define OUTPUT_FILE_LOG( LogType, Message, ... ) ( AuxEngine::DebugLog::OutputFile_Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__ ) )

/* Will print to console log */
#define CONSOLE_LOG( LogType, Message, ... ) ( AuxEngine::DebugLog::Console_Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__ ) )

/* Prints message to Output File and Console */
#define DEBUG_LOG( LogType, Message, ... ) ( OUTPUT_FILE_LOG(LogType, Message, __VA_ARGS__ ), CONSOLE_LOG(LogType, Message, __VA_ARGS__ ) )


namespace AuxEngine
{
	/*
*	Utility class for functionality around logging to console and output file
*/
	class DebugLog
	{
	public:
		DebugLog() = delete;	// Static class, no constructor needed
		DebugLog(const DebugLog&) = delete;
		DebugLog& operator=(const DebugLog&) = delete;
		DebugLog(DebugLog&&) = delete;
		DebugLog& operator=(DebugLog&&) = delete;

		static void DebugLogInit(const std::string& outputDir_ = "", const std::string& initMessage_ = "")
		{
			outputFilePath = outputDir_ + outputFileName;

			std::filesystem::path path(outputFilePath);
			if (path.has_parent_path())
			{
				std::filesystem::create_directories(path.parent_path());	// Ensure parent directories exist.
			}

			std::ofstream outputFile;
			outputFile.open(outputFilePath, std::ios::out);	// We create the file using out just to make sure it is there and clears it
			if (!outputFile)
			{
				return;
			}
			outputFile << initMessage_ << std::endl;
			outputFile.flush();
			outputFile.close();

			std::cout << initMessage_ << std::endl;
		}

		template<typename ... Args>
		static void OutputFile_Log(const LOG logType,
			const std::string& message,
			const std::string& fileName,
			const std::string& function,
			const int line,
			Args&& ... args)
		{
			std::ofstream outputFile;
			outputFile.open(outputFilePath, std::ios::app | std::ios::out);
			if (!outputFile)
			{
				return;
			}
			/*[05/15/22|21:33:51][INFO]:	FunctionName(00):	Message {}*/
			std::string output;
			output.append(BuildTimeStamp());
			output.append("[");
			output.append(ToString(logType));
			output.append("]");
			output.append(BuildFunctionSignature(fileName, line));
			output.append(": ");
			output.append(message);
			output.append("\n");

			outputFile << std::vformat(output, std::make_format_args(std::forward<Args>(args)...));

			outputFile.flush();
			outputFile.close();
		};


		template<typename ... Args>
		static void Console_Log(const LOG logType,
			const std::string& message,
			const std::string& fileName,
			const std::string& function,
			const int line,
			Args&& ... args)
		{
			/*[05/15/22|21:33:51][INFO]:	FunctionName(00):	Message {}*/
			std::string output;
			output.append(BuildTimeStamp());
			output.append("[");
			output.append(ToString(logType));
			output.append("]");
			output.append(BuildFunctionSignature(fileName, line));
			output.append(": ");
			output.append(message);
			output.append("\n");

			std::cout << std::vformat(output, std::make_format_args(std::forward<Args>(args)...));
		};

	private:
		inline static std::string outputFilePath = "";
		inline static std::string outputFileName = "Output-Log.txt";

		/* Returns a string in the format: [05/15/22|21:33:51]*/
		static std::string BuildTimeStamp()
		{
			/*
			*	Code to obtain Date and Time stamps, adapted from:
			*	https://www.daniweb.com/programming/software-development/threads/177665/help-with-asctime-s-and-localtime-s
			*/
			char date[9];
			_strdate_s(date);
			char timestamp[9];
			_strtime_s(timestamp);

			/*[05/15/22|21:33:51]*/
			std::string dateTime;
			dateTime.append("[");
			dateTime.append(std::string(date));
			dateTime.append("|");
			dateTime.append(std::string(timestamp));
			dateTime.append("]");

			return dateTime;
		}

		/* Returns a string in the format: FunctionName(00)*/
		static std::string BuildFunctionSignature(const std::string& function, const int lineNumber)
		{
			/*FunctionName(00):*/
			std::string signature;
			signature.append("[");
			signature.append(function);
			signature.append(":");
			signature.append(std::to_string(lineNumber));
			signature.append("]");
			return signature;
		}
	};
}

#endif	// AUX_DEBUGLOG_H