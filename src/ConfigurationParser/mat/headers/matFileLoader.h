#ifndef MATFILELOADER_H
#define MATFILELOADER_H

#include "../../../headers/allHeaders.h"

#define readOnlyMode 0
#define readWriteMode 1

class matFileLoader
{
    virtual ~matFileLoader();

    matFileLoader();

    mat_t* loadMatFile(const char* fileName, int mode);
};

#endif //MATFILELOADER_H
