#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    enum class Level { DEBUG, INFO, WARNING, ERROR, FATAL };

    Logger(const std::string &logFile = "sportpulse.log") {
        logStream.open(logFile, std::ios::app);
    }

    ~Logger() {
        if (logStream.is_open())
            logStream.close();
    }

    virtual void log(Level level, const std::string &message) {
        std::lock_guard<std::mutex> lock(mutex);
        std::string levelStr;
        switch (level) {
            case Level::DEBUG: levelStr = "DEBUG"; break;
            case Level::INFO: levelStr = "INFO"; break;
            case Level::WARNING: levelStr = "WARNING"; break;
            case Level::ERROR: levelStr = "ERROR"; break;
            case Level::FATAL: levelStr = "FATAL"; break;
        }

        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%F %T");
        std::string timestamp = ss.str();

        std::string logEntry = "{\"timestamp\":\"" + timestamp + "\",\"level\":\"" + levelStr + "\",\"message\":\"" + message + "\"}";

        std::cout << logEntry << std::endl;

        if (logStream.is_open()) {
            logStream << logEntry << std::endl;
        }
    }

private:
    std::ofstream logStream;
    std::mutex mutex;
};

#endif // LOGGER_H
