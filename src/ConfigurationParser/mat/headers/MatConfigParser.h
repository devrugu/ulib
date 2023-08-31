#ifndef MATCONFIGPARSER_H
#define MATCONFIGPARSER_H

#include "MatFileLoader.h"
#include "MatParser.h"
#include "MatInterpreter.h"

class matConfigParser
{
public:
    virtual ~matConfigParser();
    matConfigParser();

    std::map<std::string ,std::any> ParseConfigMatFile(const std::string fileName, int mode, std::vector<std::string> UserVariableNames);
    void FreeMemory(std::map<std::string ,std::any> TypeCastedVariablesOfUser);

private:
    MatFileLoader fileLoader;
    MatParser parser;
    MatInterpreter interpreter;
};

#endif // MATCONFIGPARSER_H
