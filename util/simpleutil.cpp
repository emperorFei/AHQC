#include "simpleutil.h"
QString AHQC::TimeUtil::sdf4SMOLocFile("'smo_'yyyyMMdd'_'HHmmss'.loc'");

QString AHQC::TimeUtil::sdf4YMD("yyyyMMdd");
QTime AHQC::TimeUtil::dayDemarcationTime = QTime::fromString("200000");
QTime AHQC::TimeUtil::changeShiftsTime = QTime::fromString("163000");
int AHQC::TimeUtil::OBInterval = 6;

QString AHQC::FileNameUtil::ISOSPath = "\\\\10.126.148.90\\isos\\";
QString AHQC::stationNo = "58342";
QString AHQC::FileNameUtil::subPathBeforeStationNo = "ISOS\\dataset\\江苏\\";
QString AHQC::FileNameUtil::subPathAfterStationNo = "\\AWS\\新型自动站\\质控\\Minute\\";
QString AHQC::FileNameUtil::amFileFolderPath = ISOSPath+subPathBeforeStationNo+AHQC::stationNo+subPathAfterStationNo;

QString AHQC::TimeUtil::sdf4SMOFile = "'AWS_M_Z_"+stationNo+"_'yyyyMMdd'.txt'";
QDateTime AHQC::TimeUtil::SMOFileName2DT(QString smoFileName){
     return QDateTime::fromString(smoFileName,sdf4SMOFile);
}

QString AHQC::TimeUtil::DT2SMOFileName(QDateTime dateTime){
     return dateTime.toString(sdf4SMOFile);
}

QDate AHQC::TimeUtil::translateDateTime2AWSDay(QDateTime dateTime){
     QDate awsDay = dateTime.date();

     if(dateTime.time() > dayDemarcationTime){
        awsDay.addDays(1);
     }
     return awsDay;
}

TimeRange AHQC::TimeUtil::getFocusedTimeRange(FocusScheme* focusScheme){
    return focusScheme->getFocusRange();
}

QDateTime AHQC::TimeUtil::getPreviousDayBound(QDateTime gaveTime){
    QDateTime previousDayBound;
    int seconds = -gaveTime.time().secsTo(QTime::fromString("000000","HHmmss"));
    previousDayBound = gaveTime.addSecs(-seconds);
    previousDayBound = previousDayBound.addDays(20*60*60);
    if(seconds  < 20*60*60){
      previousDayBound.addDays(-1);
    }
    return previousDayBound;
}
QDateTime AHQC::TimeUtil::nextHour(QDateTime dateTime){
    QDateTime oneMinuteAfterTheHour = QDateTime::fromString(dateTime.toString("yyyyMMddHH"),"yyyyMMddHH").addSecs(60);
    if(dateTime >= oneMinuteAfterTheHour){
        return oneMinuteAfterTheHour.addSecs(59*60);
    }else{
        return oneMinuteAfterTheHour.addSecs(-60);
    }
}
QDateTime AHQC::TimeUtil::prevoiusOnHour(QDateTime dateTime){
    return QDateTime::fromString(dateTime.toString("yyyyMMddHH"),"yyyyMMddHH");
}


QList<QDateTime> AHQC::TimeUtil::getFocusedHours(TimeRange focusedTimeRange){
    QList<QDateTime> focusedHours ;
    QDateTime lastHour =  AHQC::TimeUtil::prevoiusOnHour(focusedTimeRange.later);
    QDateTime onHour = AHQC::TimeUtil::nextHour(focusedTimeRange.older);

    while(onHour < lastHour){
        focusedHours.append(onHour);
        onHour = onHour.addSecs(60*60);
    }
    focusedHours.append(lastHour);
    if(focusedHours.length() >= 2){
        switch(focusedTimeRange.bound) {

        case timeRange_bound::BE:
            focusedHours.pop_front();
            focusedHours.pop_back();
            break;
        case timeRange_bound::BEND:
            focusedHours.pop_front();
            break;
        case timeRange_bound::BEGINE:
            focusedHours.pop_back();
            break;
        case timeRange_bound::BEGINEND:
            break;
        default:
            break;
        }
    }
    return focusedHours;
}

QList<QString> AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(QList<QDateTime> focursedHours){
    if(focursedHours.length() == 0){
        return QList<QString>();
    }
    QList<QString> amFileNames;
    QDateTime firstHour = focursedHours.at(0);
    QDateTime lastHour = focursedHours.back();
    QDate firstAWSDay = AHQC::TimeUtil::translateDateTime2AWSDay(firstHour);
    QDate lastAWSDay = AHQC::TimeUtil::translateDateTime2AWSDay(lastHour);
    QDate tempDate = firstAWSDay;
    QString fileName("beforeGiveValue");
    while(tempDate <= lastAWSDay){
        fileName = AHQC::FileNameUtil::amFileFolderPath+tempDate.toString(AHQC::TimeUtil::sdf4SMOFile);
        amFileNames.append(fileName);
        fileName = fileName.toLocal8Bit();
        tempDate = tempDate.addDays(1);
    }
    return amFileNames;

}
QDate AHQC::FileNameUtil::getDayFormAMFileFullName(const QString &AMFileFullName){
    QString amFileName = AMFileFullName;
    amFileName = amFileName.replace(amFileFolderPath,"");
    return QDate::fromString( AHQC::TimeUtil::sdf4SMOFile);
}

//template<class T,int N>
//QString AHQC::PrintUtil::printEmbeddedArray(const T (&list)[N]){
//    int i = 0;
//    QString temp("");
//    for(T t:list){
//        temp += i+": "+list[i];
//        i++;
//    }
//    return temp;
//}

//template<class T>
//QString AHQC::PrintUtil::printList(const QList<T> &list){
//    QString temp("");
//    for(T t:list){
//        temp = temp + t;
//        temp = temp+" ";
//    }
//    return temp;
//}
