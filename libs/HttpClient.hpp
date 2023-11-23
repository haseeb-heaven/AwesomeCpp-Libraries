#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

/*
- This code requires the curl library to run.
- To compile and run, use the following command:
- g++ -std=c++17 file.cpp -lcurl -o file && ./file
*/


#include <iostream> // Include the iostream library for input/output operations
#include <string> // Include the string library for string manipulation
#include <curl/curl.h> // Include the curl library for making HTTP requests
#include "Logger.hpp" // Include the Logger header file for logging events


/**
 * @brief The HttpClient class provides methods for making HTTP requests.
 */
class HttpClient {
    Logger logger; // Logger instance for logging events

public:
    /**
     * @brief Constructs an HttpClient object.
     * 
     * Initializes the logger and the CURL library.
     */
    HttpClient()
        : logger([]() {
            std::string currentFile = __FILE__;
            std::string::size_type pos = currentFile.find_last_of("/\\");
            std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
            std::string logFilename = Logger::getLogsFilename(fileName);
            return logFilename;
        }())
    {
        curl = curl_easy_init();
        logger.log("HttpClient instance created");
    }

    /**
     * @brief Destructs the HttpClient object.
     * 
     * Cleans up the CURL library resources.
     */
    ~HttpClient() {
        if (curl) {
            curl_easy_cleanup(curl);
        }
    }

    /**
     * @brief Sends a GET request to the specified URL.
     * 
     * @param url The URL to send the request to.
     * @return The response received from the server.
     */
    std::string getRequest(const std::string& url) {
        logger.log("Sending GET request to " + url);
        return performRequest(url, "GET");
    }

    /**
     * @brief Sends a POST request to the specified URL with the given data.
     * 
     * @param url The URL to send the request to.
     * @param postData The data to include in the request body.
     * @return The response received from the server.
     */
    std::string postRequest(const std::string& url, const std::string& postData) {
        logger.log("Sending POST request to " + url);
        return performRequest(url, "POST", postData);
    }

    /**
     * @brief Sends a DELETE request to the specified URL.
     * 
     * @param url The URL to send the request to.
     * @return The response received from the server.
     */
    std::string deleteRequest(const std::string& url) {
        logger.log("Sending DELETE request to " + url);
        return performRequest(url, "DELETE");
    }

private:
    CURL* curl; // CURL handle for making HTTP requests

    /**
     * @brief Callback function for writing response data.
     * 
     * @param contents Pointer to the response data.
     * @param size Size of each element in the response data.
     * @param nmemb Number of elements in the response data.
     * @param s Pointer to the string object to store the response.
     * @return The total number of bytes written.
     */
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
        size_t newLength = size * nmemb;
        try {
            s->append((char*)contents, newLength);
            return newLength;
        } catch(std::bad_alloc& e) {
            // Handle memory allocation errors
            return 0;
        }
    }

    /**
     * @brief Performs an HTTP request to the specified URL with the given method and data.
     * 
     * @param url The URL to send the request to.
     * @param method The HTTP method to use (e.g., GET, POST, DELETE).
     * @param data The data to include in the request body (for POST requests).
     * @return The response received from the server.
     */
    std::string performRequest(const std::string& url, const std::string& method, const std::string& data = "") {
        std::string response;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            if (method == "POST") {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            } else if (method == "DELETE") {
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            }

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                logger.log("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
            } else {
                logger.log("HTTP request performed successfully.");
            }
        }
        return response;
    }
};

#endif // HTTP_CLIENT_HPP