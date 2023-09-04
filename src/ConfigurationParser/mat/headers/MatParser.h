#ifndef MATPARSER_H
#define MATPARSER_H

#include "../../../headers/AllHeaders.h"

#define ReadAll 0
#define ReadPartial 1

class MatParser
{
public:
    virtual ~MatParser();
    MatParser();

    std::map<std::string, matvar_t *> ParseMatFile(mat_t* matfp, std::vector<std::string> UserVariableNames, int ReadType);
    void WriteMatFile(std::vector<matvar_t*> AllVariablesOfMatFile);
};

#endif // MATPARSER_H
