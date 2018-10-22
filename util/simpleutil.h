#ifndef SIMPLEUTIL_H
#define SIMPLEUTIL_H
#include "QDateTime"
#include "QTime"
#include <QList>
#include "simpleobject.h"
#include "focusScheme/focusscheme.h"
#include <QDebug>
namespace AHQC {
    extern QString stationNo;
    namespace TimeUtil {
//        class ShiftsScheme;
//        class dayBoundScheme;
//        class OBScheme;
//        class AppointedRangeScheme;

        extern QString sdf4SMOLocFile;
        extern QString sdf4SMOFile;
        extern QString sdf4YMD;
        extern QTime dayDemarcationTime;
        extern QTime changeShiftsTime;
        extern int OBInterval;

        QDateTime SMOFileName2DT(QString smoFileName);
        QString DT2SMOFileName(QDateTime dateTime);
        QDate translateDateTime2AWSDay(QDateTime dateTime);
        TimeRange getFocusedTimeRange(FocusScheme *focusScheme);
        QDateTime getPreviousDayBound(QDateTime gaveTime);
        QList<QDateTime> getFocusedHours(TimeRange focusedTimeRange);
        QDateTime nextHour(QDateTime dateTime);
        QDateTime prevoiusOnHour(QDateTime dateTime);
        //QList<QDateTime> getAWSTimepoints(QDateTime );
    }
    namespace FileNameUtil {
        extern QString ISOSPath;
        extern QString subPathBeforeStationNo;
        extern QString subPathAfterStationNo;
        extern QString amFileFolderPath;


        QList<QString> getAMFileNamesFormFocusedHours(QList<QDateTime> foucsedHours);
        QList<QString> getAMFileNamesFormFocusedTimeRange();
        QDate getDayFormAMFileFullName(const QString &AMFileFullName);

    }
    namespace PrintUtil {

        export template<class T,int N>
        QString printEmbeddedArray(const T (&list)[N]){
            int i = 0;
            QString temp("");
            for(T t:list){
                temp += i+": "+list[i];
                i++;
            }
            return temp;
        }

       export template<class T>
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
