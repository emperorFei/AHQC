#ifndef ZDATA_H
#define ZDATA_H

#include <QDateTime>
#include <QMap>
#include "util/dataformatutil.h"
#include "util/simpleutil.h"
#include <QFile>
#include <QTextStream>

extern QDateTime unInitTime;
class ZDataDAOMysqlImp;
class AZData;
class DataFormatUtil;
class ZData
{
friend class ZDataDAOMysqlImp;
friend class DataFormatUtil;
friend class AZData;
public:
//    explicit ZData(const QDateTime &observeTime,const QMap<QString,QString> &data);
    bool isTotalInited() const;
    QString value(const QString &key) const;
    static ZData fromZFile(const QString &zFileName);
    QString toString();

    ZData(const ZData &other);
    QDateTime getObserveTime() const;
    QDate getObserveMonth() const;
    void setObserveTime(const QDateTime &value);
    void setObserveMonth(const QDate &value);

private:
    ZData();
    QDateTime observeTime;
    QDate observeMonth;
    QMap<QString,QString> data;
//    QMap<QString,QString> stringData;
//    QMap<QString,int> intData;
    bool totalInited = false;
};

#endif // ZDATA_H
