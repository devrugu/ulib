#include "../headers/TxtInterpreter.h"

std::unordered_map<std::string, ConfigVariant> TxtInterpreter::interpret(const std::unordered_map<std::string, std::pair<std::string, std::string>>& parsedData) {
    std::unordered_map<std::string, ConfigVariant> data;

    for (const auto& [key, typeValue] : parsedData) {
        const auto& [type, value] = typeValue;

        std::istringstream iss(value);

        if (type == "int") {
            int intValue;
            iss >> intValue;
            data[key] = intValue;
        }
        else if (type == "double") {
            double doubleValue;
            iss >> doubleValue;
            data[key] = doubleValue;
        }
        else if (type == "string") {
            data[key] = value;
        }
        // Add more types as necessary
    }

    return data;
}

