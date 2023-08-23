#ifndef XMLFILELOADER_H
#define XMLFILELOADER_H

#include "../../interfaces/IFileLoader.h"

class XmlFileLoader : public IFileLoader
{
public:
    virtual ~XmlFileLoader() = default;
    QDomDocument LoadFile(const std::string& filePath) override;
};

#endif // XMLFILELOADER_H
