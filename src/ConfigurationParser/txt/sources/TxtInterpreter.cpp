#include "../headers/TxtInterpreter.h"

std::any TxtInterpreter::VariantToAny(const std::variant<int, double, float, std::string, bool> &var)
{
    return std::visit([](auto&& arg) -> std::any { return arg; }, var);
}

std::variant<int, double, float, std::string, bool> TxtInterpreter::SpecifyDataType(Variable Var)
{
    if (Var.type == "int") {
        return std::stoi(Var.value);
    } else if (Var.type == "double") {
        return std::stod(Var.value);
    } else if (Var.type == "float") {
        return std::stof(Var.value);
    } else if (Var.type == "string") {
        if (Var.value.front() == '\"' && Var.value.back() == '\"') {
            Var.value = Var.value.substr(1, Var.value.size() - 2);
        }
        return Var.value;
    } else if (Var.type == "bool") {
        bool value;
        if(Var.value == "true" || Var.value == "1" || Var.value == "TRUE") {
            value = true;
        } else if (Var.value == "false" || Var.value == "0" || Var.value == "FALSE") {
            value = false;
        } else {
            std::cout << "bool type should be 'true' or 'false'.\n"
                         "correct usage --> 'true', '1' or 'TRUE' for true "
                         "and 'false', '0' or 'FALSE' for false\n";
            exit(1);
        }
        return value;
    } else {
        std::cerr << Var.name << ":" << Var.type << " datatype is unknown\n";
        exit(1);
    }
}

std::unordered_map<std::string, std::any> TxtInterpreter::InterpreteTxt(std::vector<Variable> Variables)
{
    std::unordered_map<std::string, std::any> CastedVariables;

    std::regex ArrVecPattern("\\b(\\w+)<(\\w+)>");
    std::smatch MatchArrVec;

    for (const auto& Var : Variables) {
        if (Var.type.compare(0, 5, "array") == 0 || Var.type.compare(0, 6, "vector") == 0) {
            if (std::regex_search(Var.type, MatchArrVec, ArrVecPattern)) {
                std::string elementType = MatchArrVec[2];

                std::regex number_pattern(R"((\btrue\b|\bfalse\b|\bTRUE\b|\bFALSE\b|\b\d+\.\d+|\b\d+|"(?:[^"\\]|\\.)*"))");
                std::sregex_iterator begin(Var.value.begin(), Var.value.end(), number_pattern);
                std::sregex_iterator end;
                std::vector<std::string> values;
                for(std::sregex_iterator it = begin; it != end; ++it) {
                    values.push_back(it->str());
                }
                std::cout << "(";
                for (const auto& s : values) {
                    std::cout << s << ",";      // debug vector-array value
                }
                std::cout << ")\n";

                if (elementType == "int") {
                    std::vector<int> VectorInt;
                    for (const auto &element : values)
                        VectorInt.push_back(std::stoi(element));
                    CastedVariables[Var.name] = VectorInt;
                } else if (elementType == "double") {
                    std::vector<double> VectorDouble;
                    for (const auto &element : values)
                        VectorDouble.push_back(std::stod(element));
                    CastedVariables[Var.name] = VectorDouble;
                } else if (elementType == "float") {
                    std::vector<float> VectorFloat;
                    for (const auto &element : values)
                        VectorFloat.push_back(std::stof(element));
                    CastedVariables[Var.name] = VectorFloat;
                } else if (elementType == "string") {
                    std::vector<std::string> VectorString;
                    for (const auto &element : values) {
                        std::string StrValue = element;
                        if (StrValue.front() == '\"' && StrValue.back() == '\"') {
                                StrValue = StrValue.substr(1, StrValue.size() - 2);
                            }
                        VectorString.push_back(StrValue);
                    }
                    CastedVariables[Var.name] = VectorString;
                } else if (elementType == "bool") {
                    std::vector<bool> VectorBool;
                    for (const auto& element : values) {
                        bool BoolValue;
                        if(element == "true" || element == "1" || element == "TRUE") {
                            BoolValue = true;
                        } else if (element == "false" || element == "0" || element == "FALSE") {
                            BoolValue = false;
                        } else {
                            std::cout << "bool type should be 'true' or 'false'.\n"
                                         "correct usage --> 'true', '1' or 'TRUE' for true "
                                         "and 'false', '0' or 'FALSE' for false\n";
                            exit(1);
                        }
                        VectorBool.push_back(BoolValue);
                    }
                    CastedVariables[Var.name] = VectorBool;
                }
            } else {
                std::cerr << "array or vector format is incorrect\n";
                exit(1);
            }
        } else {
            CastedVariables[Var.name] = VariantToAny(SpecifyDataType(Var));
        }
    }
    return CastedVariables;
}
