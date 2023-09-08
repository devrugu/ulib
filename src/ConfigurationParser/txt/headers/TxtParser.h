#ifndef TXTPARSER_H
#define TXTPARSER_H

#include "../../../headers/AllHeaders.h"

struct Variable
{
    std::string name;
    std::string type;
    std::string value;
};

class TxtParser {
public:
    std::string trim(const std::string& str);
    std::vector<Variable> ParseTxt(std::string content);
};

#endif  // TXTPARSER_H
