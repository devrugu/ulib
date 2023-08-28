#ifndef MATINTERPRETER_H
#define MATINTERPRETER_H

#include "../../../headers/AllHeaders.h"

class MatInterpreter
{
public:
    virtual ~MatInterpreter();
    MatInterpreter();

    std::pair<std::string, std::any> SpecifyDataType(matvar_t *Variable, std::string Name);
    std::map<std::string, std::any> InterpreteMatFile(std::vector<matvar_t*> Variables, std::vector<std::string> UserVariableNames);
};

#endif // MATINTERPRETER_H
