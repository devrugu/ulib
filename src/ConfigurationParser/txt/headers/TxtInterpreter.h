#ifndef TXTINTERPRETER_H
#define TXTINTERPRETER_H

#include "../../../headers/AllHeaders.h"

using ConfigVariant = std::variant<int, double, std::string, std::vector<int>, std::vector<std::vector<double>>>;

class TxtInterpreter {
public:
    static std::unordered_map<std::string, ConfigVariant> interpret(const std::unordered_map<std::string, std::pair<std::string, std::string>>& parsedData);
};

#endif  // TXTINTERPRETER_H
