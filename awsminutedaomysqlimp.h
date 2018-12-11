#ifndef AWSMINUTEDAOMYSQLIMP_H
#define AWSMINUTEDAOMYSQLIMP_H

#include <QObject>
#include <QDateTime>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <globalseeting.h>
#include <QtMath>
#include <QMap>
#include "util/simpleutil.h"
#include "awsminutedata.h"

class AWSMinuteDAOMySqlImp : public QObject
{
    Q_OBJECT
public:
    explicit AWSMinuteDAOMySqlImp(QSqlDatabase *conn,QObject *parent = nullptr);
    enum AWSItemType{T,GT,ET,P,Rh,V,WS,exWS,WSD,exWSD,VP3,VP24,VT24,ExWS6,ExWD6,ExWS12,ExWD12,MinT24,MaxT24,MinET12,HRain,HRain3,HRain6,HRain12,HRain24};

    int findTempisByObserveTime(const QDateTime &observeTime);
    int getRecordsCount(const TimeRange &tr);
    bool saveAWSMinuteData(const AWSMinuteData &amData);
    bool saveAMFile(const QString &amFileName);

    //获取变化值，雨量，海平面气压
    QMap<QString,int> getVAndRain(const QDateTime &observeTime);
    //获得所有极值
    QMap<QString,int> getExtremums(const QDateTime &observeTime);
    //获得所有正点数据
    AWSMinuteData findByOT(const QDateTime &observeTime);

    bool exists(const QDateTime &observeTime);
    int getMaxByOnTime(QDateTime onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getMinByOnTime(const QDateTime &onTimeDate, AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getMaxTimeByOnTime(const QDateTime &onTimeDate, AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getMinTimeByOnTime(const QDateTime &onTimeDate, AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getWDByOnTime(const QDateTime &onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);


    int getNVWD(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getNVExtremum(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getVariatedValue(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getRain(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    int getSP(const QDateTime &onTimeDate);

    //T
    int getMaxTByOT(QDateTime onTime);
    int getMaxTTByOT(QDateTime onTime);
    int getMinTByOT(QDateTime onTime);
    int getMinTTByOT(QDateTime onTime);
    int getMinT24ByOT(QDateTime onTime);
    int getMaxT24ByOT(QDateTime onTime);
    int getVT24ByOT(QDateTime onTime);
    //getGT

    int getMaxGTByOT(QDateTime onTime);
    int getMaxGTTByOT(QDateTime onTime);
    int getMinGTByOT(QDateTime onTime);
    int getMinGTTByOT(QDateTime onTime);
    //getET

    int getMaxETByOT(QDateTime onTime);
    int getMaxETTByOT(QDateTime onTime);
    int getMinETByOT(QDateTime onTime);
    int getMinETTByOT(QDateTime onTime);
    int getMinET12ByOT(QDateTime onTime);
    //getP;

    //P
    int getMaxPByOT(QDateTime onTime);
    int getMaxPTByOT(QDateTime onTime);
    int getMinPByOT(QDateTime onTime);
    int getMinPTByOT(QDateTime onTime);
    int getVP3ByOT(QDateTime onTime);
    int getVP24ByOT(QDateTime onTime);
    int getSPByOT(QDateTime onTime);
    //getRh

    //RH
    int getMinRHByOT(QDateTime onTime);
    int getMinRHTByOT(QDateTime onTime);
    //getWind

    //wind
    int getMaxWSByOT(QDateTime onTime);
    int getMaxWSTByOT(QDateTime onTime);
    int getMaxWSDByOT(QDateTime onTime);
    int getExWSByOT(QDateTime onTime);
    int getExWSTByOT(QDateTime onTime);
    int getExWSDByOT(QDateTime onTime);
    int getExWS6ByOT(QDateTime onTime);
    int getExWS12ByOT(QDateTime onTime);
    int getExWD6ByOT(QDateTime onTime);
    int getExWD12ByOT(QDateTime onTime);
    //getRain

    //Rain
    int getHRainByOT(QDateTime onTime);
    int getHRain3ByOT(QDateTime onTime);
    int getHRain6ByOT(QDateTime onTime);
    int getHRain12ByOT(QDateTime onTime);
    int getHRain24ByOT(QDateTime onTime);

    //Visibility
    int getMinVByOT(QDateTime onTime);
    int getMinVTByOT(QDateTime onTime);

private:



    //functions for get sql Strings
    QString getMinSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) ;
    QString getMinTimeSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    QString getMaxSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    QString getMaxTimeSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) ;
    QString getNVSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType);
    QString getRainSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType);

    QSqlDatabase *conn = Q_NULLPTR;

    static QString findTByObserveTimeSql;
    static QString findOTDByOTSql;
    static QString getRecordsCountSql;
    static QString checkExistsSql;
    //max
    static QString getMaxTByOnTimeSql;
    static QString getMaxETByOnTimeSql;
    static QString getMaxGTByOnTimeSql;
    static QString getMaxPByOnTimeSql;
    static QString getMaxWSByOnTimeSql;
    static QString getExWSByOnTimeSql;
    //min
    static QString getMinTByOnTimeSql;
    static QString getMinETByOnTimeSql;
    static QString getMinGTByOnTimeSql;
    static QString getMinRHByOnTimeSql;
    static QString getMinPByOnTimeSql;
    static QString getMinVByOnTimeSql;
    //rain
    static QString getRainSql;
    //sp
    static QString getValue4SPSql;
    //extremum that not visible
    static QString getVPSql;
    static QString getVTSql;
    static QString getMinTSql;
    static QString getMaxTSql;
    static QString getExWSSql;
    static QString getExWDSql;
    static QString getMinETSql;
    //maxT
    static QString getMaxTTByOnTimeSql;
    static QString getMaxETTByOnTimeSql;
    static QString getMaxGTTByOnTimeSql;
    static QString getMaxPTByOnTimeSql;
    static QString getMaxWSTByOnTimeSql;
    static QString getExWSTByOnTimeSql;
    //minT
    static QString getMinTTByOnTimeSql;
    static QString getMinETTByOnTimeSql;
    static QString getMinGTTByOnTimeSql;
    static QString getMinPTByOnTimeSql;
    static QString getMinRHTByOnTimeSql;
    static QString getMinVTByOnTimeSql;

    //WindDir
    static QString getMaxWSDByOnTimeSql;
    static QString getExWSDByOnTimeSql;

    QString insertSql = "";
signals:

public slots:
};

#endif // AWSMINUTEDAOMYSQLIMP_H
