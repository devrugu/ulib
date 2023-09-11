#ifndef MATINTERPRETER_H
#define MATINTERPRETER_H

#include <any>
#include <map>
#include <string>

class matvar_t;

class MatInterpreter
{
public:
    virtual ~MatInterpreter();
    MatInterpreter();

    std::pair<std::string, std::any> SpecifyDataType(matvar_t *Variable, std::string Name);
    std::map<std::string, std::any> InterpreteMatFile(std::map<std::string, matvar_t*> VariablesOfUser);
};

#endif // MATINTERPRETER_H
