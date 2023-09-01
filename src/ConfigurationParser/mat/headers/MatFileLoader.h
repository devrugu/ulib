#ifndef MATFILELOADER_H
#define MATFILELOADER_H

#include "../../../headers/AllHeaders.h"

#define ReadOnlyMode 0
#define ReadWriteMode 1

class MatFileLoader
{
public:
    virtual ~MatFileLoader();

    MatFileLoader();

    mat_t* LoadMatFile(std::string fileName, int mode);
};

#endif //MATFILELOADER_H
