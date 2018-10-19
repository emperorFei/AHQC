#ifndef SIMPLEUTIL_H
#define SIMPLEUTIL_H
#include "QDateTime"
#include "QTime"
#include <QList>
#include "simpleobject.h"
#include "focusScheme/focusscheme.h"
namespace AHQC {
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

        QList<QString> getAMFileNamesFormFocusedHours();
        QList<QString> getAMFileNamesFormFocusedTimeRange();
    }
}
#endif // SIMPLEUTIL_H
