#ifndef SIMPLEUTIL_H
#define SIMPLEUTIL_H
#include "QDateTime"
#include "QTime"
#include <QList>
#include <QMap>
#include "simpleobject.h"
#include "focusScheme/focusscheme.h"
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include "globalseeting.h"
namespace AHQC {
    extern QString stationNo;
    extern QString isosPath;
    extern QString minuteDataPathTemplate;
    extern QString zFilePathTemplate;
    extern QString AMFileNameTemplate;
    extern QString ZFileNameTemplate;
    extern QString AMFileFullNameTemplate;
    extern QString ZFileFullNameTemplate;
    extern QRegExp amFileNameReg;
    extern QRegExp zFileNameReg;
    extern QList<QString> QCItemNames;
    extern QList<QString> defaultQCItemNames;
    extern QList<QString> hideWidget;


    enum DataLevel{INFO,SUSPECTED,CLASH,MISSING,MISSINGZDATA,MISSINGAMDATA,ERROR};
    int connectToShareDfolder();
    namespace TimeUtil {

        extern QString sdf4SMOLocFile;
        extern QString sdf4AMFile;
        extern QTime dayDemarcationTime;
        extern QTime changeShiftsTime;
        extern int OBInterval;

        QDate dateTime2AWSDay(const QDateTime &dateTime);
        QDate dateTime2AWSMonth(const QDateTime &dateTime);
        TimeRange getFocusedTimeRange(FocusScheme *focusScheme);
        QDateTime getPreviousDayBound(const QDateTime &gaveTime);
        QList<QDateTime> getFocusedHours(const TimeRange &focusedTimeRange);
        QDateTime nextHour(const QDateTime &dateTime);
        inline QDateTime prevoiusOnHour(const QDateTime &dateTime);
        TimeRange getTimeRange(const QDateTime &onTime, int hours);
        TimeRange getTimeRange4Sum(const QDateTime &onTime, int hours);
        QDateTime previousOnTimeZSendTime();

        //QList<QDateTime> getAWSTimepoints(QDateTime );
    }
    namespace FileNameUtil {
        QDate AMFileName2Date(const QString &AMFileName);
        QString Date2AMFileName(const QDate &date);
        QDateTime ZFileName2DateTime(const QString &ZFileName);
        QString DateTime2ZFileName(const QDateTime &dateTime);
        QString AMFUllName2ShortName(const QString &amFullName);
        QString zFUllName2ShortName(const QString &zFullName);
        QList<QString> getAMFileNamesFormFocusedHours(const QList<QDateTime> &foucsedHours);
        QList<QString> getZFileNamesFormFocusedHours(const QList<QDateTime> &foucsedHours);
        QList<QString> getAMFileNamesFormFocusedTimeRange();
        QList<QString> getZFileNamesFormFocusedTimeRange();
        bool validateZFileExistsByDT(const QDateTime&);
        QList<QString> prepareAMFile4Select(const QDateTime &timepoint);
        QList<QString> prepareAMFile4Select(const TimeRange &timeRange);
        QList<QString> prepareAMFile4Select(const QList<QDateTime> &timepoints);
        inline QString findCCXZFileNameFromPlanFileName(const QString &planZFileName);

    }
    namespace PrintUtil {

        template<class T,int N>
        QString printEmbeddedArray(const T (&list)[N]){
            int i = 0;
            QString temp("");
            for(T t:list){
                temp += QString::number(i)+": "+list[i];
                i++;
            }
            return temp;
        }

        template<class T>
        QString printList(QList<T> const  &list){
            QString temp("");
            for(T t:list){
                temp = temp + t;
                temp = temp+" ";
            }
            return temp;
        }
        // argument types can differ but must be compatible
        template <typename A, typename B>
        int flexibleCompare(const A& v1, const B& v2)
        {
            if (v1 < v2) return -1;
            if (v2 < v1) return 1;
            return 0;
        }

//        template <typename K, typename V> QMap<K,V>::const_iterator;
        template <typename K, typename V>
        QString printMap(QMap<K,V> const &map){
          QString temp("QMap");
////            auto key = map.keyBegin();
////            temp += map.value(*key);
           return temp;
        }

    }
}
template QString AHQC::PrintUtil::printMap<QString,QString>(const  QMap<QString,QString>  &map);
template QString AHQC::PrintUtil::printList<int>(const  QList<int>  &list);
//#include"simpleutil.cpp"
#endif // SIMPLEUTIL_H
