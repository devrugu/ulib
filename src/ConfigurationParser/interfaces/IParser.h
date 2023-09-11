#ifndef IPARSER_H
#define IPARSER_H

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

class QDomDocument;

class IParser
{
public:
    virtual ~IParser() = default;
    virtual std::map<std::string, std::string> Parse(QDomDocument doc) = 0;
};

#endif // IPARSER_H
