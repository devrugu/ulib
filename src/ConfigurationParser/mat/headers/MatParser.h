#ifndef MATPARSER_H
#define MATPARSER_H

#include "../../../headers/AllHeaders.h"

class MatParser
{
public:
    virtual ~MatParser();
    MatParser();

    std::map<std::string, matvar_t *> ParseMatFile(mat_t* matfp, std::vector<std::string> UserVariableNames);
};

#endif // MATPARSER_H
