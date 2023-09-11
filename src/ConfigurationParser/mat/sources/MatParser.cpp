#include "../headers/MatParser.h"

#include <cstring>
#include <iostream>
#include <matio.h>

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
        // reading selected variables one by one
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

        WriteMatFile(AllVariablesOfMatFile);

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

void MatParser::WriteMatFile(std::vector<matvar_t *> AllVariablesOfMatFile)
{
    mat_t* matfp2 = Mat_CreateVer("generated-mat-file.mat", NULL, MAT_FT_MAT5);
        if (matfp2 == NULL) {
            std::cerr << "Error creating MAT file: " << "generated-mat-file.mat" << std::endl;
        }

        for (const auto& Var : AllVariablesOfMatFile) {
            if (Mat_VarWrite(matfp2, Var, MAT_COMPRESSION_NONE) != 0) {
                std::cerr << "Error writing variable '" << Var->name << "' to MAT file." << std::endl;
            }
        }

        Mat_Close(matfp2);
}
