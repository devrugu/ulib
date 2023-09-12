#ifndef IPARSER_H
#define IPARSER_H



#include <string>
#include <map>

class QDomDocument;

class IParser
{
public:
    virtual ~IParser() = default;
    virtual std::map<std::string, std::string> Parse(QDomDocument doc) = 0;
};

#endif // IPARSER_H
