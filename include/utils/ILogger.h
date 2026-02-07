#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger {
public:

    virtual ~ILogger() = default;

    enum class Level { DEBUG, INFO, WARNING, ERROR, FATAL };

    virtual void log(Level level, const std::string &message) = 0;
    virtual void debug(const std::string &message) = 0;
    virtual void info(const std::string &message) = 0;
    virtual void warning(const std::string &message) = 0;
    virtual void error(const std::string &message) = 0;
    virtual void fatal(const std::string &message) = 0;
};

#endif // ILOGGER_H