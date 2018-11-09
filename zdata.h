#ifndef ZDATA_H
#define ZDATA_H

#include <QDateTime>
#include <QMap>
#include "util/dataformatutil.h"
#include <QFile>
#include <QTextStream>
extern QDateTime unInitTime;
class ZDataDAOMysqlImp;
class ZData
{
friend class ZDataDAOMysqlImp;
public:
//    explicit ZData(const QDateTime &observeTime,const QMap<QString,QString> &data);
    bool isTotalInited() const;
    QString value(const QString &key) const;
    static ZData fromZFile(const QString &zFileName);

    QDateTime getObserveTime() const;
    QDateTime getInsertTime() const;
    QDateTime getUpdateTime() const;
    void setObserveTime(const QDateTime &value);
    void setInsertTime(const QDateTime &value);
    void setUpdateTime(const QDateTime &value);

private:
    ZData();
    QDateTime observeTime;
    QDateTime insertTime;
    QDateTime updateTime;
    QMap<QString,QString> data;
//    QMap<QString,QString> stringData;
//    QMap<QString,int> intData;
    bool totalInited = false;
};

#endif // ZDATA_H
