#include "awsminutedata.h"
const int AWSMinuteData::validateIndexs[] = {15,17,18,22,24,25,26,27,28,29,30,31,32,33,34,};
const int AWSMinuteData::nestenIndex[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,19,20,21,40,41,42,43,44,45,46};

AWSMinuteData::AWSMinuteData(){}
AWSMinuteData::~AWSMinuteData(){}
AWSMinuteData::AWSMinuteData(const QDate &awsDay,const QString &line):
    observeDay(awsDay),
    observeMonth(awsDay.toString("yyyyMM")),
    observeTime(QDateTime(awsDay)),
    insertTime(observeTime),
    updateTime(observeTime){
    if(line != Q_NULLPTR && line != QString("") && line.at(0) != '-' ) {

        minute = line.mid(0,4).toInt();

        if( minute > 2000) {
            observeTime = observeTime.addDays(-1);
        }
        observeTime = observeTime.addSecs((minute/100)*60*60+ (minute%100)*60);
        updateTime = insertTime = observeTime;

        initData(line);
        validateData();
        nestenData();
        inited = true;
    }
}

void AWSMinuteData::initData(const QString &line){
    int temp = 999999;
    GlobalSetting * globalSetting = GlobalSetting::getInstance();
    QList<ColInfo> *cInfos = globalSetting->getColInfos();
    QList<ColInfo>::iterator it = cInfos->begin();
    QList<ColInfo>::iterator cendIt= cInfos->end()-2;
    QString tempString("beforeInit");


    for(;it != cendIt;it++){
        tempString = line.mid(it->getBeginIndex(),it->getLength());
        if(tempString.at(0) == "/"){
            tempString = tempString.replace('/',9);
        }else if(tempString.at(0) == '-' ) {
            if(tempString.at(1) == '-'){
                tempString = tempString.replace('-', '6');
            }
        }else if(tempString.at(0) == ',') {
            tempString = tempString.replace(',', '7');
        }
        temp = atoi(tempString.toStdString().c_str());
        data.append(temp);
    }

    weatherphcode = line.mid(it->getBeginIndex(), it->getLength());
    it++;
    dataQulity = line.mid(it->getBeginIndex(), it->getLength());
    it++;
}
void AWSMinuteData::validateData(){
    int temp = 0;
    for(int i:validateIndexs) {
        temp = data[i];
        if(temp != 6666 && temp != 9999 && temp != 7777) {
            temp += 1000;
            data[i] = temp;
            //data.set(i, temp > 800 ? 2000-temp : temp+1000);
        }
    }
}
void AWSMinuteData::nestenData(){
    int temp = 0;
    for(int i:nestenIndex) {
        temp = data[i];
        if(temp != 6666 && temp != 9999 && temp != 7777) {
            temp += 1000;
            data[i] = temp;
            //data.set(i, temp > 800 ? 2000-temp : temp+1000);
        }
    }
}

QDebug& operator<<(QDebug &debug, const AWSMinuteData &obj){
    debug << obj.getObserveTime()
          <<" IntData: "+ AHQC::PrintUtil::printList(obj.getData())
          << " Weatherphcod: "+obj.getWeatherphcode()
          << " DataQulity: "+obj.getDataQulity();
}

QString operator+(const QString &string,const AWSMinuteData &obj){
    return string + obj.getObserveTime().toString(QString::fromLocal8Bit("yyyy年MM月dd日HH时mm分"))
            + " IntData: "+ AHQC::PrintUtil::printList(obj.getData())
            + " Weatherphcod: "+obj.getWeatherphcode()
            + " DataQulity: "+obj.getDataQulity();
}
QString operator+(const AWSMinuteData &obj,const QString &string){
    return string + obj;
}

QString AWSMinuteData::toString(){
    return  this->getObserveTime().toString("yyyy年MM月dd日HH时mm分")
            + " IntData: "+  AHQC::PrintUtil::printList(this->getData())
            + " Weatherphcod: "+ this->getWeatherphcode()
            + " DataQulity: "+ this->getDataQulity();
}


QDate AWSMinuteData::getObserveDay() const
{
    return observeDay;
}

void AWSMinuteData::setObserveDay(const QDate &value)
{
    observeDay = value;
}



int AWSMinuteData::getMinute() const
{
    return minute;
}

void AWSMinuteData::setMinute(int value)
{
    minute = value;
}


QString AWSMinuteData::getObserveMonth() const
{
    return observeMonth;
}

void AWSMinuteData::setObserveMonth(const QString &value)
{
    observeMonth = value;
}



QDateTime AWSMinuteData::getObserveTime() const
{
    return observeTime;
}

void AWSMinuteData::setObserveTime(const QDateTime &value)
{
    observeTime = value;
}


QDateTime AWSMinuteData::getInsertTime() const
{
    return insertTime;
}

void AWSMinuteData::setInsertTime(const QDateTime &value)
{
    insertTime = value;
}


QDateTime AWSMinuteData::getUpdateTime() const
{
    return updateTime;
}

void AWSMinuteData::setUpdateTime(const QDateTime &value)
{
    updateTime = value;
}

QList<int> AWSMinuteData::getData() const
{
    return data;
}

void AWSMinuteData::setData(const QList<int> &value)
{
    data = value;
}

QString AWSMinuteData::getWeatherphcode() const
{
    return weatherphcode;
}

void AWSMinuteData::setWeatherphcode(const QString &value)
{
    weatherphcode = value;
}

QString AWSMinuteData::getDataQulity() const
{
    return dataQulity;
}

void AWSMinuteData::setDataQulity(const QString &value)
{
    dataQulity = value;
}

bool AWSMinuteData::isInited() const
{
    return inited;
}

void AWSMinuteData::setInited(bool value)
{
    inited = value;
}


