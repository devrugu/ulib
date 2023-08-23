#include "../headers/XmlConfigParser.h"

std::map<std::string, std::string> XmlConfigParser::ParseConfig(const std::string& filePath)
{
    auto fileData = fileLoader.LoadFile(filePath);
    auto configData = parser.Parse(fileData);

    if (configData.empty()) {
        std::cerr << "No configuration values found. Check your XML file.\n";
        return std::map<std::string, std::string>();
    }

    return configData;
}
