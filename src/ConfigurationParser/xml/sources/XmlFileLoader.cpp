#include "../headers/XmlFileLoader.h"

#include <QDomDocument>
#include <QFile>
#include <QString>
#include <QTextStream>

QDomDocument XmlFileLoader::LoadFile(const std::string& filePath) {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        printf("errorf\n");
        return QDomDocument();
    }
    QTextStream in(&file);
    QString fileContent = in.readAll();

    // XML bildirimini algıla ve gereksiz yinelemeyi önlemek için sarma işleminden çıkar
    QString xmlDeclaration;
    int declarationEndIndex = fileContent.indexOf("?>");
    if (declarationEndIndex != -1) {
        xmlDeclaration = fileContent.left(declarationEndIndex + 2);
        fileContent = fileContent.mid(declarationEndIndex + 2);
    }

    QDomDocument doc;

    // İçeriği orijinal dosya içeriği ile ayarlamayı dene; bu, XML dosyasının bir kök (root) öğesi olması durumunda başarılı olur
    QString errorMsg;
    int errorLine;
    int errorColumn;
    bool isSetContentSuccessful = doc.setContent(fileContent, &errorMsg, &errorLine, &errorColumn);

    // İçerik ayarlaması başarısız olursa, bu kök elementin eksik olduğu anlamına gelir
    // Bu durumda, iyi biçimlendirilmiş bir XML belgesi oluşturmak için içeriği geçici bir kök (root) içinde sarar
    if (!isSetContentSuccessful) {
        QString wrappedContent = xmlDeclaration + "<TempRoot>" + fileContent + "</TempRoot>";
        if (!doc.setContent(wrappedContent, &errorMsg, &errorLine, &errorColumn)) {
            std::cerr << "XML yüklenirken hata: " << errorMsg.toStdString() << " Satır: " << errorLine << " Sütun: " << errorColumn << std::endl;
            return QDomDocument();
        }
    }

    // Hata ayıklama amaçları için XML belgesini bir dizgi (string) olarak yazdır
    std::cout << "XML Belgesi: " << doc.toString().toStdString() << std::endl;

    return doc;
}
