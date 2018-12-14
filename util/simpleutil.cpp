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
QList<QString> AHQC::defaultQCItemNames =
{
   "CA","CH","E","ET","ET10","ET15","ET160","ET20","ET320",
   "ET40","ET5","ET80","ExWD","ExWD12","ExWD6","ExWS","ExWS12",
   "ExWS6","ExWST","GT",
   "HRain","HRain12","HRain24",
   "HRain3","HRain6","LCA",
   "MaxET","MaxETT","MaxGT","MaxGTT",
   "MaxP","MaxPT","MaxT","MaxT24","MaxTT",
   "MaxWD","MaxWS","MaxWST","MinET","MinET12",
   "MinETT","MinGT","MinGTT","MinP","MinPT","MinRH",
   "MinRHT","MinT","MinT24","MinTT","MinV",
   "MinVT","P","RH","SP","SnowD","T",
   "TD","V1","V10","VP24","VP3","VT24",
   "WD","WD10","WD2","WP","WS","WS10","WS2",
   "CCX","CF","CFC","EC","FE1D","FE1U","FE2D","FE2U","GA","HA"
};
QList<QString> AHQC::QCItemNames =
{
   "CA","CH","E","ET","ET10","ET15","ET160","ET20","ET320",
   "ET40","ET5","ET80","ExWD","ExWD12","ExWD6","ExWS","ExWS12",
   "ExWS6","ExWST","GT",
   "HRain","HRain12","HRain24",
   "HRain3","HRain6","LCA",
   "MaxET","MaxETT","MaxGT","MaxGTT",
   "MaxP","MaxPT","MaxT","MaxT24","MaxTT",
   "MaxWD","MaxWS","MaxWST","MinET","MinET12",
   "MinETT","MinGT","MinGTT","MinP","MinPT","MinRH",
   "MinRHT","MinT","MinT24","MinTT","MinV",
   "MinVT","P","RH","SP","SnowD","T",
   "TD","V1","V10","VP24","VP3","VT24",
   "WD","WD10","WD2","WP","WS","WS10","WS2",
   "CCX","CF","CFC","EC","FE1D","FE1U","FE2D","FE2U","GA","HA"
};

QList<QString> AHQC::hideWidget =
{
   "CF_DL","CF_label"
};


QString AHQC::TimeUtil::sdf4SMOLocFile("'smo_'yyyyMMdd'_'HHmmss'.loc'");
QString AHQC::TimeUtil::sdf4AMFile = "'AWS_M_Z_#{stationNum}_'yyyyMMdd'.txt'";

QTime AHQC::TimeUtil::dayDemarcationTime = QTime::fromString("200000","HHmmss");
QTime AHQC::TimeUtil::changeShiftsTime = QTime::fromString("163000","HHmmss");
int AHQC::TimeUtil::OBInterval = 6;


int AHQC::connectToShareDfolder(){
    GlobalSetting *globalSetting = GlobalSetting::getInstance();

}



QDate AHQC::TimeUtil::dateTime2AWSDay(const QDateTime &dateTime){
     QDate awsDay = dateTime.date();
     if(dateTime.time() > dayDemarcationTime){
        awsDay = awsDay.addDays(1);
     }
     return awsDay;
}
QDate AHQC::TimeUtil::dateTime2AWSMonth(const QDateTime &dateTime){
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

QDateTime AHQC::TimeUtil::getPreviousDayBound(const QDateTime &gaveTime){
    QDateTime previousDayBound;
    int seconds = -gaveTime.time().secsTo(QTime::fromString("000000","HHmmss"));
    previousDayBound = gaveTime.addSecs(-seconds);
    previousDayBound = previousDayBound.addSecs(20*60*60);
    if(seconds  < 20*60*60){
      previousDayBound = previousDayBound.addDays(-1);
    }
    return previousDayBound;
}
QDateTime AHQC::TimeUtil::nextHour(const QDateTime &dateTime){
    if(dateTime.toString("mmss") == "0000"){
       return  QDateTime(dateTime);
    }else{
       return QDateTime::fromString(dateTime.toString("yyyyMMddHH"),"yyyyMMddHH").addSecs(60*60);
    }
}
inline QDateTime AHQC::TimeUtil::prevoiusOnHour(const QDateTime &dateTime){
    return QDateTime::fromString(dateTime.toString("yyyyMMddHH"),"yyyyMMddHH");
}


QList<QDateTime> AHQC::TimeUtil::getFocusedHours(const TimeRange &focusedTimeRange){
    QList<QDateTime> focusedHours ;
    QDateTime lastHour =  AHQC::TimeUtil::prevoiusOnHour(focusedTimeRange.later);
    QDateTime onHour = AHQC::TimeUtil::nextHour(focusedTimeRange.older);
    QDateTime previousZSendTime = previousOnTimeZSendTime();
    QDateTime now = QDateTime::currentDateTime();
    if(!QFile(AHQC::FileNameUtil::DateTime2ZFileName(onHour)).exists()){
        return focusedHours;
    }else if(!QFile(AHQC::FileNameUtil::DateTime2ZFileName(lastHour)).exists()){
        lastHour = previousOnTimeZSendTime();
    }
    if(onHour > lastHour){
        focusedHours.append(lastHour);
        return focusedHours;
    }
    while(onHour <= lastHour){
        focusedHours.append(onHour);
        onHour = onHour.addSecs(60*60);
    }
    if(focusedHours.length() >= 2 ){
        if(focusedTimeRange.older.toString("mmss") == "0000"){
            if(focusedTimeRange.bound == timeRange_bound::BE
                    || focusedTimeRange.bound == timeRange_bound::BEND ){
                focusedHours.pop_front();
            }
        }
        if(focusedTimeRange.later.toString("mmss") == "0000"){
            if(focusedTimeRange.bound == timeRange_bound::BEGINE
                    || focusedTimeRange.bound == timeRange_bound::BEGINE ){
                focusedHours.pop_back();
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
    older = older.addSecs(-60);
    QDateTime later = onTime;
    return TimeRange(older,later,timeRange_bound::BEND);
}

QDateTime AHQC::TimeUtil::previousOnTimeZSendTime(){
    QDateTime now = QDateTime::currentDateTime();
    QDateTime previousHour = AHQC::TimeUtil::prevoiusOnHour(now);
    QString zFileName = AHQC::FileNameUtil::DateTime2ZFileName(previousHour);
    if(QFile(zFileName).exists()){
        return previousHour;
    }else{
        return previousHour.addSecs(-60*60);
    }
}

QDate AHQC::FileNameUtil::AMFileName2Date(const QString &AMFileName){
    if(!AMFileName.isEmpty()){
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

QDateTime AHQC::FileNameUtil::ZFileName2DateTime(const QString &ZFileName){
    if(!ZFileName.isEmpty()){
        int startIndex = zFileNameReg.indexIn(ZFileName);
        int len = ZFileName.length() - startIndex;
        QString zFileNameWithoutPath = ZFileName.mid(startIndex,len);
        QRegExp datatimeStringReg("[0-9]{14}");
        int datatimeStringIndex =  datatimeStringReg.indexIn(zFileNameWithoutPath);
        if(datatimeStringIndex >= 0){
            QDateTime utcDateTime(
                        QDateTime::fromString(zFileNameWithoutPath.mid(datatimeStringIndex,14)
                                              ,"yyyyMMddHHmmss"));
            QDateTime observeTime(utcDateTime.addSecs(60*60*8));
            return observeTime;
        }
    }
    return QDateTime();
}

QString AHQC::FileNameUtil::DateTime2ZFileName(const QDateTime &dateTime){
    QDateTime utcTime(dateTime.addSecs(-60*60*8));
    QString ZFileFullNameTemplateNeedTime(QString(AHQC::ZFileFullNameTemplate)
                                            .replace("#{isosPath}",AHQC::isosPath)
                                            .replace("#{stationNum}",AHQC::stationNo)
                                            .replace("#{ccx}",""));
    QString zFileName = ZFileFullNameTemplateNeedTime.replace("#{DateTime}",utcTime.toString("yyyyMMddHHmmss"))
                                        .replace("#{month}",AHQC::TimeUtil::dateTime2AWSMonth(dateTime).toString("yyyyMM"));
    QString zFileNameCCX = AHQC::FileNameUtil::findCCXZFileNameFromPlanFileName(zFileName);
    return zFileNameCCX;
}
QString AHQC::FileNameUtil::AMFUllName2ShortName(const QString &amFullName){
    if(!amFullName.isEmpty()){
        int startIndex = amFileNameReg.indexIn(amFullName);
        int len = amFullName.length() - startIndex;
        QString amFileNameWithoutPath = amFullName.mid(startIndex,len);
        return amFileNameWithoutPath;
    }
    return QString();
}
QString AHQC::FileNameUtil::zFUllName2ShortName(const QString &zFullName){
    if(!zFullName.isEmpty()){
        int startIndex = zFileNameReg.indexIn(zFullName);
        int len = zFullName.length() - startIndex;
        QString zFileNameWithoutPath = zFullName.mid(startIndex,len);
        return zFileNameWithoutPath;
    }
    return QString();
}

QList<QString> AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(const QList<QDateTime> &focursedHours){
    if(focursedHours.length() == 0){
        return QList<QString>();
    }
    QList<QString> amFileNames;
    QDateTime firstHour = focursedHours.at(0);
    QDateTime lastHour = focursedHours.back();
    QDate firstAWSDay = AHQC::TimeUtil::dateTime2AWSDay(firstHour);
    QDate lastAWSDay = AHQC::TimeUtil::dateTime2AWSDay(lastHour);
    QDate tempDate = firstAWSDay;
    QString amFileNameTemplateNeedTime(QString(AHQC::AMFileFullNameTemplate)
                                              .replace("#{isosPath}",AHQC::isosPath)
                                              .replace("#{stationNum}",AHQC::stationNo));
   // QString usingSdf4AMFile = QString(AHQC::TimeUtil::sdf4AMFile).replace("#{stationNum}",AHQC::stationNo);
    QString fileName("beforeGiveValue");
    while(tempDate <= lastAWSDay){
        fileName = QString(amFileNameTemplateNeedTime).replace("#{Date}",tempDate.toString("yyyyMMdd"));
        amFileNames.append(fileName);
        fileName = fileName.toLocal8Bit();
        tempDate = tempDate.addDays(1);
    }
    return amFileNames;

}

QList<QString> AHQC::FileNameUtil::getZFileNamesFormFocusedHours(const QList<QDateTime> &focursedHours){
    if(focursedHours.length() == 0){
        return QList<QString>();
    }
    QList<QString> zFileNames;
    QString fileName("beforeGiveValue");

    QDateTime firstHour = focursedHours.at(0);
    QDateTime lastHour = focursedHours.back();
    QDateTime tempHour(firstHour);
    QDate firstAWSMonth = AHQC::TimeUtil::dateTime2AWSMonth(firstHour);
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
bool AHQC::FileNameUtil::validateZFileExistsByDT(const QDateTime &dateTime){
    QString fileName = AHQC::FileNameUtil::DateTime2ZFileName(dateTime);
    QFile zFile(fileName);
    if(zFile.exists()){
        return true;
    }
    return false;
}
QList<QString> AHQC::FileNameUtil::prepareAMFile4Select(const QDateTime &timepoint){
    QList<QString> amFileNames;
    QDateTime time4V24H = timepoint.addDays(-1);
    QString fileName1 = AHQC::FileNameUtil::Date2AMFileName(AHQC::TimeUtil::dateTime2AWSDay(time4V24H));
    QString fileName2 = AHQC::FileNameUtil::Date2AMFileName(AHQC::TimeUtil::dateTime2AWSDay(timepoint));
    amFileNames.append(fileName1);
    amFileNames.append(fileName2);
    return amFileNames;

}
QList<QString> AHQC::FileNameUtil::prepareAMFile4Select(const TimeRange &timeRange){
    QList<QDateTime> focursedHours = AHQC::TimeUtil::getFocusedHours(timeRange);
    QList<QString> amFileNames = AHQC::FileNameUtil::getAMFileNamesFormFocusedHours(focursedHours);
    if(!focursedHours.isEmpty()){
        QString fileName1 = AHQC::FileNameUtil::Date2AMFileName(
                    AHQC::TimeUtil::dateTime2AWSDay(
                        focursedHours.first().addDays(-1)));;
        amFileNames.append(fileName1);
    }
    return amFileNames;
}
QList<QString> AHQC::FileNameUtil::prepareAMFile4Select(const QList<QDateTime> &timepoints){
    QList<QString> amFileNames;
    for(const QDateTime &timepoint:timepoints){
        QDateTime time4V24H = timepoint.addDays(-1);
        QString fileName1 = AHQC::FileNameUtil::Date2AMFileName(AHQC::TimeUtil::dateTime2AWSDay(time4V24H));
        QString fileName2 = AHQC::FileNameUtil::Date2AMFileName(AHQC::TimeUtil::dateTime2AWSDay(timepoint));
        if(!amFileNames.contains(fileName1)){
            amFileNames.append(fileName1);
        }
        if(!amFileNames.contains(fileName2)){
            amFileNames.append(fileName2);
        }
    }
    return amFileNames;
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
