#ifndef ICONFIGPARSER_H
#define ICONFIGPARSER_H

#include <iostream>
#include <map>
#include <string>

class IConfigParser
{
public:
    virtual ~IConfigParser() = default;
    virtual std::map<std::string, std::string> ParseConfig(const std::string& filePath) = 0;
};

#endif // ICONFIGPARSER_H
