#include "../headers/MatFileLoader.h"

MatFileLoader::~MatFileLoader()
{
    std::cout << "mat file loader successfully deconstructed\n\n";
}

MatFileLoader::MatFileLoader()
{
    std::cout << "mat file loader successfully constructed\n\n";
}

mat_t *MatFileLoader::LoadMatFile(const char *fileName, int mode)
{
    // Open the MAT file
    mat_t *matfp = Mat_Open(fileName, (mode==0)?readOnlyMode:readWriteMode);
    if (NULL == matfp) {
        std::cerr << "Error opening MAT file: " << fileName << "\n";
        exit(-1);
    } else if(mode != 0 && mode != 1){
        std::cerr << "openning mode of MAT file is incorrect. Valid values:\n0 --> read only\n1 --> read and write\n";
        exit(-1);
    } else{
        return matfp;
    }
}
