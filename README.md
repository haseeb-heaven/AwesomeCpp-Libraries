# C++ Awesome Libraries Project

## Features ✨
- **DataConvertor**: Convert various data types. 🔄
- **DataParser**: Parse data from strings (JSON, CSV, etc.). 📝
- **HttpClient**: Send HTTP requests with GET, POST, PUT, and DELETE methods. 🌐
- **ProcessManager**: Manage processes for all major OS (Create,Terminate,etc). 📊
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
## 🏗️ Library Modules

### HttpClient Module
- **[HttpClient.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/HttpClient.hpp)**
  - 🌐 Header file for the HttpClient module
  - 🛠️ Requires cURL for operation
  - 📖 Example usage: [http_request_example.cpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/http_request_example.cpp)

### FileManager Module
- **[FileManager.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileManager.hpp)**
  - 📂 Manages file-related operations

### DataConvertor Module
- **[DataConvertor.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/DataConvertor.hpp)**
  - 🔄 Converts data between different `c++` data types like `string` to `int` and vice versa.

### FileParser Module
- **[FileParser.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileParser.hpp)**
  - 📝 Parses data for various applications for (JSON,CSV,XML) and more.

### ProcessManager Module
- **[ProcessManager.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/ProcessManager.hpp)**
  - 📊 Manages processes within the all major operating systems (Windows, Linux, MacOS).

### EventHandlingSystem Module
- **[EventHandlingSystem.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/EventHandlingSystem.hpp)**
  - 📅 Manages event handling within the application

### FileSystemWatcher Module
- **[FileSystemWatcher.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/FileSystemWatcher.hpp)**
  - 🔍 Monitors file system changes

### ItemRemover Module
- **[ItemRemover.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/ItemRemover.hpp)**
  - 🗑️ Removes items from collections like `Map`, `Vector`, `List`, `Set`, etc.

### MathOperations Module
- **[MathOperations.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/MathOperations.hpp)**
  - ➕ Performs mathematical operations on `Matrix` and `Vector` statstical analysis.

### NumberSwapper Module
- **[NumberSwapper.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/NumberSwapper.hpp)**
  - 🔁 Swaps numbers in data types like `int`, `float`, `double`, `string`, etc.

### PrintContainer Module
- **[PrintContainer.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/PrintContainer.hpp)**
  - 🖨️ Prints container contents like `List`, `Vector`, `Map`, `Set`, etc.

### TypeResolver Module
- **[TypeResolver.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/TypeResolver.hpp)**
  - 🧩 Resolves data types names at compile time and runtime.

### Logger Module
- **[Logger.hpp](https://github.com/haseeb-heaven/AwesomeCpp-Libraries/blob/main/libs/Logger.hpp)**
  - 📜 Handles logging and reporting


## Contributing 🤝
Contributions are welcome! Please feel free to submit pull requests or open issues.

## Versioning 🏷️
For the versions available, see the tags on this repository.

## License 📜
This project is licensed under the [MIT LICENSE] - see the LICENSE file for details.

## Authors 👨‍💻
- **HeavenHM** - [haseeb-heaven](https://github.com/haseeb-heaven)