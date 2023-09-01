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
};

#endif // MATPARSER_H
