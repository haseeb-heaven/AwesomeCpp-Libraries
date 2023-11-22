#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Logger.hpp"
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <system_error>  // For std::system_error

class FileManager {
    Logger logger;

public:
    FileManager() 
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            return Logger::getLogsFilename(fileName);
        }()) 
    {
        logger.log("FileManager instance created");
    }

    void createFile(const std::string& path) {
        if (std::filesystem::exists(path)) {
            throw std::runtime_error("File already exists: " + path);
        }
        std::ofstream file(path);
        if (!file) {
            std::string errMsg = "Failed to create file: " + path;
            logger.log(errMsg);
            throw std::runtime_error(errMsg);
        }
        logger.log("File created: " + path);
    }

    std::string readFile(const std::string& path) {
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error("File does not exist: " + path);
        }
        std::ifstream file(path, std::ios::binary); // Use binary mode to handle all types of file content
        if (!file) {
            std::string errMsg = "Failed to open file for reading: " + path;
            logger.log(errMsg);
            throw std::runtime_error(errMsg);
        }
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        logger.log("File read: " + path);
        return content;
    }

    void updateFile(const std::string& path, const std::string& content) {
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error("File does not exist: " + path);
        }
        std::ofstream file(path, std::ios::out | std::ios::trunc | std::ios::binary); // Use binary mode
        if (!file) {
            std::string errMsg = "Failed to open file for updating: " + path;
            logger.log(errMsg);
            throw std::runtime_error(errMsg);
        }
        file << content;
        logger.log("File updated: " + path);
    }

    void deleteFile(const std::string& path) {
        try {
            if (!std::filesystem::remove(path)) {
                std::string errMsg = "Failed to delete file: " + path;
                logger.log(errMsg);
                throw std::system_error(errno, std::system_category(), errMsg);
            }
        } catch (const std::filesystem::filesystem_error& e) {
            logger.log(std::string("Filesystem error: ") + e.what());
            throw;
        }
        logger.log("File deleted: " + path);
    }
};

#endif // FILEMANAGER_HPP
