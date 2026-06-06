#ifndef OOP5_LOGGER_H
#define OOP5_LOGGER_H
#include <iostream>
#include <ostream>
#include <string>

class Logger {
public:
    static Logger& instance() {
        static Logger logger;
        return logger;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

    void error(const std::string& message) {
        std::cout << "[ERROR] " << message << std::endl;
    }
private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

#endif //OOP5_LOGGER_H
