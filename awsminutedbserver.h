#ifndef AWSMINUTEDBSERVER_H
#define AWSMINUTEDBSERVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QMap>
#include "awsminutedaomysqlimp.h"
#include "awsminutedata.h"
#include "ahdata.h"
#include "util/simpleutil.h"
#include "dbcenter.h"

class AWSMinuteDBServer : public QObject
{
    Q_OBJECT
public:
    explicit AWSMinuteDBServer(QObject *parent = nullptr);
    bool saveAWSMinData(const AWSMinuteData &amData);
    AHData getAHData(const QDateTime &timepoint);

    bool savaFileByName(const QString &fileName);
    bool savaFileByTimePoint(const QDateTime &timepoint);
    bool saveAWSMinuteData(const AWSMinuteData &amData);
    bool saveAWSMinuteData(const QDate &AWS_date,const QString &AM_Line);

private:

    QList<QString> DIC2FlieList(TimeRange tr);
    QSqlDatabase *conn;
    AWSMinuteDAOMySqlImp *dao;
signals:

public slots:
};

#endif // AWSMINUTEDBSERVER_H
