#include <filesystem>
#include <thread>
#include <atomic>
#include "Logger.hpp"

/**
 * @brief A class for watching changes in a specified directory.
 */
class FileSystemWatcher {
    Logger logger; // Logger instance for logging events
    std::thread watcherThread; // Thread for watching the directory
    std::atomic<bool> isWatching; // Flag to indicate if the watcher is active

public:
    /**
     * @brief Constructs a FileSystemWatcher object.
     * 
     * Initializes the logger and sets the isWatching flag to false.
     */
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

    /**
     * @brief Destroys the FileSystemWatcher object.
     * 
     * Stops watching the directory if it is currently being watched.
     */
    ~FileSystemWatcher() {
        if (isWatching) {
            stopWatching();
        }
    }

    /**
     * @brief Starts watching the specified directory for file changes.
     * 
     * @param directory The directory to watch.
     */
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

    /**
     * @brief Stops watching the directory.
     */
    void stopWatching() {
        isWatching = false;
        if (watcherThread.joinable()) {
            watcherThread.join();
        }
        logger.log("Stopped watching");
    }

    // Additional methods as needed
};