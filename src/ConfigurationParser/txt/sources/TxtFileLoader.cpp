#include "../headers/TxtFileLoader.h"

#include <stdexcept>
#include <fstream>

std::string TxtFileLoader::LoadTxt(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}
