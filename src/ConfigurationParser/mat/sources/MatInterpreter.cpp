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

#include <iostream>
#include <matio.h>
#include <memory>

MatInterpreter::MatInterpreter()
{
    //std::cout << "MAT file interpreter successfully constructed\n\n";
}

MatInterpreter::~MatInterpreter()
{
    //std::cout << "MAT file interpreter successfully deconstructed\n\n";
}

std::pair<std::string, std::any> MatInterpreter::SpecifyDataType(matvar_t* Variable, const std::string Name) {
    std::pair<std::string, std::any> TypeCastedVariableOfUser;

    if (Variable->class_type == MAT_C_OPAQUE) {
        std::cout << "Error: Data type of variable '" << Variable->name << "' is unknown!\n";
    }
    else if (Variable->data_type == MAT_T_UNKNOWN) {
        std::cout << "Error: Data type of variable '" << Variable->name << "' is unknown!\n";
    }
    else if ((Variable->class_type == MAT_C_CHAR) && (Variable->data_type == MAT_T_UINT16)) {
        uint16_t* uint16Data = static_cast<uint16_t*>(Variable->data);
        size_t numElements = Variable->dims[0] * Variable->dims[1];
        std::wstring wideString(uint16Data, uint16Data + numElements);
        std::string value(wideString.begin(), wideString.end());

        std::shared_ptr<char[]> newValue(new char[value.length() + 1]);
        std::copy(value.begin(), value.end(), newValue.get());
        newValue[value.length()] = '\0';

        TypeCastedVariableOfUser = std::make_pair(Name, newValue);
    }
    else {
        switch (Variable->data_type) {
            case MAT_T_INT8:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<int8_t>(static_cast<int8_t*>(Variable->data), [](int8_t*){}));
                break;
            case MAT_T_UINT8:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<uint8_t>(static_cast<uint8_t*>(Variable->data), [](uint8_t*){}));
                break;
            case MAT_T_INT16:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<int16_t>(static_cast<int16_t*>(Variable->data), [](int16_t*){}));
                break;
            case MAT_T_UINT16:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<uint16_t>(static_cast<uint16_t*>(Variable->data), [](uint16_t*){}));
                break;
            case MAT_T_INT32:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<int32_t>(static_cast<int32_t*>(Variable->data), [](int32_t*){}));
                break;
            case MAT_T_UINT32:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<uint32_t>(static_cast<uint32_t*>(Variable->data), [](uint32_t*){}));
                break;
            case MAT_T_SINGLE:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<float>(static_cast<float*>(Variable->data), [](float*){}));
                break;
            case MAT_T_DOUBLE:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<double>(static_cast<double*>(Variable->data), [](double*){}));
                break;
            case MAT_T_INT64:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<int64_t>(static_cast<int64_t*>(Variable->data), [](int64_t*){}));
                break;
            case MAT_T_UINT64:
                TypeCastedVariableOfUser = std::make_pair(Name, std::shared_ptr<uint64_t>(static_cast<uint64_t*>(Variable->data), [](uint64_t*){}));
                break;
            case MAT_T_UTF8:
            case MAT_T_UTF16:
            case MAT_T_UTF32:
            case MAT_T_STRING:
            {
                std::shared_ptr<char[]> ptr(static_cast<char*>(Variable->data));
                TypeCastedVariableOfUser = std::make_pair(Name, ptr);
                break;
            }
            default:
                break;
        }
    }

    return TypeCastedVariableOfUser;
}

std::map<std::string, std::any> MatInterpreter::InterpreteMatFile(std::map<std::string, matvar_t*> VariablesOfUser)
{
    std::map<std::string ,std::any> TypeCastedVariablesOfUser;
    for (const auto& [Name, Var] : VariablesOfUser) {
        if(Var->class_type == MAT_C_STRUCT){
            for (size_t i = 0; i < Var->nbytes / Var->data_size; ++i) {
                matvar_t *field = Mat_VarGetStructFieldByIndex(Var, i, 0);
                if (field) {
                    std::cout << "Processing struct field: " << field->name << "\n";
                    TypeCastedVariablesOfUser.insert(SpecifyDataType(field, field->name));
                    //Mat_VarFree(field);   // no need
                }
            }
        } else {
            std::cout << "Processing variable: " << Name << "\n";
            TypeCastedVariablesOfUser.insert(SpecifyDataType(Var, Name));
        }
    }

    return TypeCastedVariablesOfUser;
}
