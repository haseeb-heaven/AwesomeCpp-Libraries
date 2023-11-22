// EventHandlingSystem.hpp
#ifndef EVENTHANDLINGSYSTEM_HPP
#define EVENTHANDLINGSYSTEM_HPP

#include "Logger.hpp"
#include <functional>
#include <map>
#include <string>
#include <stdexcept>

class EventHandlingSystem {
    Logger logger;
    std::map<std::string, std::function<void()>> eventMap;

public:
    EventHandlingSystem()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            std::string logFilename = Logger::getLogsFilename(fileName);
            return logFilename;
        }())
    {
        logger.log("FileSystemWatcher instance created");
    }

    void registerEvent(const std::string& eventName, std::function<void()> callback) {
        eventMap[eventName] = callback;
        logger.log("Event registered: " + eventName);
    }

    void triggerEvent(const std::string& eventName) {
        if (eventMap.find(eventName) == eventMap.end()) {
            logger.log("Event not found: " + eventName);
            throw std::runtime_error("Event not registered");
        }
        eventMap[eventName](); // Call the callback function
        logger.log("Event triggered: " + eventName);
    }
};

#endif // EVENTHANDLINGSYSTEM_HPP
