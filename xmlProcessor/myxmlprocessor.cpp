#include "myxmlprocessor.h"

MyXMLProcessor::MyXMLProcessor()
{

}
QList<ColInfo>* MyXMLProcessor::readColsXml(QString &fileName){
    QList<ColInfo>* colsInfo = new QList<ColInfo>();
    tinyxml2::XMLDocument colsInfoDoc;

    colsInfoDoc.LoadFile("configs/ItemCols.xml");

    tinyxml2::XMLElement* root = colsInfoDoc.FirstChildElement("factors");
    tinyxml2::XMLElement* factor = root ->FirstChildElement("factor");
    tinyxml2::XMLElement* item = Q_NULLPTR;

    while(factor != Q_NULLPTR){
        item = factor->FirstChildElement("Item");
        while(item != Q_NULLPTR){
            QString dataName(item->FirstChildElement("name")->FirstChild()->ToText()->Value());
            int beginIndex = std::atoi(item->FirstChildElement("beginIndex")->FirstChild()->ToText()->Value());
            int endIndex = std::atoi(item->FirstChildElement("endIndex")->FirstChild()->ToText()->Value());
            int length= std::atoi(item->FirstChildElement("length")->FirstChild()->ToText()->Value());
            colsInfo->append(ColInfo(dataName,beginIndex,endIndex,length));
            item = item -> NextSiblingElement("Item");
        }

        factor = factor -> NextSiblingElement("factor");
    }


    //}

    return colsInfo;
}
