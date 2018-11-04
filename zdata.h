#ifndef ZDATA_H
#define ZDATA_H

#include <QDateTime>
#include <QMap>
#include "util/dataformatutil.h"
#include <QFile>
#include <QTextStream>
class ZData
{
public:
//    explicit ZData(const QDateTime &observeTime,const QMap<QString,QString> &data);
    bool isTotalInited() const;
    QString value(const QString &key);
    static ZData fromZFile(const QString &zFileName);
private:
    ZData();
    QDateTime observeTime;
    QMap<QString,QString> data;
//    QMap<QString,QString> stringData;
//    QMap<QString,int> intData;
    bool totalInited = false;
};

#endif // ZDATA_H
