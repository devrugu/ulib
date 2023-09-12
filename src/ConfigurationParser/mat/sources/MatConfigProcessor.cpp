#include "../headers/MatConfigProcessor.h"
#include "../headers/MatFileLoader.h"
#include "../headers/MatParser.h"
#include "../headers/MatInterpreter.h"
#include "matio.h"

#include <memory>

matConfigProcessor::matConfigProcessor()
{
    //std::cout << "mat config parser successfully constructed\n\n";
}


matConfigProcessor::~matConfigProcessor()
{
    //std::cout << "mat config parser successfully deconstructed\n\n";
}

std::map<std::string, std::any> matConfigProcessor::ParseConfigMatFile(const std::string fileName, int mode, int ReadType, std::vector<std::string> UserVariableNames)
{
    auto fileLoader = std::make_unique<MatFileLoader>();
    auto parser = std::make_unique<MatParser>();
    auto interpreter = std::make_unique<MatInterpreter>();

    _mat_t* matfp = fileLoader->LoadMatFile(fileName, mode);

    std::map<std::string, matvar_t*> VariablesOfUser = parser->ParseMatFile(matfp, UserVariableNames, ReadType);

    std::map<std::string ,std::any> TypeCastedVariablesOfUser = interpreter->InterpreteMatFile(VariablesOfUser);

    Mat_Close(matfp);

    return TypeCastedVariablesOfUser;
}
