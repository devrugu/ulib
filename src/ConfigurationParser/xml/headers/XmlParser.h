#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "../../interfaces/IParser.h"

class XmlParser : public IParser
{
public:
    virtual ~XmlParser() = default;
    void traverseAndParseNode(const QDomNode& node, std::map<std::string, std::string>& result, const std::string& parentPath = "");
    std::map<std::string, std::string> Parse(QDomDocument doc) override;
};

#endif // XMLPARSER_H
