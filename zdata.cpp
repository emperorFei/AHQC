#include "zdata.h"
ZData::ZData(){}


ZData ZData::fromZFile(const QString &zFileName){
    ZData zData;
    QFile zFile(zFileName);
    if(zFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream textStream(&zFile);
        QString line("");
        while(!textStream.atEnd()){
            line += textStream.readLine();
        }
        zData.data = DataFormatUtil::zFileContent2zData(line);
        zFile.close();
    }
    return zData;
}

//ZData::ZData(const QDateTime &observeTime,const QMap<QString,QString> &zFileData):observeTime(observeTime)
//{
//    this->observeTime = observeTime;
//    intData = DataFormatUtil::zFileData2ZIntData(zFileData);
//    stringData = DataFormatUtil::zFileData2ZStringData(zFileData);
//    DataFormatUtil::amendZTimeItem(intData);
//    if(observeTime != QDateTime() && !intData.empty() && !stringData.empty()){
//        totalInited = true;
//    }
//}

bool ZData::isTotalInited() const
{
    return totalInited;
}

QString ZData::value(const QString &key){
    if(key == "observeTime"){
        return observeTime.toString("yyyy年MM月mm日 HH:mm:dd");
    }else if(data.contains(key)){
        return data.value(key);
    }
    return QString();
}
