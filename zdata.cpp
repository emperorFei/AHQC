#include "zdata.h"

ZData ZData::fromZFile(const QString &zFileName){
    QFile zFile(zFileName);
    if(zFile.open(QIODevice::ReadOnly|QIODevice::Text)){

    }
}

ZData::ZData(const QDateTime &observeTime,const QMap<QString,QString> &zFileData):observeTime(observeTime)
{
    this->observeTime = observeTime;
    intData = DataFormatUtil::zFileData2ZIntData(zFileData);
    stringData = DataFormatUtil::zFileData2ZStringData(zFileData);
    DataFormatUtil::amendZTimeItem(intData);
    if(observeTime != QDateTime() && !intData.empty() && !stringData.empty()){
        totalInited = true;
    }
}

bool ZData::isTotalInited() const
{
    return totalInited;
}

QString ZData::value(const QString &key){
    if(key == "observeTime"){
        return observeTime.toString("yyyy年MM月mm日 HH:mm:dd");
    }else if(stringData.contains(key)){
        return stringData.value(key);
    }
    return QString();
}
