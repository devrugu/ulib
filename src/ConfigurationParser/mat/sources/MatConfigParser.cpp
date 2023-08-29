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

    //auto start = std::chrono::high_resolution_clock::now(); // başlangıç süresi
    std::vector<matvar_t *> Variables = parser.ParseMatFile(matfp);
    //auto end = std::chrono::high_resolution_clock::now();   // bitiş süresi

    //auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);  // süre hesaplaması
    //std::cout << "The function took: " << duration.count() << " seconds." << std::endl; //süreyi yazdır

    std::map<std::string ,std::any> TypeCastedVariablesOfUser = interpreter.InterpreteMatFile(Variables, UserVariableNames);

    return TypeCastedVariablesOfUser;
}
