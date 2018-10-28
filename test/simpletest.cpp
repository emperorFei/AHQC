#include "simpletest.h"

SimpleTest::SimpleTest(QObject *parent) : QObject(parent){}
SimpleTest::~SimpleTest(){}




void SimpleTest::testTransformDateFromSOMFileName(){
    QFETCH(QString,SMOFileName);
    QFETCH(QString,DateShouldBe);

    QCOMPARE(AHQC::TimeUtil::SMOFileName2DT(SMOFileName).toString("yyyyMMdd"),DateShouldBe);



}
void SimpleTest::testTransformDateFromSOMFileName_data(){
    QTest::addColumn<QString>("SMOFileName");
    QTest::addColumn<QString>("DateShouldBe");
    QTest::newRow("SMOFileName") << "AWS_M_Z_58342_20150724.txt" << "20150724";

}

void SimpleTest::testTransformDate2SOMFileName(){
    QFETCH(QDateTime,date);
    QFETCH(QString,SMOFileNameShouldBe);

    QCOMPARE(AHQC::TimeUtil::DT2SMOFileName(date),SMOFileNameShouldBe);
}
void SimpleTest::testTransformDate2SOMFileName_data(){
    QTest::addColumn<QDateTime>("date");
    QTest::addColumn<QString>("SMOFileNameShouldBe");
    QTest::newRow("date") << QDateTime::fromString("20150724","yyyyMMdd") << "AWS_M_Z_58342_20150724.txt";
}

void SimpleTest::testTranslateDateTime2AWSDay(){
    QFETCH(QDateTime,dateTime);
    QFETCH(QString,AWSDayShouldBe);
    //QCOMPARE(AHQC::TimeUtil::translateDateTime2AWSDay(dateTime).toString("yyyyMMdd"),AWSDayShouldBe);
}
void SimpleTest::testTranslateDateTime2AWSDay_data(){
    QTest::addColumn<QDateTime>("dateTime");
    QTest::addColumn<QString>("AWSDayShouldBe");
    QTest::newRow("dateTime") << QDateTime::fromString("20181017193351","yyyyMMddHHmmss") << "20181017";
}
void SimpleTest::testGetFocusedTimeRange(){
    QFETCH(QString,FocusedRangeShouldBe);
    QTime shiftsTime = QTime::fromString("1630","HHmm");
    ShiftsScheme shiftsScheme(shiftsTime);
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&shiftsScheme);

    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QString ssm = focusedTimeRange.older.toString("yyyyMMddHHmm")+"-"+focusedTimeRange.later.toString("yyyyMMddHHmm");
    QCOMPARE(ssm,FocusedRangeShouldBe);

}
void SimpleTest::testGetFocusedTimeRange_data(){
    QTest::addColumn<QString>("FocusedRangeShouldBe");
    QTest::newRow("range")   << "201810181630-201810181733";
}

void SimpleTest::testGetFocusedTimeRange_dayBound(){
    QFETCH(QString,FocusedRangeShouldBe);
    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);

    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QString ssm = focusedTimeRange.older.toString("yyyyMMddHHmm")+"-"+focusedTimeRange.later.toString("yyyyMMddHHmm");
    QCOMPARE(ssm,FocusedRangeShouldBe);

}
void SimpleTest::testGetFocusedTimeRange_dayBound_data(){
    QTest::addColumn<QString>("FocusedRangeShouldBe");
    QTest::newRow("range")   << "201810172000-201810181732";
}

void SimpleTest::testGetFocusedHours(){
    QFETCH(QString,HoursShouldBe);
    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QString qsb;
    for(QDateTime dt:focusedHours){
        qsb += dt.toString(" yyyyMMddHH ");
    }
    QCOMPARE(qsb,HoursShouldBe);


}
void SimpleTest::testGetFocusedHours_data(){
    QTest::addColumn<QString>("HoursShouldBe");
    QTest::newRow("Hours")   << "00";
}


void SimpleTest::testGetAMFileNamesFormFocusedHours(){
    QFETCH(QString,FileNamesShouldBe);
    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QList<QString> amFileNames = AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(focusedHours);
    QString qsb;
    for(QString ss : amFileNames){
        qDebug() << ss;
        qsb += " " + ss + " ";
    }
    QCOMPARE(qsb,FileNamesShouldBe);
    QString qsb1;
}
void SimpleTest::testGetAMFileNamesFormFocusedHours_data(){
    QTest::addColumn<QString>("FileNamesShouldBe");
    QTest::newRow("Hours")   << "00";
}

//template<>
//GlobalSetting* singleton<GlobalSetting>::GetInstance();
void SimpleTest::testGlobalSettingInit(){

    QFETCH(QString,GlobalSettingShouldBe);
    //int* global = singleton<int>::GetInstance();
    GlobalSetting * global = singleton<GlobalSetting>::GetInstance();
    //GlobalSetting * global = GlobalSetting::getInstance();
    //QCOMPARE(QString::number(*global),GlobalSettingShouldBe);
    QCOMPARE(global->toString(),GlobalSettingShouldBe);
    int i = 0;//debug before flow end;
}
void SimpleTest::testGlobalSettingInit_data(){
    QTest::addColumn<QString>("GlobalSettingShouldBe");
    QTest::newRow("GlobalSetting")   << "00";
}


void SimpleTest::testReadAMFile(){
    QFETCH(QString,AMDataShouldBe);
    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
    QList<QString> amFileNames = AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(focusedHours);
    QString line("beforeInit");
    QList<AWSMinuteData> awsMinuteDatas;
    for(QString amFileName:amFileNames){
        QFile amFile(amFileName);
        if(amFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream amIn(&amFile);
            QDate awsDay = QDate::fromString(amFileName.replace(AHQC::FileNameUtil::amFileFolderPath,""),AHQC::TimeUtil::sdf4SMOFile);

            if(!amIn.atEnd()){
                line = amIn.readLine();
                while(!amIn.atEnd()){
                    line = amIn.readLine();
                    if(line.compare("") != 0 && line.at(0) != '-'){
                        AWSMinuteData awsMinuteData(awsDay,line);
                        awsMinuteDatas.append(awsMinuteData);
                    }
                }
            }
            amFile.close();
        }
    }
    qDebug() << awsMinuteDatas.first().toString();
    if(awsMinuteDatas.length()!=0){
        QCOMPARE(awsMinuteDatas.first().toString(),AMDataShouldBe);
    }
    QString qsb1;
}
void SimpleTest::testReadAMFile_data(){
    QTest::addColumn<QString>("AMDataShouldBe");
    QTest::newRow("AMData")   << "00";
}

void SimpleTest::testReadNull(){

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

void SimpleTest::testReadNull_data(){
    QTest::addColumn<QString>("LineShouldBe");
    QTest::newRow("line")   << "00";
}


//void SimpleTest::testExecuteSqlScript(){

//    QFETCH(QString,ExecuteSqlScript);


//    QString scriptFileName = "F:/GitRepository/AHQC/configs/createMySqlTable.sql";
//    QSqlDatabase *conn = DBCenter::getDBByAccountType(DBCenter::AccountType::ADMIN);
//    SqlFileExecutor sqlFileExecutor;
//    sqlFileExecutor.execute(conn,scriptFileName);
//    DBCenter::cleanCreatedConns();
//    QCOMPARE("estExecuteSqlScript result",ExecuteSqlScript);
//    int i = 0;//debug before flow end;
//}
//void SimpleTest::testExecuteSqlScript_data(){
//    QTest::addColumn<QString>("ExecuteSqlScript");
//    QTest::newRow("testExecuteSqlScript")   << "00";
//}
