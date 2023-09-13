#ifndef TXTINTERPRETER_H
#define TXTINTERPRETER_H

#include "TxtParser.h"

#include <any>
#include <unordered_map>
#include <variant>

class TxtInterpreter{
public:
    std::any VariantToAny(const std::variant<int, double, float, std::string, bool>& var);
    std::variant<int, double, float, std::string, bool> SpecifyDataType(Variable Var);
    std::unordered_map<std::string, std::any> InterpreteTxt(std::vector<Variable> Variables);
};

#endif  // TXTINTERPRETER_H
