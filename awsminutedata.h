#ifndef AWSMINUTEDATA_H
#define AWSMINUTEDATA_H
#include <QString>
#include <QDateTime>
#include <QDate>
#include "simpleobject.h"

class AWSMinuteData
{
public:
    AWSMinuteData();
    ~AWSMinuteData();
    AWSMinuteData(QDate &awsDay,QString &line);



    QDate getObserveDay() const;
    void setObserveDay(const QDate &value);

    int getMinute() const;
    void setMinute(int value);

    QString getObserveMonth() const;
    void setObserveMonth(const QString &value);

    QDateTime getObserveTime() const;
    void setObserveTime(const QDateTime &value);

    QDateTime getInsertTime() const;
    void setInsertTime(const QDateTime &value);

    QDateTime getUpdateTime() const;
    void setUpdateTime(const QDateTime &value);

    QList<int> getData() const;
    void setData(const QList<int> &value);

    QString getWeatherphcode() const;
    void setWeatherphcode(const QString &value);

    QString getDataQulity() const;
    void setDataQulity(const QString &value);

    bool isInited() const;
    void setInited(bool value);

private:
    QDate observeDay;
    int  minute;
    QString observeMonth;
    QDateTime observeTime;
    QDateTime  insertTime;
    QDateTime  updateTime;
    QList<int> data;
    QString weatherphcode;
    QString dataQulity;
    bool inited = false;
    static const int validateIndexs[];
    static const int nestenIndex[];

    void initData(QString &line);
    void validateData();
    void nestenData();
};

#endif // AWSMINUTEDATA_H
