#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Logger.hpp"

/**
 * @brief The FileParser class is responsible for parsing different types of files such as JSON, CSV, and XML.
 */
class FileParser {
    Logger logger; // Logger instance for logging events
public:
    /**
     * @brief Constructs a FileParser object.
     * It initializes the logger instance with a log filename based on the current file name.
     */
    FileParser()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            std::string logFilename = Logger::getLogsFilename(fileName);
            return logFilename;
        }())
    {
        logger.log("FileParser instance created");
    }

    /**
     * @brief Parses a JSON file and returns the parsed data as a string.
     * @param filepath The path to the JSON file.
     * @return The parsed JSON data as a string.
     */
    std::map<std::string, std::string> parseJSON(const std::string& filepath) {
        std::map<std::string, std::string> jsonMap;
        try {
            std::string jsonData = readFile(filepath);
            std::regex jsonRegex("\"([^\"]+)\":\\s*([^,\\n\\r]+)");
            std::smatch jsonMatch;

            while (std::regex_search(jsonData, jsonMatch, jsonRegex)) {
                jsonMap[jsonMatch[1]] = jsonMatch[2];
                jsonData = jsonMatch.suffix();
            }

            logger.log("JSON file parsed successfully.");
        } catch (const std::exception& e) {
            logger.log("Error parsing JSON: " + std::string(e.what()));
        }
        return jsonMap;
    }

    /**
     * @brief Parses a CSV file and returns the parsed data as a string.
     * @param filepath The path to the CSV file.
     * @return The parsed CSV data as a string.
     */
    std::map<std::string, std::string> parseCSV(const std::string& filepath) {
        std::map<std::string, std::string> csvMap;
        try {
            std::string csvData = readFile(filepath);
            std::istringstream csvStream(csvData);
            std::string line;

            while (std::getline(csvStream, line)) {
                std::istringstream lineStream(line);
                std::string key, value;

                if (std::getline(lineStream, key, ',') && std::getline(lineStream, value)) {
                    csvMap[key] = value;
                }
            }
            
            logger.log("CSV file parsed successfully.");
        } catch (const std::exception& e) {
            logger.log("Error parsing CSV: " + std::string(e.what()));
        }
        return csvMap;
    }

    /**
     * @brief Parses an XML file and returns the parsed data as a string.
     * @param filepath The path to the XML file.
     * @return The parsed XML data as a string.
     */
    std::map<std::string, std::string> parseXML(const std::string& filepath) {
        std::map<std::string, std::string> xmlMap;
        try {
            std::string xmlData = readFile(filepath);
            std::regex xmlRegex("<([^>]+)>([^<]*)</\\1>");
            std::smatch xmlMatch;

            while (std::regex_search(xmlData, xmlMatch, xmlRegex)) {
                xmlMap[xmlMatch[1]] = xmlMatch[2];
                xmlData = xmlMatch.suffix();
            }

            logger.log("XML file parsed successfully.");
        } catch (const std::exception& e) {
            logger.log("Error parsing XML: " + std::string(e.what()));
        }
        return xmlMap;
    }

    /**
     * @brief Writes the parsed data to a file.
     * @param outputPath The path to the output file.
     */
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
    std::ostringstream jsonDataStream; // Stream to store parsed JSON data
    std::ostringstream csvDataStream; // Stream to store parsed CSV data
    std::ostringstream xmlDataStream; // Stream to store parsed XML data

    /**
     * @brief Reads the contents of a file and returns it as a string.
     * @param filepath The path to the file.
     * @return The contents of the file as a string.
     */
    std::string readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filepath);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    /**
     * @brief Parses a line of CSV data and returns it as a string.
     * @param line The line of CSV data.
     * @return The parsed CSV line as a string.
     */
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
#endif // FILEPARSER_HPP