#include <filesystem>
#include <thread>
#include <atomic>
#include "Logger.hpp"

class FileSystemWatcher {
    Logger logger;
    std::thread watcherThread;
    std::atomic<bool> isWatching;

public:
    FileSystemWatcher()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            std::string logFilename = Logger::getLogsFilename(fileName);
            return logFilename;
        }()), 
          isWatching(false)
    {
        logger.log("FileSystemWatcher instance created");
    }

    ~FileSystemWatcher() {
        if (isWatching) {
            stopWatching();
        }
    }

    void startWatching(const std::string& directory) {
        isWatching = true;
        watcherThread = std::thread([this, directory]() {
            while (isWatching) {
                for (const auto & entry : std::filesystem::directory_iterator(directory)) {
                    logger.log("Found file: " + entry.path().string());
                }
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for a while
            }
        });
        logger.log("Started watching " + directory);
    }

    void stopWatching() {
        isWatching = false;
        if (watcherThread.joinable()) {
            watcherThread.join();
        }
        logger.log("Stopped watching");
    }

    // Additional methods as needed
};