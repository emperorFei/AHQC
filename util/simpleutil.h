#ifndef SIMPLEUTIL_H
#define SIMPLEUTIL_H
#include "QDateTime"
#include "QTime"
#include <QList>
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

    namespace TimeUtil {

        extern QString sdf4SMOLocFile;
        extern QString sdf4AMFile;
        extern QTime dayDemarcationTime;
        extern QTime changeShiftsTime;
        extern int OBInterval;

        QDate translateDateTime2AWSDay(QDateTime dateTime);
        QDate translateDateTime2AWSMonth(QDateTime dateTime);
        TimeRange getFocusedTimeRange(FocusScheme *focusScheme);
        QDateTime getPreviousDayBound(QDateTime gaveTime);
        QList<QDateTime> getFocusedHours(TimeRange focusedTimeRange);
        QDateTime nextHour(QDateTime dateTime);
        QDateTime prevoiusOnHour(QDateTime dateTime);
        TimeRange getTimeRange(const QDateTime &onTime, int hours);
        TimeRange getTimeRange4Sum(const QDateTime &onTime, int hours);
        //QList<QDateTime> getAWSTimepoints(QDateTime );
    }
    namespace FileNameUtil {
        QDate AMFileName2Date(const QString &AMFileName);
        QString Date2AMFileName(const QDate &date);
        QDateTime ZFileName2DT(const QString &ZFileName);
        QString DT2ZFileName(const QDateTime &dateTime);

        QList<QString> getAMFileNamesFormFocusedHours(QList<QDateTime> foucsedHours);
        QList<QString> getZFileNamesFormFocusedHours(QList<QDateTime> foucsedHours);
        QList<QString> getAMFileNamesFormFocusedTimeRange();
        QList<QString> getZFileNamesFormFocusedTimeRange();

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

    }
}
template QString AHQC::PrintUtil::printList<int>(const  QList<int>  &list);
//#include"simpleutil.cpp"
#endif // SIMPLEUTIL_H
