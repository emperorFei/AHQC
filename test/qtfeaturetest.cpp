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
void QtFeatureTest::testReadNull(){

    QMap<QString,int> map;
    QList<QString> list;
    int mapLen = map.size();
    int listLen = list.length();
    int cc = 20;

    map.insert("da",10);
    list.append("asc");
    QFETCH(QString,LineShouldBe);

    QFile amFile("D:/testReadNull.txt");
    if(amFile.open(QIODevice::ReadOnly|QIODevice::Text)){
         QTextStream amIn(&amFile);
         QString line1 = amIn.readLine();
         int i2 = 10;
         QString line2 = amIn.readLine();
         int i3 = 10;
         QString line3 = amIn.readLine();
         int i4 = 10;
    }
    //GlobalSetting * global = GlobalSetting::getInstance();
    //QCOMPARE(QString::number(*global),GlobalSettingShouldBe);
    QCOMPARE("aaaa",LineShouldBe.toStdString().c_str());
    int i = 0;//debug before flow end;
}
void QtFeatureTest::testReadNull_data(){
    QTest::addColumn<QString>("LineShouldBe");
    QTest::newRow("line")   << "00";
}
void QtFeatureTest::testRegLookBehind(){
    QString target("_20170120120001_");
    QRegExp reg1("[0-9]{14}");
    QRegExp reg2("(?<=_)[0-9]{14}");
    QRegExp reg3("(?<=_)[0-9]{14}(?=_)");
    QRegExp reg4("(?<=_)[0-9]{14}(?<=_)");
    QRegExp reg5("[0-9]{14}(?=_)");
    int index1 = reg1.indexIn(target);
    int len1 = reg1.matchedLength();
    int index2 = reg2.indexIn(target);
    int len2 = reg2.matchedLength();
    int index3 = reg3.indexIn(target);
    int len3 = reg3.matchedLength();
    int index4 = reg4.indexIn(target);
    int len4 = reg4.matchedLength();
    int index5 = reg5.indexIn(target);
    int len5 = reg5.matchedLength();
    QString s1(target.mid(index5,len5));
    int end = 10;

}
void QtFeatureTest::testRegLookBehind_data(){
}


void QtFeatureTest::testInsertCause(){
    QSqlDatabase sqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    sqlDatabase.setHostName("localhost");
    sqlDatabase.setPort(3306);
    sqlDatabase.setDatabaseName("tempdb");
    sqlDatabase.setUserName("fei");
    sqlDatabase.setPassword("tiger");
    QSqlQuery transaction_start(sqlDatabase);
    QSqlQuery transaction_COMMIT(sqlDatabase);
    QSqlQuery transaction_ROLLBACK(sqlDatabase);
    if(sqlDatabase.open()){
        bool start = transaction_start.exec("START TRANSACTION");
        QSqlQuery query(sqlDatabase);
        query.prepare("insert into insertTest values(0,?,?)");
        for(int i=0;i<=100000;i++){
            query.bindValue(0,QVariant(1000+i));
            query.bindValue(1,QVariant("title"+QString::number(i)));
            bool successed = query.exec();
            qDebug() << i <<
                        " inseret " << (successed == true ? "success": "fault")
                        << query.lastError().databaseText();
        }
        bool commit = transaction_COMMIT.exec("COMMIT");
        int i = 10;
        qDebug() << i;

    }
    QString c("end");
    qDebug() << c;
}
void QtFeatureTest::testInsertCause_data(){

}
