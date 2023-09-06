#ifndef TXTPARSER_H
#define TXTPARSER_H

#include "../../../headers/AllHeaders.h"

class TxtParser {
public:
    static std::unordered_map<std::string, std::pair<std::string, std::string>> parse(std::string content);
};

#endif  // TXTPARSER_H
