#include "dataformatutil.h"

const QString DataFormatUtil::zIntItem[] =
        {
            "height","PPHeight","awsMode",
            "P","SP","VP3","VP24","MaxP","MaxPT","MinP","MinPT",
            "T","MaxT","MaxTT","MinT","MinTT","VT24","MaxT24","MinT24","TD","RH","MinRH","MinRHT","WP",
            "HRain","HRain3","HRain6","HRain12","HRain24","RainMT","RainM","E",
            "WS2","WS10","MaxWS","MaxWST","WS","ExWS","ExWST","ExWS6","ExWS12",
            "ET","MaxET","MaxETT","MinET","MinETT","MinET12","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320","GT","MaxGT","MaxGTT","MinGT","MinGTT",
            "V1","V10","MinV","MinVT",
            "V","CA","LCA","RCA","CH","CF","EC",
            "SnowD","SnowP","FE1U","FE1D","FE2U","FE2D","TRT","TRD","GA","HA"
        };
const QString DataFormatUtil::zStringItem[] =
        {
            "stationNum","time","latitude","longitude","QCCode","CC","CFC",
            "WD2","WD10","WD","ExWD","MaxWD","ExWD6","ExWD12",
            "HMRain","MW","WW","WT","W1","W2",
            "Q1PP","Q1TH","Q1RE","Q1WI","Q1DT","Q1VV","Q1CW","Q1SP","Q1MR",
            "Q2PP","Q2TH","Q2RE","Q2WI","Q2DT","Q2VV","Q2CW","Q2SP","Q2MR",
            "Q3PP","Q3TH","Q3RE","Q3WI","Q3DT","Q3VV","Q3CW","Q3SP","Q3MR"
        };


const QString DataFormatUtil::zTimeItem[]{"MaxPT","MinPT","MaxTT","MinTT","MinRHT",
        "MaxETT","MinETT","MaxGTT","MinGTT","MinVT","MaxWST","ExWST"};


QMap<QString,int> DataFormatUtil::zFileData2ZIntData(const QMap<QString,QString> &zFileData){
    QMap<QString,int> zIntData;
    QString tempV("/////");
    int temp = 99999;
    bool* ok  = new bool(false);
    if(!zFileData.empty()){        
        for(const QString &s: zIntItem) {
            tempV = zFileData.value(s);
            temp = tempV.toInt(ok,10);
            if(!ok){
                if(tempV.length() !=0 && tempV.at(0) == '/'){
                    temp = tempV.replace("/","9").toInt(ok);
                    if(!ok){
                        temp = 99999;
                    }
                }else if(tempV.length() !=0 && tempV.at(0) == ','){
                    temp = tempV.replace(",","9").toInt(ok);
                    if(!ok){
                        temp = 99999;
                    }
                }else{
                   temp = 99999;
                }
            }
            zIntData.insert(s, temp);
        }
        zIntData.insert("CH",couldHeightFromZFileData(zFileData));
    }
    delete ok;
    return zIntData;
}

QMap<QString,QString> DataFormatUtil::zFileData2ZStringData(const QMap<QString,QString> &zFileData){
    QMap<QString,QString> zStringData ;
    QString missing("/////");
    for(const QString &s: zStringItem) {
        if(zFileData.contains(s)){
            zStringData.insert(s, zFileData.value(s));
        }else{
            zStringData.insert(s, missing);
        }
    }
    return zStringData;
}

void DataFormatUtil::amendZTimeItem(QMap<QString,int> &zIntData) {
    int temp = 999999;
    for(const QString &s:zTimeItem) {
        if(zIntData.contains(s)){
            temp = zIntData.value(s);
            if(temp >= 2400) {
                temp -= 2400;
            }
            zIntData.insert(s, temp);
        }
    }
}

int DataFormatUtil::couldHeightFromZFileData(const QMap<QString,QString> &zFileData) {
    int temp = 999999;
    if(zFileData.contains("CH")){
        return zFileData.value("CH").toInt();
    }
    return temp;
}

QString DataFormatUtil::zIntData2String(int zIntData) {

}

