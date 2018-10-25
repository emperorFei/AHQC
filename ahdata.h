#ifndef AHDATA_H
#define AHDATA_H

#include <QList>
#include <QMap>
#include <QDateTime>
#include "awsminutedata.h"


class AHData
{
public:
    AHData();
    AHData(const AWSMinuteData &am, QMap<QString,int> &statisticData);

    QDateTime getObserveTime() const;

private:
    bool inited = false;
    QDateTime observeTime;
    static const QString minuteItems[];
};

#endif // AHDATA_H
