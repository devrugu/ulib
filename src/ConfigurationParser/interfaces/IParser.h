#ifndef IPARSER_H
#define IPARSER_H

#include "../../headers/AllHeaders.h"

class IParser
{
public:
    virtual ~IParser() = default;
    virtual std::map<std::string, std::string> Parse(QDomDocument doc) = 0;
};

#endif // IPARSER_H
