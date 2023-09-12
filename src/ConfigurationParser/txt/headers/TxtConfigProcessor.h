#ifndef TXTCONFIGPROCESSOR_H
#define TXTCONFIGPROCESSOR_H

#include <any>
#include <string>
#include <unordered_map>

class TxtConfigProcessor{
public:
    std::unordered_map<std::string, std::any> ParseConfigTxt(const std::string& filepath);
private:
};

#endif
