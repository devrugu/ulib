#include "../headers/MatParser.h"

MatParser::~MatParser()
{
    std::cout << "MAT file parser successfully deconstructed.\n\n";
}

MatParser::MatParser()
{
    std::cout << "MAT file parser successfully constructed\n\n";
}

std::map<std::string, matvar_t*> MatParser::ParseMatFile(mat_t *matfp, std::vector<std::string> UserVariableNames)
{
    matvar_t *MatVar;

    std::map<std::string, matvar_t*> VariablesOfUser;
    for (const std::string &UserVar : UserVariableNames) {
        bool found = false;
        while ( NULL != (MatVar = Mat_VarReadNext(matfp)) ) {
            if (!strcmp(MatVar->name, UserVar.c_str())) {
                VariablesOfUser[UserVar] = Mat_VarDuplicate(MatVar, 1);
                Mat_VarFree(MatVar);
                found = true;
                break;
            }
        }
        if(!found) {
            std::cerr << "Variable '" << UserVar << "' not found in the MAT file." << std::endl;
        }
    }

    return VariablesOfUser;
}
