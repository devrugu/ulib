#include "../headers/TxtConfigParser.h"

TxtConfigParser::TxtConfigParser(const std::string& filepath) {
    auto lines = TxtFileLoader::load(filepath);
    auto parsedData = TxtParser::parse(lines);
    data = TxtInterpreter::interpret(parsedData);
}

//template <typename T>
//T TxtConfigParser::get(const std::string& key) {
//    try {
//        return std::get<T>(data.at(key));
//    } catch (const std::exception&) {
//        throw std::runtime_error("Key not found or wrong type");
//    }
//}
