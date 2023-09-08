#include "../headers/XmlParser.h"

// Belirtilen XML düğümünü ve alt düğümlerini ayrıştırmak için.
void XmlParser::traverseAndParseNode(const QDomNode &node, std::map<std::string, std::string> &result, const std::string &parentPath)
{
    try
    {
        QDomNode n = node.firstChild();
        // Çocuk düğüm null olana kadar (yani çocuk düğümler tükenene kadar) döngü sürdürülüyor.
        while(!n.isNull()) {
            // Eğer geçerli düğüm bir element ise (XML elementi demek).
            if(n.isElement()) {
                QDomElement element = n.toElement();
                std::string nodeName = element.tagName().toStdString();
                std::string nodePath = parentPath.empty() ? nodeName : parentPath + "." + nodeName;
                bool isLeafNode = element.firstChildElement().isNull();

                // Yaprak düğüm ise, düğümün metnini sonuç haritasına ekliyoruz.
                if(isLeafNode) {
                    result.insert(std::make_pair(nodePath, element.text().toStdString()));
                }

                // Recursive çağrı ile geçerli düğümün tüm alt düğümlerini ayrıştırıyoruz.
                traverseAndParseNode(n, result, nodePath);
            }
            n = n.nextSibling();
        }
    }
    catch(const std::exception& e)
    {
        // Log kaydı olabilir burada
        std::cerr << "XML ayrıştırma sırasında bir hata oluştu: " << e.what() << '\n';
    }
}

// XML belgesini ayrıştırmak için.
std::map<std::string, std::string> XmlParser::Parse(QDomDocument doc)
{
    std::map<std::string, std::string> result;
    try
    {
        QDomElement root = doc.documentElement();
        if(root.isNull())
        {
            // Log kaydı
            throw std::runtime_error("XML belgesi boş veya geçersiz bir kök elemente sahip.");
        }
        traverseAndParseNode(root, result);
    }
    catch(const std::exception& e)
    {
        // Log kaydı olabilir
        std::cerr << "XML belgesini ayrıştırırken bir hata oluştu: " << e.what() << '\n';
    }

    return result;
}

