#include "../headers/TxtConfigParser.h"

std::unordered_map<std::string, std::any> TxtConfigParser::ParseConfigTxt(const std::string &filepath)
{
    std::string content = fileLoader.LoadTxt(filepath);
    std::vector<Variable> Variables = parser.ParseTxt(content);
    std::unordered_map<std::string, std::any> CastedVariables = interpreter.InterpreteTxt(Variables);

    return CastedVariables;
}
