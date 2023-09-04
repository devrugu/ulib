#include "../headers/TxtParser.h"

std::unordered_map<std::string, std::pair<std::string, std::string>> TxtParser::parse(const std::vector<std::string>& lines) {
    std::unordered_map<std::string, std::pair<std::string, std::string>> data;
    std::string current_key;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "TYPE") {
            iss.ignore(3);
            iss >> data[current_key].first;
        } else if (token == "VALUE") {
            iss.ignore(3);
            std::getline(iss, data[current_key].second);
        } else if (token[0] == '*') {
            current_key = token.substr(1, token.size() - 1);
        }
    }
    return data;
}

