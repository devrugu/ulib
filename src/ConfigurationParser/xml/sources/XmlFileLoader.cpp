#include "../headers/XmlFileLoader.h"

QDomDocument XmlFileLoader::LoadFile(const std::string& filePath) {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        printf("errorf\n");
        return QDomDocument();
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();

    // Detect the XML declaration and exclude it from the wrapping
    QString xmlDeclaration;
    int declarationEndIndex = fileContent.indexOf("?>");
    if (declarationEndIndex != -1) {
        xmlDeclaration = fileContent.left(declarationEndIndex + 2);
        fileContent = fileContent.mid(declarationEndIndex + 2);
    }

    // Wrap the entire content within a temporary root tag
    QString wrappedContent = xmlDeclaration + "<TempRoot>" + fileContent + "</TempRoot>";

    QDomDocument doc;

    QString errorMsg;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(wrappedContent, &errorMsg, &errorLine, &errorColumn)) {
        std::cerr << "Error loading XML: " << errorMsg.toStdString() << " Line: " << errorLine << " Column: " << errorColumn << std::endl;
        return QDomDocument();
    }

    std::cout << "XML Document: " << doc.toString().toStdString() << std::endl;

    return doc;
}

