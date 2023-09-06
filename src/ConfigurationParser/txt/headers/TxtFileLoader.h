#ifndef TXTFILELOADER_H
#define TXTFILELOADER_H

#include "../../../headers/AllHeaders.h"

class TxtFileLoader {
public:
    virtual ~TxtFileLoader();   //decon
    TxtFileLoader();            //con

    std::string load(const std::string& filepath);
};

#endif  // TXTFILELOADER_H
