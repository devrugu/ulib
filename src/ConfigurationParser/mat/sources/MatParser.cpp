#include "../headers/MatParser.h"



MatParser::~MatParser()
{
    std::cout << "MAT file parser successfully deconstructed.\n\n";
}

MatParser::MatParser()
{
    std::cout << "MAT file parser successfully constructed\n\n";
}

std::map<char *, matvar_t *> MatParser::ParseMatFile(mat_t *matfp)
{
    matvar_t *matVar;
    std::map<char*, matvar_t*> variableNameAndContent; // for ease of use
    while ( NULL != (matVar = Mat_VarReadNext(matfp)) ) {
        variableNameAndContent.insert({matVar->name, matVar});
        Mat_VarFree(matVar);
    }

    return variableNameAndContent;
}
