#ifndef XMLINTERPRETER_H
#define XMLINTERPRETER_H

#include "../../../headers/allHeaders.h"

class XmlInterpreter {
public:
    XmlInterpreter(const std::map<std::string, std::string>& dataMap);

    template<typename T>
    T interpret(const std::string& key);

private:
    const std::map<std::string, std::string>& data;

    template<typename T>
    T parseValue(const std::string& value);

    // Specializations for different types will be defined in the cpp file
};

#endif // XMLINTERPRETER_H
