#include "testreadxmldata.h"

TestReadXmlData::TestReadXmlData(QObject *parent) : QObject(parent){}
TestReadXmlData::~TestReadXmlData(){}
void TestReadXmlData::testReadFine(){
    QFETCH(QString,fileName);
    QFETCH(QString,firstItemName);
    MyXMLProcessor xmlProcessor;
    QList<ColsInfo>* colsInfo = xmlProcessor.readColsXml(fileName);
    if(colsInfo -> length() != 0){
        QCOMPARE(colsInfo -> at(0).dataName,firstItemName);
    }


}
void TestReadXmlData::testReadFine_data(){
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("firstItemName");
    QTest::newRow("colsXmlFileName") << ":/conf/ItemCols.xml" << "WD2";

}

