#include "../headers/TxtParser.h"

#include <iostream>
#include <regex>

std::string TxtParser::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::vector<Variable> TxtParser::ParseTxt(std::string content)
{
    std::regex var_pattern(R"(\*(\w+):\s*TYPE\s*=\s*([\w\<\>\,\s]+)\s*VALUE\s*=\s*([^\*]+))"), ArrVecPattern("\\b(\\w+)<(\\w+)>");
    std::smatch MatchVar, MatchArrVec;

    std::vector<Variable> Variables;

    while (std::regex_search(content, MatchVar, var_pattern)) {
        Variable var{trim(MatchVar[1].str()), trim(MatchVar[2].str()), trim(MatchVar[3].str())};
        Variables.push_back(var);
        std::cout << var.type << "\n";  //debug type
        content = MatchVar.suffix().str();
    }

    return Variables;
}
