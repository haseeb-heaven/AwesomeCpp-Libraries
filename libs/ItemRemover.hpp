#ifndef ITEM_REMOVER_HPP
#define ITEM_REMOVER_HPP

#include <iostream>           // For input/output operations
#include <list>               // For doubly-linked list container
#include <vector>             // For dynamic array container
#include <array>              // For fixed-size array container
#include <set>                // For sorted set container
#include <map>                // For associative array container
#include <stack>              // For stack container
#include <queue>              // For queue container
#include <string>             // For string operations
#include <algorithm>          // For algorithms like sort, find, etc.
#include <iterator>           // For iterator operations
#include <numeric>            // For numeric algorithms like accumulate, etc.
#include <functional>         // For function objects and binders
#include <chrono>             // For time-related operations
#include <fstream>            // For file input/output operations
#include "PrintContainer.hpp" // Custom header for printing container elements
#include "Logger.hpp"         // Custom header for logging messages to a file

// Class template to remove the nth element from a container
template <typename Container>
class ItemRemover
{
private:
    Logger logger;

public:
    ItemRemover()
        : logger([]()
                 {
        std::string currentFile = __FILE__;
        std::string::size_type pos = currentFile.find_last_of("/");

        // Extract the file name without the extension
        std::string fileName = currentFile.substr(pos + 1, currentFile.rfind(".") - pos - 1);
        std::string logFilename = Logger::getLogsFilename(fileName);
        return logFilename; }())
    {
    }

    void removeNthElement(Container &container, typename Container::size_type index)
    {
        index = index - 1; // Adjust the index to account for 0-based indexing
        addLog("Removing nth element from container with index: " + std::to_string(index));
        if constexpr (std::is_same_v<Container, std::stack<typename Container::value_type>> || std::is_same_v<Container, std::queue<typename Container::value_type>>)
        {
            Container temp1, temp2;
            typename Container::size_type size = container.size();
            for (typename Container::size_type idx = 0; idx < size; ++idx)
            {
                if (idx != index)
                {
                    temp1.push(container.top());
                }
                container.pop();
            }
            // Push the elements from temp1 to temp2
            while (!temp1.empty())
            {
                temp2.push(temp1.top());
                temp1.pop();
            }
            // Push the elements from temp2 back to the original container
            while (!temp2.empty())
            {
                container.push(temp2.top());
                temp2.pop();
            }
        }
        // For other containers, use the erase method
        else
        {
            if (index < container.size())
            {
                auto it = std::next(container.begin(), index);
                container.erase(it);
            }
            else
            {
                addLog("Invalid index!");
                std::cout << "Invalid index!" << std::endl;
            }
        }
    }

private:
    void addLog(const std::string &message)
    {
        logger.log(message);
    }
};

#endif // ITEM_REMOVER_HPP