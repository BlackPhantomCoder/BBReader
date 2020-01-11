#pragma once
#if defined(DEBUG)
#include <iostream>
class Logger
{
public:
	Logger(const char* fileName, const char* funcName, int lineNumber);
	~Logger();
private:
	const char* _fileName;
	const char* _funcName;
	static std::string Indent;
};
#define LOG(x) printf(x);
#define LOGF Logger Logger(__FILE__, __FUNCTION__, __LINE__);
#else
#define LOG(x)
#endif