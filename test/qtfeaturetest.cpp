#include "qtfeaturetest.h"

QtFeatureTest::QtFeatureTest(QObject *parent) : QObject(parent)
{

}
QtFeatureTest::~QtFeatureTest(){}

void QtFeatureTest::testQString2Int(){
    QFETCH(QString,theString);
    QFETCH(int,intShouldBe);
    int tempInt = theString.toInt();

    QString s1("-123F");
        bool *ok1 = new bool(false);
        int t1 = s1.toInt(ok1,10);
    QString s2("14+12");
        bool *ok2 = new bool(false);
        int t2 = s2.toInt(ok2);
    QString s3("665-123");
        bool *ok3 = new bool(false);
        int t3 = s3.toInt(ok3);
    QString s4("F123");
        bool *ok4 = new bool(false);
        int t4 = s3.toInt(ok4);

    delete ok1;
    delete ok2;
    delete ok3;
    delete ok4;


    QMap<QString,int> map;
    QList<QString> list;

    if(map.empty()){
         "map: " ;
    }
    if(map.size() == 0){
       "map: ";
    }

    map.insert("m1",11);
    list.append("l1");

    int m2 = map.value("m2");
//    QString ls2 = list.at(1);

//    QList<int> list2;
//    list2.append(10);
//    int l2 = list2.at(2);

    QMap<QString,QString> map2;
    map2.insert("k1","v1");
    QString v2 = map2.value("k2");

    if(v2 == QString()){
        qDebug() << "1";
        int v2Int = v2.toInt(ok1);
       QString S =  "map: ";
    }
    if(v2 == QString("")){
        qDebug() << "2";
    }

    QMap<QString,QDateTime> map3;
    map3.insert("k1",QDateTime::fromString("20181025165326","yyyyMMddHHmmss"));
    map3.insert("k2",QDateTime::fromString("20181025165426","yyyyMMddHHmmss"));
    map3.insert("k2",QDateTime::fromString("20181025165427","yyyyMMddHHmmss"));
    map3.insert("k11",QDateTime::fromString("20181025165526","yyyyMMddHHmmss"));
    map3.insert("k21",QDateTime::fromString("20181025165626","yyyyMMddHHmmss"));

    for(const QDateTime &d: map3) {
        qDebug() << d;
    }

    QDateTime v31 = map3.value("k1");
    QDateTime v33 = map3.value("k3");


    if(v33 == QDateTime()){
        qDebug() << "1";
    }
    if(v33 == QDateTime::fromTime_t(0)){
        qDebug() << "2";
    }


    QCOMPARE(tempInt,intShouldBe);
}
void QtFeatureTest::testQString2Int_data(){
    QTest::addColumn<QString>("theString");
    QTest::addColumn<int>("intShouldBe");
    QTest::newRow("intShouldBe") << "C" << 12;

}
