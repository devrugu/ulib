#ifndef MATINTERPRETER_H
#define MATINTERPRETER_H

#include "../../../headers/AllHeaders.h"

class MatInterpreter
{
public:
    virtual ~MatInterpreter();
    MatInterpreter();

    std::map<char *, std::any> SpecifyDataType(matvar_t *Variable, char *Name);
    std::map<char *, std::any> InterpreteMatFile(std::vector<matvar_t*> Variables, std::vector<char* > UserVariableNames);
};

#endif // MATINTERPRETER_H
