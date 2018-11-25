#include "zdata.h"

ZData::ZData():
    observeTime(unInitTime),
    insertTime(unInitTime),
    updateTime(unInitTime),
    data(QMap<QString,QString>())
{}


ZData::ZData(const ZData &other){
    this->observeTime = other.observeTime;
    this->insertTime = other.insertTime;
    this->updateTime = other.updateTime;
    this->data.clear();
    this->data.unite(other.data);
}


ZData ZData::fromZFile(const QString &zFileName){
    ZData zData;
    QFile zFile(zFileName);
    if(zFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream textStream(&zFile);
        QString line("");
        while(!textStream.atEnd()){
            line += textStream.readLine()+" ";
        }
        zData.data = DataFormatUtil::zFileContent2zData(line);
        zData.observeTime = AHQC::FileNameUtil::ZFileName2DateTime(zFileName);
        zData.totalInited = true;
        zFile.close();
    }else{

    }
    return zData;
}

QString ZData::toString(){
    QString temp;
    temp += this->observeTime.toString("yyyyMMddHHmmss ");
    temp += AHQC::PrintUtil::printMap(this->data);
    return temp;
}

bool ZData::isTotalInited() const
{
    return totalInited;
}

QString ZData::value(const QString &key) const{
    if(data.contains(key)){
        return data.value(key);
    }
    return QString();
}


QDateTime ZData::getObserveTime() const
{
    return observeTime;
}
QDateTime ZData::getUpdateTime() const
{
    return updateTime;
}

QDateTime ZData::getInsertTime() const
{
    return insertTime;
}
void ZData::setUpdateTime(const QDateTime &value)
{
    updateTime = value;
}
void ZData::setInsertTime(const QDateTime &value)
{
    insertTime = value;
}
void ZData::setObserveTime(const QDateTime &value)
{
    observeTime = value;
}
