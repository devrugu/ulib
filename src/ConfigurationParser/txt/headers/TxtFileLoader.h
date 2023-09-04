#ifndef TXTFILELOADER_H
#define TXTFILELOADER_H

#include "../../../headers/AllHeaders.h"

class TxtFileLoader {
public:
    static std::vector<std::string> load(const std::string& filepath);
};

#endif  // TXTFILELOADER_H
