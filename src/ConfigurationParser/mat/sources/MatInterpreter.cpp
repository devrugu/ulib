/*
            ---MATLAB data types---
MAT_T_UNKNOWN   =  0,  < @brief MAT unknown type
MAT_T_INT8      =  1,  < @brief MAT int8 type
MAT_T_UINT8     =  2,  < @brief MAT uint8 type
MAT_T_INT16     =  3,  < @brief MAT int16 type
MAT_T_UINT16    =  4,  < @brief MAT uint16 type
MAT_T_INT32     =  5,  < @brief MAT int32 type
MAT_T_UINT32    =  6,  < @brief MAT uint32 type
MAT_T_SINGLE    =  7,  < @brief MAT single type
MAT_T_DOUBLE    =  9,  < @brief MAT double type
MAT_T_INT64     = 10,  < @brief MAT int64 type
MAT_T_UINT64    = 11,  < @brief MAT uint64 type
MAT_T_MATRIX    = 14,  < @brief MAT matlab matrix
MAT_T_COMPRESSED= 15,  < @brief MAT compressed type
MAT_T_UTF8      = 16,  < @brief MAT unicode utf-8 encoded character data
MAT_T_UTF16     = 17,  < @brief MAT unicode utf-16 encoded character data
MAT_T_UTF32     = 18   < @brief MAT unicode utf-32 encoded character data

*/


#include "../headers/MatInterpreter.h"

MatInterpreter::MatInterpreter()
{
    std::cout << "MAT file interpreter successfully constructed\n";
}

MatInterpreter::~MatInterpreter()
{
    std::cout << "MAT file interpreter successfully deconstructed\n";
}

std::pair<std::string ,std::any> MatInterpreter::SpecifyDataType(matvar_t *Variable, std::string Name)
{
    std::pair<std::string ,std::any> TypeCastedVariableOfUser;
    if(Variable->class_type == MAT_C_OPAQUE){
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<char*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UNKNOWN) {
        //TypeCastedVariableOfUser = std::make_pair(Name, static_cast<char*>(Variable->data));
        std::cout << "Error: Data type of variable '" << Variable->name << "' is unknown!\n";
        //exit(1);
    } else if(Variable->data_type == MAT_T_INT8) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<int8_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UINT8) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<uint8_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_INT16) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<int16_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UINT16) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<uint16_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_INT32) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<int32_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UINT32) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<uint32_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_SINGLE) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<float*>(Variable->data));
    } else if(Variable->data_type == MAT_T_DOUBLE) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<double*>(Variable->data));
    } else if(Variable->data_type == MAT_T_INT64) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<int64_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UINT64) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<uint64_t*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UTF8) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<std::string*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UTF16) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<std::string*>(Variable->data));
    } else if(Variable->data_type == MAT_T_UTF32) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<std::string*>(Variable->data));
    } else if(Variable->data_type == MAT_T_STRING) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<std::string*>(Variable->data));
    } else if(Variable->class_type == MAT_C_CHAR) {
        TypeCastedVariableOfUser = std::make_pair(Name, static_cast<char*>(Variable->data));
    }

    return TypeCastedVariableOfUser;
}

std::map<std::string, std::any> MatInterpreter::InterpreteMatFile(std::vector<matvar_t*> Variables, std::vector<std::string> UserVariableNames)
{
    std::map<std::string, matvar_t*> VariablesOfUser;
    for (const std::string &UserVar : UserVariableNames) {
        bool found = false;
        for (matvar_t* MatVar : Variables) {

            if (!strcmp(MatVar->name, UserVar.c_str())) {
                VariablesOfUser[UserVar] = MatVar;
                found = true;
                break;
            }
        }
        if(!found) {
            std::cerr << "Variable '" << UserVar << "' not found in the MAT file." << std::endl;
        }
    }


    std::map<std::string ,std::any> TypeCastedVariablesOfUser;
    for (const auto& [Name, Var] : VariablesOfUser) {
        if(Var->class_type == MAT_C_STRUCT){
            for (size_t i = 0; i < Var->nbytes / Var->data_size; ++i) {
                matvar_t *field = Mat_VarGetStructFieldByIndex(Var, i, 0);
                if (field) {
                    std::cout << "Processing struct field: " << field->name << std::endl;
                    TypeCastedVariablesOfUser.insert(SpecifyDataType(field, field->name));
                }
            }
        } else {
            std::cout << "Processing variable: " << Name << std::endl;
            TypeCastedVariablesOfUser.insert(SpecifyDataType(Var, Name));
        }

    }

    return TypeCastedVariablesOfUser;
}
