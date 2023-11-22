#ifndef DATACONVERTOR_HPP
#define DATACONVERTOR_HPP

#include <iostream>
#include <string>
#include <optional>
#include "Logger.hpp"

class DataConvertor {
    Logger logger;

public:
    DataConvertor()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            return Logger::getLogsFilename(fileName);
        }()) {}

    // Unified convert method
    template <typename From, typename To>
    std::optional<To> convert(const From &from) {
        try {
            if constexpr (std::is_same<From, std::string>::value) {
                // Handle string to type conversion
                if constexpr (std::is_same<To, int>::value) {
                    return std::stoi(from);
                } else if constexpr (std::is_same<To, long>::value) {
                    return std::stol(from);
                } else if constexpr (std::is_same<To, float>::value) {
                    return std::stof(from);
                } else if constexpr (std::is_same<To, double>::value) {
                    return std::stod(from);
                } else if constexpr (std::is_same<To, char>::value) {
                    return !from.empty() ? from[0] : throw std::invalid_argument("Empty string");
                } else {
                    throw std::invalid_argument("Unsupported type for string conversion");
                }
            } else if constexpr (std::is_same<To, std::string>::value) {
                // Handle conversion to string
                return std::to_string(from);
            } else {
                // Handle other type conversions
                return static_cast<To>(from);
            }
        } catch (const std::exception &e) {
            logger.addLog("Conversion failed: " + std::string(e.what()));
            return std::nullopt;
        }
    }
};

#endif // DATACONVERTOR_HPP
