#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

// Initialize static members
Logger::Level Logger::minLevel_ = Logger::Level::DEBUG;
std::mutex Logger::mutex_;
std::ofstream Logger::fileStream_;
bool Logger::useFile_ = false;

// ------------------------------------------------------------------------------------
void Logger::setLogLevel(Logger::Level level)
{
    std::lock_guard<std::mutex> lock(mutex_);
    minLevel_ = level;
}

// ------------------------------------------------------------------------------------
bool Logger::setLogFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mutex_);

    // If we were already logging to a file, close it
    if(fileStream_.is_open()) {
        fileStream_.close();
    }

    if(!filename.empty()) {
        fileStream_.open(filename, std::ios::out | std::ios::app);
        if(!fileStream_.is_open()) {
            // Failed to open
            useFile_ = false;
            return false;
        }
        useFile_ = true;
        return true;
    } else {
        // Switch back to console output
        useFile_ = false;
        return true;
    }
}

// ------------------------------------------------------------------------------------
void Logger::debug(const std::string& msg)
{
    logInternal(Level::DEBUG, msg);
}

void Logger::info(const std::string& msg)
{
    logInternal(Level::INFO, msg);
}

void Logger::warn(const std::string& msg)
{
    logInternal(Level::WARN, msg);
}

void Logger::error(const std::string& msg)
{
    logInternal(Level::ERROR, msg);
}

void Logger::critical(const std::string& msg)
{
    logInternal(Level::CRITICAL, msg);
}

// ------------------------------------------------------------------------------------
static std::string levelToString(Logger::Level level)
{
    switch(level)
    {
        case Logger::Level::DEBUG:    return "DEBUG";
        case Logger::Level::INFO:     return "INFO";
        case Logger::Level::WARN:     return "WARN";
        case Logger::Level::ERROR:    return "ERROR";
        case Logger::Level::CRITICAL: return "CRITICAL";
    }
    return "UNKNOWN";
}

// ------------------------------------------------------------------------------------
static std::string currentDateTimeStr()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto timeT = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm buf{};
#if defined(_MSC_VER) || defined(__MINGW32__) 
    localtime_s(&buf, &timeT);
#else
    localtime_r(&timeT, &buf);
#endif

    char timeStr[64];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &buf);

    // Append milliseconds
    char result[80];
    std::snprintf(result, sizeof(result), "%s.%03lld", timeStr, (long long)ms.count());
    return std::string(result);
}

// ------------------------------------------------------------------------------------
void Logger::logInternal(Logger::Level level, const std::string& msg)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(static_cast<int>(level) < static_cast<int>(minLevel_)) {
        return; // below current minimum log level
    }

    // Construct log line: [DATETIME] [LEVEL] message
    std::string output = "[" + currentDateTimeStr() + "]";
    output += " [" + levelToString(level) + "] ";
    output += msg;

    if(useFile_ && fileStream_.is_open()) {
        fileStream_ << output << std::endl;
    } else {
        if(level == Level::ERROR || level == Level::CRITICAL || level == Level::WARN) {
            std::cerr << output << std::endl;
        } else {
            std::cout << output << std::endl;
        }
    }
}
