#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include <fstream>

// A simple logger with severity levels.
// Thread-safe with a static std::mutex.
class Logger
{
public:
    enum class Level {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    // Set the minimum level to log (anything lower is ignored)
    static void setLogLevel(Level level);

    // Direct logs to a file instead of the console
    // Pass an empty filename to revert to console
    static bool setLogFile(const std::string& filename);

    // Logging methods
    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void critical(const std::string& msg);

private:
    // Helper to actually perform the logging
    static void logInternal(Level level, const std::string& msg);

    // We'll store log level, mutex, and an ofstream if we log to file
    static Level minLevel_;
    static std::mutex mutex_;
    static std::ofstream fileStream_;
    static bool useFile_;
};

#endif // LOGGER_HPP
