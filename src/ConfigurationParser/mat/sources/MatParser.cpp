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
    //sorun burada basliyor -- once burayi hallet -- halledildi
    //matVar değiştirince vector içerisindeki matVar ın de içeriği değişiyor ve yok oluyor. --çözüldü
    while ( NULL != (matVar = Mat_VarReadNext(matfp)) ) {
        Variables.push_back(Mat_VarDuplicate(matVar, 1));
        Mat_VarFree(matVar);
    }

    return Variables;
}
