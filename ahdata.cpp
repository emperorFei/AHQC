#include "ahdata.h"

const QString AHData::minuteItems[] = {"WD2","WS2","WD10","WS10","WD","WS","WS2C","WS10C",
            "MWSC","MRR","HRainR","MRR1","HRainR1","MRW","HRW",
            "T","rsWS","rsT","WetT","HRH","RH","WP","TD","P","GT","ET","GTI","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320",
            "OE","E","V1","V10","CH","CA","LCA","SnowD","FreezingRain","Wireice","Frozensoilddeep","Lightingfreq"};

AHData::AHData(){}
AHData::AHData(const AWSMinuteData &am,QMap<QString,int> &statisticData){
    this->observeTime = am.getObserveTime();
    this->observeTime = am.getObserveTime();
    const QList<int> &onTimeIntData = am.getData();
    int index = 0;
    for(;index < 47;index++) {
        this->data.insert(minuteItems[index],onTimeIntData.at(index));
    }
    this->data.unite(statisticData);
    this->weatherphcode= am.getWeatherphcode();
    this->mDataQuality = am.getDataQulity();
    inited = true;
}

QDateTime AHData::getObserveTime() const
{
    return observeTime;
}

QString AHData::getDataQuality() const
{
    return mDataQuality;
}

QString AHData::getWeatherphcode() const
{
    return weatherphcode;
}

int AHData::getIntItemValue(const QString &itemName) {
    return this->data.value(itemName);
}

int AHData::operator< (const AHData &other){
    return this->observeTime < other.observeTime;
}
int AHData::operator> (const AHData &other){
    return this->observeTime > other.observeTime;
}
bool AHData::operator== (const AHData &other){
    return this->observeTime == other.observeTime;
}
int AHData::operator>= (const AHData &other){
    return this->observeTime >= other.observeTime;
}
int AHData::operator<= (const AHData &other){
    return this->observeTime <= other.observeTime;
}
bool AHData::operator!= (const AHData &other){
    return this->observeTime != other.observeTime;
}

