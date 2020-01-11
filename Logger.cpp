#include "Logger.h"
#if defined(DEBUG)
std::string Logger::Indent;
Logger::Logger(const char* fileName, const char* funcName, int lineNumber) {
	_fileName = fileName;
	_funcName = funcName;
	Indent.append("  ");
	std::cout << Indent << "Entering " << _funcName << "() - (" << _fileName << ":" << lineNumber << ")" << std::endl;
}

Logger::~Logger() {
	Indent.resize(Indent.length() - 2);
	std::cout << Indent << "Leaving  " << _funcName << "() - (" << _fileName << ")" << std::endl;
}
#endif