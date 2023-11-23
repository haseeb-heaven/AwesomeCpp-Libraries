#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "libs/Logger.hpp"

class FileParser {
    Logger logger; // Logger instance for logging events
public:

    FileParser()
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

    std::string parseJSON(const std::string& filepath) {
        try {
            std::string jsonData = readFile(filepath);
            std::regex jsonRegex("\"([^\"]+)\":\\s*\"([^\"]*)\"");
            std::smatch jsonMatch;

            while (std::regex_search(jsonData, jsonMatch, jsonRegex)) {
                jsonDataStream << "Key: " << jsonMatch[1] << ", Value: " << jsonMatch[2] << "\n";
                jsonData = jsonMatch.suffix();
            }

            return jsonDataStream.str();
            logger.log("JSON file parsed successfully.");
        } catch (const std::exception& e) {
            logger.log("Error parsing JSON: " + std::string(e.what()));
        }
        return std::string();
    }

    std::string parseCSV(const std::string& filepath) {
        try {
            std::string csvData = readFile(filepath);
            std::istringstream csvStream(csvData);
            std::string line;

            while (std::getline(csvStream, line)) {
                 csvDataStream << parseCSVLine(line);
            }
            
            logger.log("CSV file parsed successfully.");
            return csvDataStream.str();
        } catch (const std::exception& e) {
            logger.log("Error parsing CSV: " + std::string(e.what()));
        }
        return std::string();
    }

    std::string parseXML(const std::string& filepath) {
        try {
            std::string xmlData = readFile(filepath);
            std::regex xmlRegex("<([^>]+)>([^<]*)</\\1>");
            std::smatch xmlMatch;

            while (std::regex_search(xmlData, xmlMatch, xmlRegex)) {
                xmlDataStream << "Tag: " << xmlMatch[1] << ", Value: " << xmlMatch[2] << "\n";
                xmlData = xmlMatch.suffix();
            }
            
            return xmlDataStream.str();
            logger.log("XML file parsed successfully.");
        } catch (const std::exception& e) {
            logger.log("Error parsing XML: " + std::string(e.what()));
        }
        return std::string();
    }

    void writeToFile(const std::string& outputPath) {
        std::ofstream outFile(outputPath);
        if (!outFile.is_open()) {
            throw std::runtime_error("Error opening output file: " + outputPath);
        }

        outFile << "Parsed JSON Data:\n" << jsonDataStream.str() << "\n";
        outFile << "Parsed CSV Data:\n" << csvDataStream.str() << "\n";
        outFile << "Parsed XML Data:\n" << xmlDataStream.str() << "\n";

        logger.log("Data written to file successfully.");
    }

private:
    std::ostringstream jsonDataStream;
    std::ostringstream csvDataStream;
    std::ostringstream xmlDataStream;
    std::ostringstream outputStream;

    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filepath);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::string parseCSVLine(const std::string& line) {
        std::regex csvRegex("(\"[^\"]*(\"\"[^\"]*)*\"|[^,]*)");
        std::stringstream csvDataStream;
        for(std::sregex_iterator it = std::sregex_iterator(line.begin(), line.end(), csvRegex);it != std::sregex_iterator();++it )
        {
            csvDataStream << (*it)[0] << ",";
        }
        csvDataStream << "\n";
        return csvDataStream.str();
    }
};

