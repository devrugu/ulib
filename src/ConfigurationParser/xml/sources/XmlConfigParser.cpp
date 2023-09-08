#include "../headers/XmlConfigParser.h"

std::map<std::string, std::string> XmlConfigParser::ParseConfig(const std::string& filePath)
{
    // XML dosyasını yükle; bu işlem, dosyanın düzgün biçimde ayrıştırılıp ayrıştırılamayacağını kontrol eder
    QDomDocument fileData = fileLoader.LoadFile(filePath);

    // Yüklenen dosya verilerini ayrıştır ve ayar verilerini al
    std::map<std::string, std::string> configData = parser.Parse(fileData);

    // Eğer ayrıştırılan veri seti boş ise, kullanıcıyı bilgilendir ve boş bir map döndür
    if (configData.empty()) {
        std::cerr << "Konfigürasyon değerleri bulunamadı. XML dosyanızı kontrol edin.\n";
        return std::map<std::string, std::string>();
    }

    return configData;
}

