#ifndef AHDATA_H
#define AHDATA_H

#include <QList>
#include <QMap>
#include <QDateTime>
#include "awsminutedata.h"

class DataFormatUtil;
class AZData;
class AHData
{
friend class DataFormatUtil;
friend class AZData;
public:
    AHData();
    AHData(const AWSMinuteData &am, QMap<QString,int> &statisticData);

    int operator< (const AHData &other);
    int operator> (const AHData &other);
    bool operator== (const AHData &other);
    int operator>= (const AHData &other);
    int operator<= (const AHData &other);
    bool operator!= (const AHData &other);

    QDateTime getObserveTime() const;
    int getIntItemValue(const QString &itemName);
    QString getWeatherphcode() const;
    QString getDataQuality() const;



private:
    bool inited = false;
    QDateTime observeTime;
    QMap<QString,int> data;
    static const QString minuteItems[];
    QString weatherphcode = "------------";
    QString mDataQuality = "------------";
};

#endif // AHDATA_H
