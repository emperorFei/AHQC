#ifndef MYXMLPROCESSOR_H
#define MYXMLPROCESSOR_H
#include "QList"
#include "simpleobject.h"
#include "tinyXml2/tinyxml2.h"
#include "QFile"
#include "QDebug"
#include <QDir>
#include <QApplication>
#include <iostream>
using namespace tinyxml2;
class MyXMLProcessor
{
public:
    MyXMLProcessor();
    ~MyXMLProcessor(){}
    QList<ColInfo>* readColsXml(QString &fileName);
};

#endif // MYXMLPROCESSOR_H
