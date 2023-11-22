/*
Info: C++ General way of printing data of container including List, Sets, Maps, Stack, Queues, etc.
Author: Haseeb Mir @2022.
*/

#include <iostream> // For input/output operations
#include <map> // For std::map
#include <stack> // For std::stack
#include <queue> // For std::queue

/**
 * @brief Template struct to check if a type is a map.
 * 
 * @tparam T The type to check.
 */
template <class T>
struct is_map
{
    static constexpr bool value = false;
};

/**
 * @brief Template specialization for std::map.
 * 
 * @tparam Key The key type of the map.
 * @tparam Value The value type of the map.
 */
template <class Key, class Value>
struct is_map<std::map<Key, Value>>
{
    static constexpr bool value = true;
};

/**
 * @brief Template struct to check if a type is a stack.
 * 
 * @tparam T The type to check.
 */
template <class T>
struct is_stack
{
    static constexpr bool value = false;
};

/**
 * @brief Template specialization for std::stack.
 * 
 * @tparam T The type of the stack.
 */
template <class T>
struct is_stack<std::stack<T>>
{
    static constexpr bool value = true;
};

/**
 * @brief Template struct to check if a type is a queue.
 * 
 * @tparam T The type to check.
 */
template <class T>
struct is_queue
{
    static constexpr bool value = false;
};

/**
 * @brief Template specialization for std::queue.
 * 
 * @tparam T The type of the queue.
 */
template <class T>
struct is_queue<std::queue<T>>
{
    static constexpr bool value = true;
};


/**
 * @brief Prints the elements of a container.
 * 
 * This function prints the elements of a container to the standard output.
 * If the container is empty, it prints a message indicating that the container is empty.
 * The elements are printed with a specified delimiter between them.
 * 
 * @tparam T The type of the container.
 * @param container The container to be printed.
 * @param delimiter The delimiter to be used between elements. Default is "\t".
 */
template <typename T>
void printContainer(const T& container, const std::string& delimiter = "\t") {
    // Check if the container is empty
    if (container.empty()) {
        std::cout << "Container is empty." << std::endl;
        return;
    }

    // Container for Map.
    if constexpr (is_map<T>::value) {
        for (const auto &[k, v] : container) {
            std::cout << k << delimiter << v << std::endl;
        }
    }
    // Container for Stack & Queue.
    else if constexpr (is_stack<T>::value || is_queue<T>::value) {
        T copy = container;
        while (!copy.empty()) {
            if constexpr (is_stack<T>::value)
                std::cout << copy.top() << delimiter;
            else if constexpr (is_queue<T>::value)
                std::cout << copy.front() << delimiter;
            copy.pop();
        }
        std::cout << std::endl;
    }
    // General Container like list, set, etc.
    else {
        for (const auto &data : container) {
            if constexpr (!is_map<T>::value)
                std::cout << data << delimiter;
        }
        std::cout << std::endl;
    }
}