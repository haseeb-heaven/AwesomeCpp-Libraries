#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Logger.hpp"
#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <system_error>  // For std::system_error

/**
 * @brief The FileManager class provides functionality to create, read, update, and delete files.
 */
class FileManager {
    Logger logger; // Logger object for logging file operations

public:
    /**
     * @brief Constructs a FileManager object.
     * The logger is initialized with the logs filename based on the current file's name.
     */
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

    /**
     * @brief Creates a new file at the specified path.
     * 
     * @param path The path of the file to create.
     * @throws std::runtime_error if the file already exists or fails to create.
     */
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

    /**
     * @brief Reads the content of the file at the specified path.
     * 
     * @param path The path of the file to read.
     * @return The content of the file as a string.
     * @throws std::runtime_error if the file does not exist or fails to open for reading.
     */
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

    /**
     * @brief Updates the content of the file at the specified path.
     * 
     * @param path The path of the file to update.
     * @param content The new content to write to the file.
     * @throws std::runtime_error if the file does not exist or fails to open for updating.
     */
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

    /**
     * @brief Deletes the file at the specified path.
     * 
     * @param path The path of the file to delete.
     * @throws std::system_error if the file fails to delete.
     */
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
