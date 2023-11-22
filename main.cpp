#include "libs/ItemRemover.hpp"
#include "libs/NumberSwapper.hpp"
#include "libs/Logger.hpp"
#include "libs/TypeResolver.hpp"
#include "libs/DataConvertor.hpp"
#include <vector>
#include <iostream>
#include <functional>

std::string setupLogger();
int DataConvertorExamples();

int main()
{
    // Setting up the logger
    std::string logFilename = setupLogger();
    Logger logger(logFilename);

    logger.addLog("Starting the program");

    std::cout << "*---------------------------------*\n"
                 "*  Example with NumberSwapper     *\n"
                 "*---------------------------------*\n"
                 "*"
              << std::endl;

    NumberSwapper<int> intSwapper;
    int first = 10, second = 20;
    intSwapper.swap(first, second);
    std::cout << "Swapped numbers: " << first << ", " << second << std::endl;

    NumberSwapper<double> doubleSwapper;
    double x = 3.14, y = 2.71;
    doubleSwapper.swap(x, y);
    std::cout << "Swapped numbers: " << x << ", " << y << std::endl;

    NumberSwapper<char> charSwapper;
    char c1 = 'A', c2 = 'B';
    charSwapper.swap(c1, c2);
    std::cout << "Swapped characters: " << c1 << ", " << c2 << std::endl;

    std::cout << "*---------------------------------*\n"
                 "*  Example with ItemRemover     *\n"
                 "*---------------------------------*\n"
                 "*"
              << std::endl;

    ItemRemover<std::vector<float>> vectorRemover;
    ItemRemover<std::list<int>> listRemover;
    ItemRemover<std::set<double>> setRemover;
    ItemRemover<std::map<int, std::string>> mapRemover;

    // Example with std::vector
    std::vector<float> vector1 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    vectorRemover.removeNthElement(vector1, 3); // Remove the 3rd element from vector
    printContainer(vector1);
    logger.addLog("Removed nth element from vector1");

    // example with std::list
    std::list<int> list1 = {1, 2, 3, 4, 5};
    listRemover.removeNthElement(list1, 3); // Remove the 3rd element from list
    printContainer(list1);
    logger.addLog("Removed nth element from list1");

    // example with std::set
    std::set<double> set1 = {99.5, 33.4, 55.6, 77.7, 11.1};
    setRemover.removeNthElement(set1, 3); // Remove the 3rd element from set
    printContainer(set1);
    logger.addLog("Removed nth element from set1");

    // example with std::map
    std::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
    mapRemover.removeNthElement(map1, 1); // Remove the 1st element from map
    printContainer(map1);
    logger.addLog("Removed nth element from map1");

    std::cout << "*---------------------------------*\n"
                 "*  Example with TypeResolver     *\n"
                 "*---------------------------------*\n"
                 "*"
              << std::endl;

    TypeResolver typeResolver;
    // Dynamic resolution.
    std::map<int, int> iMap;
    typeResolver.resolveDataType(iMap);

    std::vector<double> doubleVector;
    typeResolver.resolveDataType(doubleVector);
    ;

    // Compile type resolution.
    std::cout << TypeResolver::resolveDataType<std::vector<float>>();
    std::cout << TypeResolver::resolveDataType<std::set<int>>();
    std::cout << TypeResolver::resolveDataType<std::map<std::string, double>>();

    std::cout << "*---------------------------------*\n"
                 "*  Example with DataConvertor     *\n"
                 "*---------------------------------*\n"
                 "*"
              << std::endl;

    // Creating an instance of DataConvertor
    DataConvertorExamples();

    logger.addLog("Ending the program");
    return 0;
}

int DataConvertorExamples()
{
    DataConvertor converter;

    // Example 1: String to Int
    auto intResult = converter.convert<std::string, int>("123");
    if (intResult)
        std::cout << "String to Int: " << *intResult << std::endl;

    // Example 2: Double to Char
    auto charResult = converter.convert<double, char>(65.0);
    if (charResult)
        std::cout << "Double to Char: " << *charResult << std::endl;

    // Example 3: Char to Float
    auto floatResult = converter.convert<char, float>('A');
    if (floatResult)
        std::cout << "Char to Float: " << *floatResult << std::endl;

    // Example 4: String to Double
    auto doubleResult = converter.convert<std::string, double>("3.14159");
    if (doubleResult)
        std::cout << "String to Double: " << *doubleResult << std::endl;

    return 0;
}

std::string setupLogger()
{
    std::string currentFile = __FILE__;
    std::string::size_type pos = currentFile.find_last_of("/\\");
    std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
    return Logger::getLogsFilename(fileName);
}