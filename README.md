# C++ Awesome Libraries Project

## Features ✨
- **DataConvertor**: Convert various data types. 🔄
- **DataParser**: Parse data from strings (JSON, CSV, etc.). 📝
- **HttpClient**: Send HTTP requests with GET, POST, PUT, and DELETE methods. 🌐
- **EventHandlingSystem**: Manage and dispatch events. 🎉
- **FileManager**: Perform CRUD operations on files with robust error handling. 📁
- **FileSystemWatcher**: Monitor file system changes. 🔍
- **ItemRemover**: Remove items from data structures. 🗑️
- **MathOperations**: Perform mathematical calculations and matrix operations. ➕➖✖️
- **NumberSwapper**: Swap numbers in various data types. ↔️
- **PrintContainer**: Print contents of containers. 📄
- **TypeResolver**: Resolve data types. 🔄

## Installation 🛠️
Clone the repository:
- `git clone https://github.com/haseeb-heaven/AwesomeCpp-Libraries`
- `cd AwesomeCpp-Libraries`
open main.cpp and run the program
### Dependencies - Curl for Http Client.
- Http Client module requires cURL to be installed on your system. You can download cURL from [here](https://curl.se/download.html) and follow the instructions to install it on your system.
- for MacOs users, you can install cURL using Homebrew by running the following command in your terminal:
- `brew install curl`
- for Linux users, you can install cURL using apt-get by running the following command in your terminal:
- `sudo apt-get install curl`
- for Windows users, you can download cURL from [here](https://curl.se/windows/) and follow the instructions to install it on your system.


## Usage 🚀
- Include the required header files in your C++ source files. For example:
- #include "libs/MathOperations.hpp"
- #include "libs/FileManager.hpp"

## Examples 📚
- **MathOperations**: Perform matrix addition, subtraction, and calculate the mean of numbers. ➕➖🔢
- **FileManager**: Create, read, update, and delete files safely with extensive error handling. 📁✏️❌
- **File Parser**: Parse data from a CSV,JSON,XML file. 📝

## Settings 🔧
Configure each module as needed. Refer to individual header files for module-specific settings.

## Structure 🏗️
- `libs/`: Contains all the header files for the different modules.
- [HttpClient.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/HttpClient.hpp): - Header file for the HttpClient module **(requires cURL)** and see example usage in [http_request_example.cpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/http_request_example.cpp)

- [FileManager.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileManager.hpp) - Header file for the FileManager module.
- [DataConvertor.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/DataConvertor.hpp) - Header file for the DataConvertor module.
- [DataParser.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/DataParser.hpp) - Header file for the DataParser module.
- [EventHandlingSystem.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/EventHandlingSystem.hpp) - Header file for the EventHandlingSystem module.
- [FileParser.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileParser.hpp) - Header file for the FileParser module.
- [FileSystemWatcher.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileSystemWatcher.hpp) - Header file for the FileSystemWatcher module.
- [ItemRemover.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/ItemRemover.hpp) - Header file for the ItemRemover module.
- [MathOperations.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/MathOperations.hpp) - Header file for the MathOperations module.
- [NumberSwapper.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/NumberSwapper.hpp) - Header file for the NumberSwapper module.
- [PrintContainer.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/PrintContainer.hpp) - Header file for the PrintContainer module.
- [TypeResolver.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/TypeResolver.hpp) - Header file for the TypeResolver module.
- [Logger.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/Logger.hpp) - Header file for the Logger module.

- `main.cpp`: Example usage of the libraries.

## Contributing 🤝
Contributions are welcome! Please feel free to submit pull requests or open issues.

## Versioning 🏷️
For the versions available, see the tags on this repository.

## License 📜
This project is licensed under the [MIT LICENSE] - see the LICENSE file for details.
