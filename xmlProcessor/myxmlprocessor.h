#ifndef MYXMLPROCESSOR_H
#define MYXMLPROCESSOR_H
#include "QList"
#include "simpleobject.h"
#include "tinyXml2/tinyxml2.h"
#include "QFile"
#include "QDebug"
class MyXMLProcessor
{
public:
    MyXMLProcessor();
    ~MyXMLProcessor(){}
    QList<ColsInfo>* readColsXml(QString fileName);
};

#endif // MYXMLPROCESSOR_H
