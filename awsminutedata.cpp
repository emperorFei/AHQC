#include "awsminutedata.h"
const int AWSMinuteData::validateIndexs[] = {15,17,18,22,24,25,26,27,28,29,30,31,32,33,34,};
const int AWSMinuteData::nestenIndex[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,19,20,21,40,41,42,43,44,45,46};

AWSMinuteData::AWSMinuteData(){}
AWSMinuteData::~AWSMinuteData(){}
AWSMinuteData::AWSMinuteData(QDate &awsDay,QString &line):
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

void AWSMinuteData::initData(QString &line){
    int temp = 0;
//    QString tempString("");
//    QList<ColInfo> cInfos = GlobalSetting.getcInfos();
//    //PrintUtil.printList(cInfos);
//    int index = 0;
//    ColInfo cInfo = null;
//    for(;index < cInfos.size()-2;index++) {
//        cInfo = cInfos.get(index);
//        tempString = line.substring(cInfo.getBeginIndex(), cInfo.getEndIndex());
//        if(tempString.charAt(0) == '/') {
//            tempString = tempString.replace('/', '9');
//        }else if(tempString.charAt(0) == '-' ) {
//            if(tempString.charAt(1) != '-') {}else {
//                tempString = tempString.replace('-', '6');
//            }
//        }else if(tempString.charAt(0) == ',') {
//            tempString = tempString.replace(',', '7');
//        }
//        /*System.out.print(cInfo);
//        System.out.print(tempString+ "★");*/
//        temp = Integer.parseInt(tempString.trim());
//        data.add(temp);
//    }
//    cInfo = cInfos.get(index++);
//    weatherphcode = line.substring(cInfo.getBeginIndex(), cInfo.getEndIndex());
//    cInfo = cInfos.get(index++);
//    dataQulity = line.substring(cInfo.getBeginIndex(), cInfo.getEndIndex());
}
void AWSMinuteData::validateData(){

}
void AWSMinuteData::nestenData(){

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

