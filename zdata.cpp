#include "zdata.h"

ZData::ZData():
    observeTime(unInitTime),
    observeMonth(unInitTime.date()),
    data(QMap<QString,QString>())
{}




ZData::ZData(const ZData &other){
    this->observeTime = other.observeTime;
    this->observeMonth = other.observeMonth;
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
        zData.observeTime = AHQC::FileNameUtil::ZFileName2DateTime(zFileName);
        zData.observeMonth = AHQC::TimeUtil::dateTime2AWSMonth(zData.observeTime);
        zData.data = DataFormatUtil::zFileContent2zData(line);
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

QDate ZData::getObserveMonth() const
{
    return observeMonth;
}

void ZData::setObserveMonth(const QDate &value)
{
    observeMonth = value;
}
QDateTime ZData::getObserveTime() const
{
    return observeTime;
}
void ZData::setObserveTime(const QDateTime &value)
{
    observeTime = value;
}

