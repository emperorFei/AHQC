#include "ahdata.h"

QString AHData::minuteItems[] = {"WD2","WS2","WD10","WS10","WD","WS","WS2C","WS10C",
            "MWSC","MRR","HRainR","MRR1","HRainR1","MRW","HRW",
            "T","rsWS","rsT","WetT","HRH","RH","WP","TD","P","GT","ET","GTI","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320",
            "OE","E","V1","V10","CH","CA","LCA","SnowD","FreezingRain","Wireice","Frozensoilddeep","Lightingfreq"};



AHData::AHData(){}
AHData::AHData(const AWSMinuteData &am,QMap<QString,int> &statisticData){
    this->observeTime = am.getObserveTime();

}

QDateTime AHData::getObserveTime() const
{
    return observeTime;
}
