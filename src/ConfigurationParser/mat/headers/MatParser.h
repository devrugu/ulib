#ifndef MATPARSER_H
#define MATPARSER_H

#define ReadAll 0
#define ReadPartial 1

#include <map>
#include <vector>
#include <string>

struct matvar_t;
struct _mat_t;

class MatParser
{
public:
    virtual ~MatParser();
    MatParser();

    std::map<std::string, matvar_t *> ParseMatFile(_mat_t* matfp, std::vector<std::string> UserVariableNames, int ReadType);
    void WriteMatFile(std::vector<matvar_t*> AllVariablesOfMatFile);
};

#endif // MATPARSER_H
