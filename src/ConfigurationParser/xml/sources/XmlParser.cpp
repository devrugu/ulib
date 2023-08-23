#include "../headers/XmlParser.h"

void XmlParser::traverseAndParseNode(const QDomNode &node, std::map<std::string, std::string> &result, const std::string &parentPath)
{
    QDomNode n = node.firstChild();
    while(!n.isNull()) {
        if(n.isElement()) {
            QDomElement element = n.toElement();
            std::string nodeName = element.tagName().toStdString();
            std::string nodePath = parentPath.empty() ? nodeName : parentPath + "." + nodeName;

            bool isLeafNode = element.firstChildElement().isNull();

            if(isLeafNode) {
                //nodePath = nodePath + "-" + element.attribute("type").toStdString();
                //std::cout << "success" << "\n";
                result.insert(std::make_pair(nodePath, element.text().toStdString()));
            }

            traverseAndParseNode(n, result, nodePath);
        }
        n = n.nextSibling();
    }
}

std::map<std::string, std::string> XmlParser::Parse(QDomDocument doc)
{
    std::map<std::string, std::string> result;

    QDomElement root = doc.documentElement();
    traverseAndParseNode(root, result);

    return result;
}
