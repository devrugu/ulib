#ifndef ICONFIGPROCESSOR_H
#define ICONFIGPROCESSOR_H

#include <string>
#include <map>

class IConfigProcessor
{
public:
    virtual ~IConfigProcessor() = default;
    virtual std::map<std::string, std::string> ParseConfig(const std::string& filePath) = 0;
};

#endif // ICONFIGPROCESSOR_H
