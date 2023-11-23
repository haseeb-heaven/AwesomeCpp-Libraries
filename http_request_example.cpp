/*
Description: This is an example of how to use the HttpClient.
This show how to send a GET request to a URL and save the response to a file.
and how to parse the response file based on the file type.

Note:
This code requires the curl library to run.
To compile and run, use the following command:
g++ -std=c++17 file.cpp -lcurl -o file && ./file
*/
#include "libs/HttpClient.hpp"
#include "libs/FileParser.hpp"
#include "libs/FileManager.hpp"
#include "libs/Logger.hpp"

void sendUrlRequest(const std::string& url);
std::string setupLogger();
void removeLogs();

// Setting up the logger
Logger logger("http_request_example.log");

int main(int argc, char* argv[]) {

    logger.log("Starting the program");

    std::string url;
    std::cout << "URL: ";
    std::cin >> url;

    sendUrlRequest(url);
    logger.log("Program finished");

    removeLogs(); // Remove the logs

    return 0;
}

/**
 * Sends a URL request.
 *
 * @param url The URL to send the request to.
 */
void sendUrlRequest(const std::string& url) {
    HttpClient httpClient; // HTTP client object
    FileManager fileManager; // File manager object
    FileParser fileParser; // File parser object

    try {
        // Example GET request
        std::string response = httpClient.getRequest(url);
        logger.log("GET Response: \n" + response);
        std::string outputResponseFile = "response.txt";

        // Save the file Response to a file
        fileManager.createFile(outputResponseFile);
        fileManager.updateFile(outputResponseFile, response);

        // Store the parsed data.
        std::map<std::string,std::string> parsedData;

        // Determine the file type based on the URL and Parse the file based on the determined file type
        std::string fileType;
        if (url.find(".json") != std::string::npos) {
            parsedData = fileParser.parseJSON(outputResponseFile);
        } else if (url.find(".xml") != std::string::npos) {
            parsedData = fileParser.parseXML(outputResponseFile);
        } else if (url.find(".csv") != std::string::npos) {
            parsedData = fileParser.parseCSV(outputResponseFile);
        } else {
            parsedData = fileParser.parseJSON(outputResponseFile);
            return;
        }
        
        // Now dynamically accessing the parsed data
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