﻿#pragma once

// Logger code based on: https://github.com/SFML/SFML/wiki/Source:-Simple-File-Logger-(by-mateandmetal)

#include <fstream>
#include "CommonUtilities.h"

#define MAX_LOG_FILE_SIZE (8*1024*1024) // 8 MB

class Logger 
{

public:

	enum class eLogType
	{
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
	};


	Logger(const std::string& dirPath, const std::string& fileName = "game.log", long maxLogFileSize = MAX_LOG_FILE_SIZE);
					
	~Logger();
	
	// block copy ctor & assignment
	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;

	void writeToLog(const std::string msg, bool writeToConsole = false, const eLogType logType = eLogType::LOG_INFO);	

private:
	std::ofstream _logFile;
	unsigned int _numWarnings;
	unsigned int _numErrors;
	std::mutex _mutex;


	static std::string getCurrentTime();

	static long getFileSize(std::string filename);

	// Overload << operator using log type
	friend Logger &operator << (Logger &logger, const eLogType logType);
	friend Logger &operator << (Logger &logger, const std::string text)
	{
		logger._logFile << text.c_str() << std::endl;
		return logger;
	}

};
