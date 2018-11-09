#ifndef ZDATADAOMYSQLIMP_H
#define ZDATADAOMYSQLIMP_H
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "simpleobject.h"
#include "zdata.h"
#include "util/dataformatutil.h"

class ZDataDAOMysqlImp
{
public:
    explicit ZDataDAOMysqlImp(QSqlDatabase *conn);
    int findTempisByObserveTime(const QDateTime &observeTime);
    int getRecordsCount(const TimeRange &tr);
    bool saveZData(const ZData &zData);
    ZData findByOT(const QDateTime &observeTime);
private:
    static QString insertSql;
    static QString findOTDByOTSql;
    static QString getRecordsCountSql;
    static QString findTByObserveTimeSql;

    QSqlDatabase *conn = Q_NULLPTR;
};

#endif // ZDATADAOMYSQLIMP_H
