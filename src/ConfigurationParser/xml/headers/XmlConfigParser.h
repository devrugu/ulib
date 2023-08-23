#ifndef XMLCONFIGPARSER_H
#define XMLCONFIGPARSER_H

#include "../../interfaces/IConfigParser.h"
#include "XmlFileLoader.h"
#include "XmlParser.h"
#include "XmlInterpreter.h"

class XmlConfigParser : public IConfigParser
{
private:
    XmlFileLoader fileLoader;
    XmlParser parser;
public:
    virtual ~XmlConfigParser() = default;
    std::map<std::string, std::string> ParseConfig(const std::string& filePath) override;
};

#endif // XMLCONFIGPARSER_H
