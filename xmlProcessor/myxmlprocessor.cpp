#include "myxmlprocessor.h"

MyXMLProcessor::MyXMLProcessor()
{

}
QList<ColsInfo>* MyXMLProcessor::readColsXml(QString fileName){
    QList<ColsInfo>* colsInfo = new QList<ColsInfo>();
    QFile colsInfoFile(fileName);
    if(!colsInfoFile.exists()){
        qDebug() << "cols配置文件位置错误" ;
    }else{

        tinyxml2::XMLDocument colsInfoDoc;
        const char * fileName_cstr = fileName.toStdString().c_str();
        fileName_cstr = "E:/workspace/qt5/AHQC/configs/ItemCols.xml";

        colsInfoDoc.LoadFile(fileName_cstr);

        tinyxml2::XMLElement* root = colsInfoDoc.FirstChildElement("factors");
        tinyxml2::XMLElement* factor = root ->FirstChildElement("factor");
        tinyxml2::XMLElement* item = 0;

        while(factor != 0){
            item = factor->FirstChildElement("Item");
            while(item != 0){
                QString dataName(item->FirstChildElement("name")->FirstChild()->ToText()->Value());
                int beginIndex = std::atoi(item->FirstChildElement("beginIndex")->FirstChild()->ToText()->Value());
                int endIndex = std::atoi(item->FirstChildElement("endIndex")->FirstChild()->ToText()->Value());
                colsInfo->append(ColsInfo(dataName,beginIndex,endIndex));
                item = item -> NextSiblingElement("Item");
            }

            factor = factor -> NextSiblingElement("factor");
        }


    }

    return colsInfo;
}
