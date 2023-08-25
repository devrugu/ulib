#include "../headers/MatParser.h"

MatParser::~MatParser()
{
    std::cout << "MAT file parser successfully deconstructed.\n\n";
}

MatParser::MatParser()
{
    std::cout << "MAT file parser successfully constructed\n\n";
}

std::vector<matvar_t *> MatParser::ParseMatFile(mat_t *matfp)
{
    matvar_t *matVar;
    std::vector<matvar_t *> Variables; // for ease of use
    while ( NULL != (matVar = Mat_VarReadNext(matfp)) ) {
        Variables.push_back(matVar);
        Mat_VarFree(matVar);
    }

    return Variables;
}
