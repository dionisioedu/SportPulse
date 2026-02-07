#include "utils/ILogger.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    ~FakeLogger() = default;

    void log(Level level, const std::string& message) override {
        logs.push_back("LOG: " + message);
    }
    void debug(const std::string& message) override {
        logs.push_back("DEBUG: " + message);
    }
    void info(const std::string& message) override {
        logs.push_back("INFO: " + message);
    }
    void warning(const std::string& message) override {
        logs.push_back("WARNING: " + message);
    }
    void error(const std::string& message) override {
        logs.push_back("ERROR: " + message);
    }
    void fatal(const std::string& message) override {
        logs.push_back("FATAL: " + message);
    }
};
