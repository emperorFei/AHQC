#include "awsminutedbserver.h"

AWSMinuteDBServer::AWSMinuteDBServer(QObject *parent) : QObject(parent)
{
    this -> conn = DBCenter::getDBByAccountType(DBCenter::AccountType::QIU);
    this -> dao = new AWSMinuteDAOMySqlImp(conn);
}
bool AWSMinuteDBServer::saveAWSMinuteData(const AWSMinuteData &amData) {
    bool flag = false;
    if(amData.isInited()) {
        if(this->dao ->findTempisByObserveTime(amData.getObserveTime())== 0) {
            this -> dao->saveAWSMinuteData(amData);
            flag = true;
        }
    }
    return flag;
}

bool AWSMinuteDBServer::saveAWSMinuteData(const QDate &AWS_date,const QString &AM_Line) {
    return saveAWSMinuteData(AWSMinuteData(AWS_date,AM_Line));
}

AHData AWSMinuteDBServer::getAHData(const QDateTime &timepoint){
    AHData uninitedAHData;
    if((timepoint.time().second()%60) != 0) {
        return uninitedAHData;
    }
    AWSMinuteData am = this->dao->findByOT(timepoint);
    QMap<QString,int> extremums = this->dao->getExtremums(timepoint);
    QMap<QString,int> vAndRain = this->dao->getVAndRain(timepoint);
    if(extremums.size() == 0 || vAndRain.size() == 0 || !am.isInited()) {
      return uninitedAHData;
    }

    extremums.unite(vAndRain);
    return AHData(am,extremums);
}
