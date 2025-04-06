#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger {
public:

    enum class Level { DEBUG, INFO, WARNING, ERROR, FATAL };

    virtual void log(Level level, const std::string &message) = 0;
};

#endif // ILOGGER_H