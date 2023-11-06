#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    fs::path directory_path = "./";  // Replace with the actual directory path

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        if (fs::is_directory(entry) ){ //&& entry[0] != '.') {
            std::cout << entry.path().filename() << std::endl;
        } else if (fs::is_regular_file(entry)){ // && entry[0] != '.') {
            std::cout << entry.path().filename() << std::endl;
        }
    }

    return 0;
}

