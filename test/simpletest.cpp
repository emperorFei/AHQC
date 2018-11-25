﻿#include "simpletest.h"

SimpleTest::SimpleTest(QObject *parent) : QObject(parent){}
SimpleTest::~SimpleTest(){}




void SimpleTest::testDate2AMFileName(){
    QFETCH(QDate,date);
    QFETCH(QString,AMFileNameShouldBe);
    QString amFileName(AHQC::FileNameUtil::Date2AMFileName(date));
    //qDebug() << amFileName;
    QString amFileNameWithoutPath(AHQC::FileNameUtil::AMFUllName2ShortName(amFileName));
    QCOMPARE(amFileNameWithoutPath,AMFileNameShouldBe);
}
void SimpleTest::testDate2AMFileName_data(){
    QTest::addColumn<QDate>("date");
    QTest::addColumn<QString>("AMFileNameShouldBe");
    QTest::newRow("date") << QDate::fromString("20150724","yyyyMMdd") << "AWS_M_Z_58342_20150724.txt";
}
void SimpleTest::testAMFileName2Date(){
    QFETCH(QString,AMFileName);
    QFETCH(QString,DateShouldBe);
    QString dateString = AHQC::FileNameUtil::AMFileName2Date(AMFileName).toString("yyyyMMdd");
    QCOMPARE(dateString,DateShouldBe);
}
void SimpleTest::testAMFileName2Date_data(){
    QTest::addColumn<QString>("AMFileName");
    QTest::addColumn<QString>("DateShouldBe");
    QTest::newRow("AMFileName") << "AWS_M_Z_58342_20150724.txt" << "20150724";

}
void SimpleTest::testDateTime2ZFileName(){
    QFETCH(QDateTime,dateTime);
    QFETCH(QString,ZFileNameShouldBe);
    QString zFileName(AHQC::FileNameUtil::DateTime2ZFileName(dateTime));
    //qDebug() << zFileName;
    QString zFileNameWithoutPath(AHQC::FileNameUtil::zFUllName2ShortName(zFileName));
    QCOMPARE(zFileNameWithoutPath,ZFileNameShouldBe);
}
void SimpleTest::testDateTime2ZFileName_data(){
    QTest::addColumn<QDateTime>("dateTime");
    QTest::addColumn<QString>("ZFileNameShouldBe");
    QTest::newRow("dateTime") << QDateTime::fromString("20181121120000","yyyyMMddHHmmss") << "Z_SURF_I_58342_20181121040000_O_AWS_FTM-CCA.txt";
}
void SimpleTest::testZFileName2DateTime(){
    QFETCH(QString,ZFileName);
    QFETCH(QString,DateTimeShouldBe);
    QCOMPARE(AHQC::FileNameUtil::ZFileName2DateTime(ZFileName).toString("yyyyMMddHHmmss"),DateTimeShouldBe);
}
void SimpleTest::testZFileName2DateTime_data(){
    QTest::addColumn<QString>("ZFileName");
    QTest::addColumn<QString>("DateTimeShouldBe");
    QTest::newRow("ZFileName") << "Z_SURF_I_58342_20180731200000_O_AWS_FTM.txt" << "20180801040000";
}

void SimpleTest::testDateTime2AWSDay(){
    QFETCH(QDateTime,dateTime);
    QFETCH(QString,AWSDayShouldBe);
    QCOMPARE(AHQC::TimeUtil::dateTime2AWSDay(dateTime).toString("yyyyMMdd"),AWSDayShouldBe);
}
void SimpleTest::testDateTime2AWSDay_data(){
    QTest::addColumn<QDateTime>("dateTime");
    QTest::addColumn<QString>("AWSDayShouldBe");
    QTest::newRow("dateTime") << QDateTime::fromString("20181017193351","yyyyMMddHHmmss") << "20181017";
}
void SimpleTest::testDateTime2AWSMonth(){
    QFETCH(QDateTime,dateTime);
    QFETCH(QString,AWSMonthShouldBe);
    QCOMPARE(AHQC::TimeUtil::dateTime2AWSMonth(dateTime).toString("yyyyMMdd"),AWSMonthShouldBe);
}
void SimpleTest::testDateTime2AWSMonth_data(){
    QTest::addColumn<QDateTime>("dateTime");
    QTest::addColumn<QString>("AWSMonthShouldBe");
    QTest::newRow("dateTime") << QDateTime::fromString("20181031220351","yyyyMMddHHmmss") << "20181101";
}

void SimpleTest::testGetFocusedTimeRange(){
    QFETCH(QString,FocusedRangeShouldBe);
    QTime shiftsTime = QTime::fromString("1630","HHmm");
    ShiftsScheme shiftsScheme(shiftsTime);
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&shiftsScheme);

    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QString timeRangeString = focusedTimeRange.older.toString("yyyyMMddHHmm")+"-"+focusedTimeRange.later.toString("yyyyMMddHHmm");
    QCOMPARE(timeRangeString,FocusedRangeShouldBe);

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
void SimpleTest::testGetZFileNamesFormFocusedHours(){
    QFETCH(QString,ZFileNamesShouldBe);
    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
    //QCOMPARE(focusedTimeRange.older.toString("HHmm"),FocusedRangeShouldBe);
    QList<QString> amFileNames = AHQC::FileNameUtil::getZFileNamesFormFocusedHours(focusedHours);
    QString qsb;
    for(QString ss : amFileNames){
        qDebug() << ss;
        qsb += " " + ss + " ";
    }
    QCOMPARE(qsb,ZFileNamesShouldBe);
    QString qsb1;
}
void SimpleTest::testGetZFileNamesFormFocusedHours_data(){
    QTest::addColumn<QString>("ZFileNamesShouldBe");
    QTest::newRow("Hours")   << "00";
}

void SimpleTest::testGlobalSettingInit(){
    QFETCH(QString,GlobalSettingShouldBe);
    GlobalSetting * global = singleton<GlobalSetting>::GetInstance();
    QCOMPARE(global->toString(),GlobalSettingShouldBe);
}
void SimpleTest::testGlobalSettingInit_data(){
    QTest::addColumn<QString>("GlobalSettingShouldBe");
    QTest::newRow("GlobalSetting")   << "00";
}




//void SimpleTest::testReadAMFile(){
//    QFETCH(QString,AMDataShouldBe);
//    DayBoundScheme dbScheme;
//    TimeRange focusedTimeRange = AHQC::TimeUtil::getFocusedTimeRange(&dbScheme);
//    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
//    QList<QString> amFileNames = AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(focusedHours);
//    if(amFileNames.isEmpty()){
//        qDebug() << "no amFiles between "<< focusedTimeRange.toQString() << "found in " << AHQC::isosPath;
//        return;
//    }
//    QString line("beforeInit");
//    QList<AWSMinuteData> awsMinuteDatas;
//    for(QString amFileName:amFileNames){
//        QFile amFile(amFileName);
//        if(amFile.exists()){
//            if(amFile.open(QIODevice::ReadOnly|QIODevice::Text)){
//                QTextStream amIn(&amFile);
//                QDate awsDay = AHQC::FileNameUtil::AMFileName2Date(amFileName);
//                if(!amIn.atEnd()){
//                    line = amIn.readLine();
//                    while(!amIn.atEnd()){
//                        line = amIn.readLine();
//                        if(line.compare("") != 0 && line.at(0) != '-'){
//                            AWSMinuteData awsMinuteData(awsDay,line);
//                            awsMinuteDatas.append(awsMinuteData);
//                        }
//                    }
//                }
//                amFile.close();
//            }else{
//                qDebug() << "file: " << amFileName << "can't open";
//                return ;
//            }
//        }else{
//            qDebug() << "file: " << amFileName << "not exists";
//            return ;
//        }
//    }

//    qDebug() << awsMinuteDatas.first().toString();
//    if(awsMinuteDatas.length()!=0){
//        QCOMPARE(awsMinuteDatas.first().toString(),AMDataShouldBe);
//    }
//    QString qsb1;
//}
//void SimpleTest::testReadAMFile_data(){
//    QTest::addColumn<QString>("AMDataShouldBe");
//    QTest::newRow("AMData")   << "00";
//}

void SimpleTest::testReadAMFile(){
    QFETCH(QString,AMDataShouldBe);
    QFETCH(QString,AMFileName);
    QFile amFile(AMFileName);
    QList<AWSMinuteData> awsMinuteDatas;
    if(amFile.exists()){
        if(amFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream amIn(&amFile);
            QDate awsDay = AHQC::FileNameUtil::AMFileName2Date(AMFileName);
            QString line("");
            if(!amIn.atEnd()){
                line = amIn.readLine();
                while(!amIn.atEnd()){
                    line = amIn.readLine();
                    if(!line.isEmpty() && line.at(0) != '-'){
                        AWSMinuteData awsMinuteData(awsDay,line);
                        awsMinuteDatas.append(awsMinuteData);
                    }
                }
            }
            amFile.close();
        }else{
            qDebug() << "file: " << AMFileName << "can't open";
            return ;
        }
    }else{
        qDebug() << "file: " << AMFileName << "not exists";
        return ;
    }
    qDebug() << awsMinuteDatas.first().toString();
    if(awsMinuteDatas.length()!=0){
        QCOMPARE(awsMinuteDatas.first().toString(),AMDataShouldBe);
    }
}
void SimpleTest::testReadAMFile_data(){
    QTest::addColumn<QString>("AMDataShouldBe");
    QTest::addColumn<QString>("AMFileName");
    QTest::newRow("AMData")   << "00" << AHQC::FileNameUtil::Date2AMFileName(QDate::fromString("20181121","yyyyMMdd"));
}
void SimpleTest::testReadZFile(){
    QFETCH(QString,ZDataShouldBe);
    QFETCH(QString,ZFileName);
    QFile zFile(ZFileName);
    ZData zData = ZData::fromZFile(ZFileName);;
    if(!zFile.exists()){
        qDebug() << "file: " << ZFileName << "not exists";
        return ;
    }
    if(!zData.isTotalInited()){
        qDebug() << "file: " << ZFileName << " exists, but read error.";
        return ;
    }
    QCOMPARE(zData.toString(),ZDataShouldBe);
}
void SimpleTest::testReadZFile_data(){
    QTest::addColumn<QString>("ZDataShouldBe");
    QTest::addColumn<QString>("ZFileName");
    QTest::newRow("ZData")   << "00" << AHQC::FileNameUtil::DateTime2ZFileName(QDateTime::fromString("20181121120000","yyyyMMddHHmmss"));
}

void SimpleTest::testGetZFileNames(){
    QFETCH(QString,FileNamesShouldBe);
//    DayBoundScheme dbScheme;
    TimeRange focusedTimeRange = TimeRange(
                QDateTime::fromString("20170930193000","yyyyMMddHHmmss"),
                QDateTime::fromString("20171201203000","yyyyMMddHHmmss"),
                timeRange_bound::BEND);

    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(focusedTimeRange);
    QList<QString> zFileNames = AHQC::FileNameUtil::getZFileNamesFormFocusedHours(focusedHours);
    if(zFileNames.isEmpty()){
        qDebug() << "no zFiles between "<< focusedTimeRange.toQString() << "found in " << AHQC::isosPath;
    }
    QString qsb;
    for(QString ss : zFileNames){
        if(ss.indexOf(QRegExp("FTM-CC[A-Z]")) != -1){
            qDebug() << ss;
            qsb += " " + ss + " ";
        }
    }
    QCOMPARE(qsb,FileNamesShouldBe);
    QString qsb1;
}
void SimpleTest::testGetZFileNames_data(){
    QTest::addColumn<QString>("FileNamesShouldBe");
    QTest::newRow("Hours")   << "00";
}


void SimpleTest::testGetConnect(){
    QSqlDatabase *sqlDatabase =  DBCenter::getDBByAccountType(DBCenter::AccountType::QIU);
    if(sqlDatabase!=Q_NULLPTR && sqlDatabase->open()){
       qDebug() <<"db open seccess";
       sqlDatabase->close();
    }else{
       qDebug() <<"db open fault";
    }
}
void SimpleTest::testGetConnect_data(){

}
void SimpleTest::testSaveAWSMinuteData(){

}
void SimpleTest::testSaveAWSMinuteData_data(){

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
