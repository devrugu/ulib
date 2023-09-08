#ifndef TXTCONFIGPARSER_H
#define TXTCONFIGPARSER_H

#include "../../../headers/AllHeaders.h"
#include "TxtParser.h"
#include "TxtFileLoader.h"
#include "TxtInterpreter.h"

class TxtConfigParser{
public:
    std::unordered_map<std::string, std::any> ParseConfigTxt(const std::string& filepath);
private:
    TxtFileLoader fileLoader;
    TxtParser parser;
    TxtInterpreter interpreter;
};

#endif
