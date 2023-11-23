#include "libs/HttpClient.hpp"
#include "libs/FileParser.hpp"
#include "libs/FileManager.hpp"
#include "libs/Logger.hpp"


void HttpRequestExamples(const std::string& url);
std::string setupLogger();
void removeLogs();

Logger logger("HttpRequest.log");

int main(int argc, char* argv[]) {
    // Setting up the logger
    logger.log("Starting the program");

    std::string url;
    std::cout << "Http URL: ";
    std::cin >> url;

    HttpRequestExamples(url);
    logger.log("Program finished");

    return 0;
}


// This code requires the curl library to run.
// To compile and run, use the following command:
// g++ -std=c++17 file.cpp -lcurl -o file && ./file

void HttpRequestExamples(const std::string& url) {
    HttpClient httpClient; // HTTP client object
    FileManager fileManager; // File manager object
    FileParser fileParser; // File parser object

    try {
        // Example GET request
        std::string response = httpClient.getRequest(url);
        logger.log("GET Response: \n" + response);
        std::string outputResponseFile = "response.txt";

        // Save the file Response to a file
        // check file exists
        
        if (std::filesystem::exists(outputResponseFile)) {
            fileManager.deleteFile(outputResponseFile);
        }

        fileManager.createFile(outputResponseFile);
        fileManager.updateFile(outputResponseFile, response);

        // Parse the JSON response.
        auto parsedData = fileParser.parseJSON(outputResponseFile);

        // Now accessing the parsed data
        logger.log("Parsed Data:");
        for (const auto& [key, value] : parsedData) {
            std::cout << (key + ": " + value) << std::endl;
        }
        logger.log("Parsed Data End");
        // Delete the file
        fileManager.deleteFile(outputResponseFile);
    } catch (const std::exception& e) {
        logger.error("An error occurred: " + std::string(e.what()));
    }
}


// Function to set up the logger
std::string setupLogger()
{
    std::string currentFile = __FILE__;
    std::string::size_type pos = currentFile.find_last_of("/\\");
    std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
    // if logs directory does not exist, create it
    if (!std::filesystem::exists("logs")) {
        std::filesystem::create_directory("logs");
    }
    return logger.getLogsFilename(fileName);
}

void removeLogs() {
    std::filesystem::path currentDir = std::filesystem::current_path();
    for (const auto& entry : std::filesystem::recursive_directory_iterator(currentDir)) {
        if (entry.path().extension() == ".log") {
            std::filesystem::remove(entry.path());
        }
    }
}