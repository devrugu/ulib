#include "../headers/MatParser.h"

MatParser::~MatParser()
{
    //std::cout << "MAT file parser successfully deconstructed.\n\n";
}

MatParser::MatParser()
{
    //std::cout << "MAT file parser successfully constructed\n\n";
}

std::map<std::string, matvar_t*> MatParser::ParseMatFile(mat_t *matfp, std::vector<std::string> UserVariableNames, int ReadType)
{
    std::map<std::string, matvar_t*> VariablesOfUser;

    if(ReadType){
        // reading some of the variables
        for (const std::string &UserVar : UserVariableNames) {
            VariablesOfUser[UserVar] = Mat_VarRead(matfp, UserVar.c_str());
        }
    } else {
        // reading all variables at once
        matvar_t *MatVar;
        std::vector<matvar_t*> AllVariablesOfMatFile;

        while ( NULL != (MatVar = Mat_VarReadNext(matfp)) ) {
            AllVariablesOfMatFile.push_back(MatVar);
        }

        for (const std::string &UserVar: UserVariableNames) {
            bool found = false;
            for (matvar_t* Var : AllVariablesOfMatFile) {
                if(!strcmp(UserVar.c_str(), Var->name)) {
                    VariablesOfUser[UserVar] = Var;
                    found=true;
                    break;
                }
            }
            if(!found)
                std::cerr << "Variable '" << UserVar << "' not found in the MAT file.\n";
        }
    }
    return VariablesOfUser;
}

//for (const std::string &UserVar : UserVariableNames) {
//    bool found = false;
//    while ( NULL != (MatVar = Mat_VarReadNext(matfp)) ) {
//        if (!strcmp(MatVar->name, UserVar.c_str())) {
//            VariablesOfUser[UserVar] = Mat_VarDuplicate(MatVar, 1);
//            Mat_VarFree(MatVar);
//            found = true;
//            break;
//        }
//    }
//    if(!found) {
//        std::cerr << "Variable '" << UserVar << "' not found in the MAT file." << std::endl;
//    }
//}

//for (const std::string &UserVar : UserVariableNames) {
//    for (matvar_t* Var : AllVariablesOfMatFile) {
//        if(!strcmp(Var->name, UserVar.c_str())) {
//            VariablesOfUser[UserVar] = Var;
//            break;
//        }
//    }
//}
