#ifndef XMLCONFIGPROCESSOR_H
#define XMLCONFIGPROCESSOR_H

#include "../../interfaces/IConfigProcessor.h"

class XmlConfigProcessor : public IConfigProcessor
{
private:
public:
    virtual ~XmlConfigProcessor() = default;
    std::map<std::string, std::string> ParseConfig(const std::string& filePath) override;
};

#endif // XMLCONFIGPROCESSOR_H
