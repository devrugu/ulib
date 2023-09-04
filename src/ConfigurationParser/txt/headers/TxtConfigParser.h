#ifndef TXTCONFIGPARSER_H
#define TXTCONFIGPARSER_H

#include "../../../headers/AllHeaders.h"
#include "TxtFileLoader.h"
#include "TxtParser.h"
#include "TxtInterpreter.h"

class TxtConfigParser {
private:
    std::unordered_map<std::string, ConfigVariant> data;

public:
    TxtConfigParser(const std::string& filepath);

    template <typename T>
        T get(const std::string& key) {
            try {
                return std::get<T>(data.at(key));
            } catch (const std::exception&) {
                throw std::runtime_error("Key not found or wrong type");
            }
        }
};

#endif
