#ifndef MATFILELOADER_H
#define MATFILELOADER_H

#include "../../../headers/AllHeaders.h"

#define readOnlyMode 0
#define readWriteMode 1

class MatFileLoader
{
public:
    virtual ~MatFileLoader();

    MatFileLoader();

    mat_t* LoadMatFile(const char* fileName, int mode);
};

#endif //MATFILELOADER_H
