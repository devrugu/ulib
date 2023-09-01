#include "../headers/MatConfigParser.h"

matConfigParser::matConfigParser()
{
    //std::cout << "mat config parser successfully constructed\n\n";
}


matConfigParser::~matConfigParser()
{
    //std::cout << "mat config parser successfully deconstructed\n\n";
}

std::map<std::string, std::any> matConfigParser::ParseConfigMatFile(const std::string fileName, int mode, int ReadType, std::vector<std::string> UserVariableNames)
{
    mat_t* matfp = fileLoader.LoadMatFile(fileName, mode);

    std::map<std::string, matvar_t*> VariablesOfUser = parser.ParseMatFile(matfp, UserVariableNames, ReadType);

    std::map<std::string ,std::any> TypeCastedVariablesOfUser = interpreter.InterpreteMatFile(VariablesOfUser);

    Mat_Close(matfp);

    return TypeCastedVariablesOfUser;
}
