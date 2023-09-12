#ifndef MATCONFIGPROCESSOR_H
#define MATCONFIGPROCESSOR_H

#include <any>
#include <map>
#include <string>
#include <vector>

class matConfigProcessor
{
public:
    virtual ~matConfigProcessor();
    matConfigProcessor();

    std::map<std::string ,std::any> ParseConfigMatFile(const std::string fileName, int mode, int ReadType, std::vector<std::string> UserVariableNames);
    void FreeMemory(std::map<std::string ,std::any> TypeCastedVariablesOfUser);

private:
};

#endif // MATCONFIGPROCESSOR_H
