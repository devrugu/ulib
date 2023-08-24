#ifndef MATPARSER_H
#define MATPARSER_H

#include "../../../headers/AllHeaders.h"

class MatParser
{
public:
    virtual ~MatParser();
    MatParser();

    std::map<char *, matvar_t *> ParseMatFile(mat_t* matfp);
};

#endif // MATPARSER_H
