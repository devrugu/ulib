#include "../headers/XmlConfigProcessor.h"
#include "../headers/XmlFileLoader.h"
#include "../headers/XmlParser.h"

#include <QDomDocument>
#include <memory>

std::map<std::string, std::string> XmlConfigProcessor::ParseConfig(const std::string& filePath)
{
    auto fileLoader = std::make_unique<XmlFileLoader>();
    auto parser = std::make_unique<XmlParser>();

    // XML dosyasını yükle; bu işlem, dosyanın düzgün biçimde ayrıştırılıp ayrıştırılamayacağını kontrol eder
    QDomDocument fileData = fileLoader->LoadFile(filePath);

    // Yüklenen dosya verilerini ayrıştır ve config verilerini al
    std::map<std::string, std::string> configData = parser->Parse(fileData);

    // Eğer ayrıştırılan veri seti boş ise, kullanıcıyı bilgilendir ve boş bir map döndür
    if (configData.empty()) {
        std::cerr << "Konfigürasyon değerleri bulunamadı. XML dosyanızı kontrol edin.\n";
        return std::map<std::string, std::string>();
    }

    return configData;
}

