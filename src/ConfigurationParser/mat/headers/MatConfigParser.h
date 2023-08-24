#ifndef MATCONFIGPARSER_H
#define MATCONFIGPARSER_H

#include "MatFileLoader.h"

class matConfigParser
{
public:
    virtual ~matConfigParser();
    matConfigParser();

    /*
     * önce parser sınıfını tasarla ve implemente et
     * sonra config parser ana sınıfını tasarla
     * dönüş türünü belirle
    */

private:
    MatFileLoader fileLoader;
};

#endif // MATCONFIGPARSER_H
