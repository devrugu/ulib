#ifndef MATFILELOADER_H
#define MATFILELOADER_H

#include <string>

class _mat_t;

#define ReadOnlyMode 0
#define ReadWriteMode 1

class MatFileLoader
{
public:
    virtual ~MatFileLoader();

    MatFileLoader();

    _mat_t* LoadMatFile(std::string fileName, int mode);
};

#endif //MATFILELOADER_H
