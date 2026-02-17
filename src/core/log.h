#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>

enum class LogLevel {
    CRITICAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    TRACE,
    FRAME,
    POSITION // Add POSITION log level here (though we will treat it differently)
};

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void log(LogLevel level, const std::string& message);
    void setLogLevel(LogLevel level);  // Function to set the logging level

private:
    std::ofstream logFile;
    LogLevel currentLogLevel = LogLevel::DEBUG; // Default log level
    std::map<LogLevel, std::string> logLevelNames;

    std::string getCurrentTime();
    std::string levelToString(LogLevel level);
};

extern Logger logger;  // Declare the global logger instance

#endif // LOG_H
