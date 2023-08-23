#ifndef ILEXER_H
#define ILEXER_H

#include "../../headers/allHeaders.h"

class ILexer
{
public:
    virtual ~ILexer() = default;
    virtual std::pair<std::vector<std::string>, QDomDocument> Tokenize(const std::vector<char>& fileData) = 0;
};

#endif // ILEXER_H
