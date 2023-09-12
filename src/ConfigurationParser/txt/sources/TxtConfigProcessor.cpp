#include "../headers/TxtConfigProcessor.h"
#include "../headers/TxtParser.h"
#include "../headers/TxtFileLoader.h"
#include "../headers/TxtInterpreter.h"

#include <memory>

std::unordered_map<std::string, std::any> TxtConfigProcessor::ParseConfigTxt(const std::string &filepath)
{
    auto fileLoader = std::make_unique<TxtFileLoader>();
    auto parser = std::make_unique<TxtParser>();
    auto interpreter = std::make_unique<TxtInterpreter>();

    std::string content = fileLoader->LoadTxt(filepath);
    std::vector<Variable> Variables = parser->ParseTxt(content);
    std::unordered_map<std::string, std::any> CastedVariables = interpreter->InterpreteTxt(Variables);

    return CastedVariables;
}
