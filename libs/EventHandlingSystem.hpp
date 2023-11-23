// EventHandlingSystem.hpp

#ifndef EVENTHANDLINGSYSTEM_HPP
#define EVENTHANDLINGSYSTEM_HPP

#include "Logger.hpp"
#include <functional>
#include <map>
#include <string>
#include <stdexcept>

/**
 * @brief The EventHandlingSystem class handles event registration and triggering.
 */
class EventHandlingSystem {
    Logger logger; // Logger instance for logging events
    std::map<std::string, std::function<void()>> eventMap; // Map to store event names and their corresponding callback functions

public:
    /**
     * @brief Constructs an EventHandlingSystem object.
     * Initializes the logger and logs the creation of the object.
     */
    EventHandlingSystem()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            std::string logFilename = Logger::getLogsFilename(fileName);
            return logFilename;
        }())
    {
        logger.log("EventHandlingSystem instance created");
    }

    /**
     * @brief Registers an event with a callback function.
     * @param eventName The name of the event to be registered.
     * @param callback The callback function to be called when the event is triggered.
     */
    void registerEvent(const std::string& eventName, std::function<void()> callback) {
        eventMap[eventName] = callback;
        logger.log("Event registered: " + eventName);
    }

    /**
     * @brief Triggers an event by calling its callback function.
     * @param eventName The name of the event to be triggered.
     * @throws std::runtime_error if the event is not registered.
     */
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
