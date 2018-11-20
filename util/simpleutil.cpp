#include "simpleutil.h"

QString AHQC::stationNo = "58342";
QString AHQC::isosPath = "\\\\10.126.148.90\\isos\\ISOS";
QString AHQC::minuteDataPathTemplate =  "\\dataset\\江苏\\#{stationNum}\\AWS\\新型自动站\\质控\\minute";
QString AHQC::zFilePathTemplate = "\\bin\\Awsnet\\#{month}";
QString AHQC::AMFileNameTemplate = "AWS_M_Z_#{stationNum}_#{Date}.txt";
QString AHQC::ZFileNameTemplate = "Z_SURF_I_#{stationNum}_#{DateTime}_O_AWS_FTM#{ccx}.txt";
QString AHQC::AMFileFullNameTemplate = "#{isosPath}\\dataset\\江苏\\#{stationNum}\\AWS\\新型自动站\\质控\\minute\\AWS_M_Z_#{stationNum}_#{Date}.txt";
QString AHQC::ZFileFullNameTemplate = "#{isosPath}\\bin\\Awsnet\\#{month}\\Z_SURF_I_#{stationNum}_#{DateTime}_O_AWS_FTM#{ccx}.txt";
QRegExp AHQC::amFileNameReg("AWS_M_Z_.*[\\.txt|\\.TXT]");
QRegExp AHQC::zFileNameReg("Z_SURF_I_.*[\\.txt|\\.TXT]");

QString AHQC::TimeUtil::sdf4SMOLocFile("'smo_'yyyyMMdd'_'HHmmss'.loc'");
QString AHQC::TimeUtil::sdf4AMFile = "'AWS_M_Z_#{stationNum}_'yyyyMMdd'.txt'";

QTime AHQC::TimeUtil::dayDemarcationTime = QTime::fromString("200000","HHmmss");
QTime AHQC::TimeUtil::changeShiftsTime = QTime::fromString("163000","HHmmss");
int AHQC::TimeUtil::OBInterval = 6;





QDate AHQC::FileNameUtil::AMFileName2Date(const QString &AMFileName){
    if(AMFileName.isEmpty()){
        int startIndex = amFileNameReg.indexIn(AMFileName);
        int len = AMFileName.length() - startIndex;
        QString usingSdf4AMFile(QString(AHQC::TimeUtil::sdf4AMFile).replace("#{stationNum}",AHQC::stationNo));
        return QDate::fromString(AMFileName.mid(startIndex,len),usingSdf4AMFile);
    }
    return QDate();
}

QString AHQC::FileNameUtil::Date2AMFileName(const QDate &date){
    QString AMFileFullNameTemplateNeedDate(QString(AHQC::AMFileFullNameTemplate)
                                            .replace("#{isosPath}",AHQC::isosPath)
                                            .replace("#{stationNum}",AHQC::stationNo));
    return AMFileFullNameTemplateNeedDate.replace("#{Date}",date.toString("yyyyMMdd"));
}

QDateTime AHQC::FileNameUtil::ZFileName2DT(const QString &ZFileName){
    if(ZFileName.isEmpty()){
        int startIndex = zFileNameReg.indexIn(ZFileName);
        int len = ZFileName.length() - startIndex;
        QString zFileNameWithoutPath = ZFileName.mid(startIndex,len);
        QRegExp datatimeStringReg("(?<=_)[0-9]{12}(?=_)");
        int datatimeStringIndex =  datatimeStringReg.indexIn(zFileNameWithoutPath);
        if(datatimeStringIndex >= 0){
            return QDateTime::fromString(zFileNameWithoutPath.mid(datatimeStringIndex,12),"yyyyMMddHHmmss");
        }
    }
    return QDateTime();
}

QString AHQC::FileNameUtil::DT2ZFileName(const QDateTime &dateTime){
    QString ZFileFullNameTemplateNeedTime(QString(AHQC::ZFileFullNameTemplate)
                                            .replace("#{isosPath}",AHQC::isosPath)
                                            .replace("#{stationNum}",AHQC::stationNo));
    return ZFileFullNameTemplateNeedTime.replace("#{DateTime}",dateTime.toUTC().toString("yyyyMMddHHmmss"));
}

QDate AHQC::TimeUtil::translateDateTime2AWSDay(QDateTime dateTime){
     QDate awsDay = dateTime.date();

     if(dateTime.time() > dayDemarcationTime){
        awsDay = awsDay.addDays(1);
     }
     return awsDay;
}
QDate AHQC::TimeUtil::translateDateTime2AWSMonth(QDateTime dateTime){
    QDate awsMonth = dateTime.date();
    if(dateTime.time() > dayDemarcationTime){
       awsMonth = awsMonth.addDays(1);
    }
    awsMonth = QDate::fromString(awsMonth.toString("yyyyMM"),"yyyyMM");
    return awsMonth;
}

TimeRange AHQC::TimeUtil::getFocusedTimeRange(FocusScheme* focusScheme){
    return focusScheme->getFocusRange();
}

QDateTime AHQC::TimeUtil::getPreviousDayBound(QDateTime gaveTime){
    QDateTime previousDayBound;
    int seconds = -gaveTime.time().secsTo(QTime::fromString("000000","HHmmss"));
    previousDayBound = gaveTime.addSecs(-seconds);
    previousDayBound = previousDayBound.addSecs(20*60*60);
    if(seconds  < 20*60*60){
      previousDayBound = previousDayBound.addDays(-1);
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

    while(onHour <= lastHour){
        focusedHours.append(onHour);
        onHour = onHour.addSecs(60*60);
    }
    if(focusedTimeRange.older.toString("mmss") == "0000"){
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
    }
    return focusedHours;
}

TimeRange AHQC::TimeUtil::getTimeRange(const QDateTime &onTime,int hours){
    QDateTime older = onTime.addSecs(-hours*60*60);
    QDateTime later = onTime;
    return TimeRange(older,later,timeRange_bound::BEGINEND);
}

TimeRange AHQC::TimeUtil::getTimeRange4Sum(const QDateTime &onTime,int hours){
    QDateTime older = onTime.addSecs(-hours*60*60);
    QDateTime later = onTime;
    return TimeRange(older,later,timeRange_bound::BEND);
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
    QString amFileNameTemplateNeedTime(QString(AHQC::AMFileFullNameTemplate)
                                              .replace("#{isosPath}",AHQC::isosPath)
                                              .replace("#{stationNum}",AHQC::stationNo));
    QString usingSdf4AMFile = QString(AHQC::TimeUtil::sdf4AMFile).replace("#{stationNum}",AHQC::stationNo);
    QString fileName("beforeGiveValue");
    while(tempDate <= lastAWSDay){
        fileName = QString(amFileNameTemplateNeedTime).replace("#{Date}",tempDate.toString("yyyyMMdd"));
        amFileNames.append(fileName);
        fileName = fileName.toLocal8Bit();
        tempDate = tempDate.addDays(1);
    }
    return amFileNames;

}

QList<QString> AHQC::FileNameUtil::getZFileNamesFormFocusedHours(QList<QDateTime> focursedHours){
    if(focursedHours.length() == 0){
        return QList<QString>();
    }
    QList<QString> zFileNames;
    QString fileName("beforeGiveValue");

    QDateTime firstHour = focursedHours.at(0);
    QDateTime lastHour = focursedHours.back();
    QDateTime tempHour(firstHour);
    QDate firstAWSMonth = AHQC::TimeUtil::translateDateTime2AWSMonth(firstHour);
    //QDate lastAWSMonth = AHQC::TimeUtil::translateDateTime2AWSMonth(lastHour);
    QDate tempMonth(firstAWSMonth);
    QString tempMonthString(tempMonth.toString("yyyyMM"));
    QString zFileNameTemplateNeedMonthAndTime(QString(AHQC::ZFileFullNameTemplate)
                                              .replace("#{isosPath}",AHQC::isosPath)
                                              .replace("#{stationNum}",AHQC::stationNo)
                                              .replace("#{ccx}",""));
    QString zFileNameTemplateNeedTime(QString(zFileNameTemplateNeedMonthAndTime)
                                      .replace("#{month}",tempMonthString));
    QDateTime firstMinuteOfFirstMonth = QDateTime::fromString(firstAWSMonth.addDays(-1).toString("yyyyMMdd")+"2001","yyyyMMddHHmm");
    QDateTime lastMinuteOfFirstMonth = QDateTime::fromString(firstAWSMonth.addMonths(1).addDays(-1).toString("yyyyMMdd")+"2000","yyyyMMddHHmm");

    //QDateTime firstMinuteOfLastMonth = QDateTime::fromString(lastAWSMonth.addDays(-1).toString("yyyyMMdd")+"2001","yyyyMMddHHmm");
    //QDateTime lastMinuteOfLastMonth = QDateTime::fromString(lastAWSMonth.addMonths(1).addDays(-1).toString("yyyyMMdd")+"2000","yyyyMMddHHmm");

    QDateTime firstMinuteOfTheMonth(firstMinuteOfFirstMonth);
    QDateTime lastMinuteOfTheMonth(lastMinuteOfFirstMonth);
    if(lastHour <= lastMinuteOfFirstMonth){
        while(tempHour <= lastHour){
            fileName = QString(zFileNameTemplateNeedTime)
                    .replace("#{DateTime}",
                             tempHour.toUTC().toString("yyyyMMddHHmmss"));
            fileName = findCCXZFileNameFromPlanFileName(fileName);
            zFileNames.append(fileName);
            tempHour = tempHour.addSecs(3600);
        }
    }else{
        while( lastMinuteOfTheMonth < lastHour){
            while(tempHour <= lastMinuteOfTheMonth){
                fileName = QString(zFileNameTemplateNeedTime)
                        .replace("#{DateTime}",
                                 tempHour.toUTC().toString("yyyyMMddHHmmss"));
                fileName = findCCXZFileNameFromPlanFileName(fileName);
                zFileNames.append(fileName);
                tempHour = tempHour.addSecs(3600);
            }
            tempMonth = tempMonth.addMonths(1);
            tempMonthString = tempMonth.toString("yyyyMM");
            zFileNameTemplateNeedTime = QString(zFileNameTemplateNeedMonthAndTime).replace("#{month}",tempMonthString);
            lastMinuteOfTheMonth = QDateTime::fromString(tempMonth.addMonths(1).addDays(-1).toString("yyyyMMdd")+"2000","yyyyMMddHHmm");
        }
        while(tempHour <= lastHour){
            fileName = QString(zFileNameTemplateNeedTime)
                                .replace("#{DateTime}",
                                         tempHour.toUTC().toString("yyyyMMddHHmmss"));
            fileName = findCCXZFileNameFromPlanFileName(fileName);
            zFileNames.append(fileName);
            tempHour = tempHour.addSecs(3600);
        }
    }
    return zFileNames;

}



inline QString AHQC::FileNameUtil::findCCXZFileNameFromPlanFileName(const QString &planZFileName){
    QString fileName(planZFileName);
    QChar ccx('A');
    QString ccafileName = QString(fileName).replace("FTM","FTM-CC"+QString(ccx));
    QFile * tempFilePtr = new QFile(ccafileName);

    while(tempFilePtr->exists()){
       fileName = ccafileName;
       delete tempFilePtr;
       ccafileName = QString(ccafileName).replace("FTM-CC"+QString(ccx),"FTM-CC"+QString(ccx+1));
       tempFilePtr = new QFile(ccafileName);
    }
    delete tempFilePtr;
    return fileName;
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
