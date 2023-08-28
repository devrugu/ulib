#include "../headers/MatConfigParser.h"

matConfigParser::matConfigParser()
{
    std::cout << "mat config parser successfully constructed\n\n";
}


matConfigParser::~matConfigParser()
{
    std::cout << "mat config parser successfully deconstructed\n\n";
}

std::map<std::string, std::any> matConfigParser::ParseConfigMatFile(const std::string fileName, int mode, std::vector<std::string> UserVariableNames)
{
    mat_t* matfp = fileLoader.LoadMatFile(fileName, mode);

    std::vector<matvar_t *> Variables = parser.ParseMatFile(matfp);

    std::map<std::string ,std::any> TypeCastedVariablesOfUser = interpreter.InterpreteMatFile(Variables, UserVariableNames);

    return TypeCastedVariablesOfUser;
}
