#ifndef AWSMINUTEDATA_H
#define AWSMINUTEDATA_H
#include <QString>
#include <QDateTime>
#include <QDate>
#include <QDebug>
#include "simpleobject.h"
#include "util/simpleutil.h"
#include "globalseeting.h"
class AWSMinuteDAOMySqlImp;

class AWSMinuteData
{
friend class AWSMinuteDAOMySqlImp;

friend QDebug& operator<<(QDebug &debug, const AWSMinuteData &obj);
friend QString operator+(const QString &string,const AWSMinuteData &obj);
friend QString operator+(const AWSMinuteData &obj,const QString &string);
public:
    AWSMinuteData();
    ~AWSMinuteData();
    AWSMinuteData(const QDate &awsDay, const QString &line);
    QString toString();


    QDate getObserveDay() const;
    void setObserveDay(const QDate &value);

    int getMinute() const;
    void setMinute(int value);

    QDateTime getObserveTime() const;
    void setObserveTime(const QDateTime &value);

    QDate getObserveMonth() const;
    void setObserveMonth(const QDate &value);

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
    QDateTime observeTime;
    QDate observeMonth;
    QList<int> data;
    QString weatherphcode;
    QString dataQulity;
    bool inited = false;
    static const int validateIndexs[];
    static const int nestenIndex[];

    void initData(const QString &line);
    void validateData();
    void nestenData();
};
template QString AHQC::PrintUtil::printList<AWSMinuteData>(const  QList<AWSMinuteData>  &list);
#endif // AWSMINUTEDATA_H
