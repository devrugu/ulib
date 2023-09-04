#ifndef TXTPARSER_H
#define TXTPARSER_H

#include "../../../headers/AllHeaders.h"

class TxtParser {
public:
    static std::unordered_map<std::string, std::pair<std::string, std::string>> parse(const std::vector<std::string>& lines);
};

#endif  // TXTPARSER_H
