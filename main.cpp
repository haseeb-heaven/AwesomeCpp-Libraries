/*
Brief: These are Awesome Cpp libraries project under MIT license.
Author: HeavenHM
Coding : C++ 17.
*/

#include "libs/ItemRemover.hpp"    // Used for removing items from containers
#include "libs/NumberSwapper.hpp"  // Used for swapping numbers
#include "libs/Logger.hpp"         // Used for logging program events
#include "libs/TypeResolver.hpp"   // Used for resolving data types
#include "libs/DataConvertor.hpp"  // Used for converting data types
#include "libs/MathOperations.hpp" // Used for performing mathematical operations
#include "libs/FileManager.hpp"    // Used for file management
#include "libs/PrintContainer.hpp" // Used for printing container elements
#include "libs/FileParser.hpp"     // Used for parsing files

std::string setupLogger();     // Function to set up the logger
void NumberSwapperExamples();  // Function to demonstrate number swapping
void ItemRemoverExamples();    // Function to demonstrate item removal from containers
void TypeResolverExamples();   // Function to demonstrate data type resolution
void DataConvertorExamples();  // Function to demonstrate data conversion
void MathOperationsExamples(); // Function to demonstrate mathematical operations
void FileManagerExamples();    // Function to demonstrate file management
void ParserExamples();        // Function to demonstrate file management

int main()
{
    // Setting up the logger
    std::string logFilename = setupLogger();
    Logger logger(logFilename);

    logger.log("Starting the program");

    int choice = -1; // Initialize choice with a non-zero value

    while (choice != 0)
    {
        std::cout << "Select an option:\n"
                  << "1. NumberSwapperExample\n"
                  << "2. ItemRemoverExample\n"
                  << "3. TypeResolverExample\n"
                  << "4. DataConvertorExample\n"
                  << "5. MathOperationsExample\n"
                  << "6. FileManagerExample\n"
                  << "7. ParserExample\n"
                  << "0. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with NumberSwapper     *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            NumberSwapperExamples();
            break;
        case 2:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with ItemRemover       *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            ItemRemoverExamples();
            break;
        case 3:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with TypeResolver      *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            TypeResolverExamples();
            break;
        case 4:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with DataConvertor     *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            DataConvertorExamples();
            break;
        case 5:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with MathOperations    *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            MathOperationsExamples();
            break;
        case 6:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with FileManager       *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            FileManagerExamples();
            break;
        case 7:
            std::cout << "*---------------------------------*\n"
                      << "*  Example with Parser            *\n"
                      << "*---------------------------------*\n"
                      << "*"
                      << std::endl;
            ParserExamples();
            break;
        case 0:
            // remove all logs file recursively from logs and current directory
            std::string removeCommand = "rm " + logFilename + " logs/*.log";
            std::system(removeCommand.c_str());

            std::cout << "Exiting the program\n";
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }

    logger.log("Ending the program");
    return 0;
}

// Function to demonstrate number swapping
void NumberSwapperExamples()
{
    NumberSwapper<int> intSwapper;
    int first = 10, second = 20;
    intSwapper.swap(first, second);
    std::cout << "Swapped numbers: " << first << " and " << second << std::endl;

    NumberSwapper<double> doubleSwapper;
    double x = 3.14, y = 2.71;
    doubleSwapper.swap(x, y);
    std::cout << "Swapped numbers: " << x << " and " << y << std::endl;

    NumberSwapper<char> charSwapper;
    char c1 = 'A', c2 = 'B';
    charSwapper.swap(c1, c2);
    std::cout << "Swapped characters: '" << c1 << "' and '" << c2 << "'" << std::endl;
}

// Function to demonstrate item removal from containers
void ItemRemoverExamples()
{
    ItemRemover<std::vector<float>> vectorRemover;
    ItemRemover<std::list<int>> listRemover;
    ItemRemover<std::set<double>> setRemover;
    ItemRemover<std::map<int, std::string>> mapRemover;

    // Example with std::vector
    std::vector<float> vector1 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    std::cout << "Input vector: ";
    printContainer(vector1);
    vectorRemover.removeNthElement(vector1, 3); // Remove the 3rd element from vector
    std::cout << "Output vector: ";
    printContainer(vector1);

    // Example with std::list
    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::cout << "Input list: ";
    printContainer(list1);
    listRemover.removeNthElement(list1, 3); // Remove the 3rd element from list
    std::cout << "Output list: ";
    printContainer(list1);

    // Example with std::set
    std::set<double> set1 = {99.5, 33.4, 55.6, 77.7, 11.1};
    std::cout << "Input set: ";
    printContainer(set1);
    setRemover.removeNthElement(set1, 3); // Remove the 3rd element from set
    std::cout << "Output set: ";
    printContainer(set1);

    // Example with std::map
    std::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
    std::cout << "Input map: ";
    printContainer(map1);
    mapRemover.removeNthElement(map1, 1); // Remove the 1st element from map
    std::cout << "Output map: ";
    printContainer(map1);
}

// Function to demonstrate data type resolution
void TypeResolverExamples()
{
    TypeResolver typeResolver;
    // Dynamic resolution.
    std::map<int, int> iMap;
    std::cout << "Input data: ";
    printContainer(iMap);
    std::cout << "Resolved data type: ";
    typeResolver.resolveDataType(iMap);

    std::vector<double> doubleVector;
    std::cout << "Input data: ";
    printContainer(doubleVector);
    std::cout << "Resolved data type: ";
    typeResolver.resolveDataType(doubleVector);

    // Compile type resolution.
    std::cout << "Resolved data type: " << TypeResolver::resolveDataType<std::vector<float>>() << std::endl;
    std::cout << "Resolved data type: " << TypeResolver::resolveDataType<std::set<int>>() << std::endl;
    std::cout << "Resolved data type: " << TypeResolver::resolveDataType<std::map<std::string, double>>() << std::endl;
}

// Function to demonstrate data conversion
void DataConvertorExamples()
{
    DataConvertor converter;

    // Example 1: String to Int
    std::string strInput = "123";
    auto intResult = converter.convert<std::string, int>(strInput);
    if (intResult)
        std::cout << "Input: " << strInput << ", Converted to Int: " << *intResult << std::endl;

    // Example 2: Double to Char
    double doubleInput = 65.0;
    auto charResult = converter.convert<double, char>(doubleInput);
    if (charResult)
        std::cout << "Input: " << doubleInput << ", Converted to Char: " << *charResult << std::endl;

    // Example 3: Char to Float
    char charInput = 'A';
    auto floatResult = converter.convert<char, float>(charInput);
    if (floatResult)
        std::cout << "Input: " << charInput << ", Converted to Float: " << *floatResult << std::endl;

    // Example 4: String to Double
    std::string doubleInputStr = "3.14159";
    auto doubleResult = converter.convert<std::string, double>(doubleInputStr);
    if (doubleResult)
        std::cout << "Input: " << doubleInputStr << ", Converted to Double: " << *doubleResult << std::endl;
}

// Function to demonstrate mathematical operations
void MathOperationsExamples()
{
    // Create matrices for demonstration
    std::vector<std::vector<double>> matrixA = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> matrixB = {{5, 6}, {7, 8}};

    try
    {
        // Perform matrix addition
        auto sumMatrix = MathOperations::addMatrices(matrixA, matrixB);
        std::cout << "Sum Matrix:" << std::endl;
        for (const auto &row : sumMatrix)
        {
            for (const auto &elem : row)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }

        // Perform matrix subtraction
        auto diffMatrix = MathOperations::subtractMatrices(matrixA, matrixB);
        std::cout << "Difference Matrix:" << std::endl;
        for (const auto &row : diffMatrix)
        {
            for (const auto &elem : row)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }

        // Calculate mean of a vector
        std::vector<double> data = {1, 2, 3, 4, 5};
        std::cout << "Input Data: ";
        for (const auto &num : data)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        double dataMean = MathOperations::mean(data);
        std::cout << "Mean of Input Data: " << dataMean << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to demonstrate file management
void FileManagerExamples()
{
    FileManager fileManager;
    std::string filename = "demo_file.txt";

    // Example 1: Create a file
    fileManager.createFile(filename);

    // Example 2: Write to the file
    std::string message = "Hello, world!";
    fileManager.updateFile(filename, message);
    std::cout << "Successfully wrote \"" << message << "\" to " << filename << std::endl;

    // Example 3: Read from the file
    std::string content = fileManager.readFile(filename);
    std::cout << "Content of " << filename << ": " << content << std::endl;

    // Example 4: Delete the file
    fileManager.deleteFile(filename);
    std::cout << "Successfully deleted " << filename << std::endl;
}

void ParserExamples() {
    try {
        FileParser parser;
        std::string jsonPath = "data/jsonfile.json";
        std::string csvPath = "data/csvfile.csv";
        std::string xmlPath = "data/xmlfile.xml";

        std::string jsonData = parser.parseJSON(jsonPath);
        std::string csvData = parser.parseCSV(csvPath);
        std::string xmlData = parser.parseXML(xmlPath);

        parser.writeToFile("data/output.txt");
    
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


// Function to set up the logger
std::string setupLogger()
{
    std::string currentFile = __FILE__;
    std::string::size_type pos = currentFile.find_last_of("/\\");
    std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
    return Logger::getLogsFilename(fileName);
}