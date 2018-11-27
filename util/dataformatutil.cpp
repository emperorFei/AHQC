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
            "stationNum","time","latitude","longitude","QCCode","CFC",
            "WD2","WD10","WD","ExWD","MaxWD","ExWD6","ExWD12",
            "HMRain","MWW","WW","WT","W1","W2",
            "Q1PP","Q1TH","Q1RE","Q1WI","Q1DT","Q1VV","Q1CW","Q1SP","Q1MR",
            "Q2PP","Q2TH","Q2RE","Q2WI","Q2DT","Q2VV","Q2CW","Q2SP","Q2MR",
            "Q3PP","Q3TH","Q3RE","Q3WI","Q3DT","Q3VV","Q3CW","Q3SP","Q3MR"
        };
const QString DataFormatUtil::zDBItem[] =
        {
            "stationNum","time","latitude","longitude","height","PPHeight","awsMode","QCCode","CCX",
            "P","SP","VP3","VP24","MaxP","MaxPT","MinP","MinPT",
            "T","MaxT","MaxTT","MinT","MinTT","VT24","MaxT24","MinT24","TD","RH","MinRH","MinRHT","WP",
            "HRain","HRain3","HRain6","HRain12","HRain24","RainMT","RainM","E",
            "WD2","WS2","WD10","WS10","MaxWD","MaxWS","MaxWST","WD","WS","ExWD","ExWS","ExWST","ExWS6","ExWD6","ExWS12","ExWD12",
            "ET","MaxET","MaxETT","MinET","MinETT","MinET12","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320","GT","MaxGT","MaxGTT","MinGT","MinGTT",
            "V1","V10","MinV","MinVT",
            "V","CA","LCA","RCA","CH","CF","CFC","WW","WT","W1","W2","EC"
            "SnowD","SnowP","FE1U","FE1D","FE2U","FE2D","TRT","TRD","GA","HA",
            "HMRain",
            "MWW",
            "Q1PP","Q1TH","Q1RE","Q1WI","Q1DT","Q1VV","Q1CW","Q1SP","Q1MR",
            "Q2PP","Q2TH","Q2RE","Q2WI","Q2DT","Q2VV","Q2CW","Q2SP","Q2MR",
            "Q3PP","Q3TH","Q3RE","Q3WI","Q3DT","Q3VV","Q3CW","Q3SP","Q3MR"
        };
const QString DataFormatUtil::zFileItem[] =
        {
            "stationNum","time","latitude","longitude","height","PPHeight","awsMode","QCCode","CCX",
            "P","SP","VP3","VP24","MaxP","MaxPT","MinP","MinPT",
            "T","MaxT","MaxTT","MinT","MinTT","VT24","MaxT24","MinT24","TD","RH","MinRH","MinRHT","WP",
            "HRain","HRain3","HRain6","HRain12","HRain24","RainMT","RainM","E",
            "WD2","WS2","WD10","WS10","MaxWD","MaxWS","MaxWST","WD","WS","ExWD","ExWS","ExWST","ExWS6","ExWD6","ExWS12","ExWD12",
            "ET","MaxET","MaxETT","MinET","MinETT","MinET12","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320","GT","MaxGT","MaxGTT","MinGT","MinGTT",
            "V1","V10","MinV","MinVT",
            "V","CA","LCA","RCA","CH","CF","CFC","WW","WT","W1","W2","EC",
            "SnowD","SnowP","FE1U","FE1D","FE2U","FE2D","TRT","TRD","GA","HA",
            "HMRain",
            "MWW",
            "Q1PP","Q1TH","Q1RE","Q1WI","Q1DT","Q1VV","Q1CW","Q1SP","Q1MR",
            "Q2PP","Q2TH","Q2RE","Q2WI","Q2DT","Q2VV","Q2CW","Q2SP","Q2MR",
            "Q3PP","Q3TH","Q3RE","Q3WI","Q3DT","Q3VV","Q3CW","Q3SP","Q3MR"
        };
const QString DataFormatUtil::zFileSectionID[] =
        {"PP","TH","RH","RE","WI","DT","VV","CW","SP","MR","MW","QC","Q1","Q2","Q3"};
const QString DataFormatUtil::zTimeItem[] = {"MaxPT","MinPT","MaxTT","MinTT","MinRHT",
        "MaxETT","MinETT","MaxGTT","MinGTT","MinVT","MaxWST","ExWST"};
const QRegExp DataFormatUtil::mwReg = QRegExp("MW.*\\.");


QMap<QString,QString> DataFormatUtil::zFileContent2zData(const QString &zFileContent){
    QMap<QString,QString> zData;
    if(!zFileContent.isEmpty()){
        QString zFileDataString = removeZFileSectionID(zFileContent);
        zData = zFileDataString2zFileData(zFileDataString);
    }
    return zData;
}

QString DataFormatUtil::removeZFileSectionID(const QString &zFileContent){
    QString zFileDataString(zFileContent);
    if(zFileContent.isEmpty()){
        return zFileContent;
    }

    int startIndex = mwReg.indexIn(zFileDataString);
    int len = mwReg.matchedLength();
    QString MW(zFileDataString.mid(startIndex,len));
    QString forMatedMW(MW);
    forMatedMW.replace(QRegExp("[\\s]+"),"@");
    zFileDataString.replace(MW,forMatedMW);
    zFileDataString.remove(QRegExp("\\s*=\\s*NNNN\\s*"));
    for(const QString &sectionID : zFileSectionID){
       zFileDataString = zFileDataString.replace(sectionID,"");
    }
    return zFileDataString;
}
QMap<QString,QString> DataFormatUtil::zFileDataString2zFileData(const QString &zFileDataString){
    QMap<QString,QString> zFileData;
    if(zFileDataString.isEmpty()){
        return zFileData;
    }
    QString zDataString(zFileDataString);

    QStringList zDataList = zDataString.split(QRegExp("[\\s]+"));
    QString temp("");
    for(const QString &item : zFileItem){
        temp += item +" ";
    }
    int size = zFileItem->size();
    if(128 != zDataList.length()){
        return zFileData;
    }
    QStringList::const_iterator constIt = zDataList.cbegin();
    for(const QString &item : zFileItem){
        zFileData.insert(item,*constIt);
        constIt++;
    }
    QString MWW = zFileData.value("MWW");
    if(!MWW.isEmpty()){
        MWW.replace("@"," ");
        zFileData.remove("MWW");
        zFileData.insert("MWW",MWW);
    }
    return zFileData;
}



//QMap<QString,int> DataFormatUtil::zFileData2ZIntData(const QMap<QString,QString> &zFileData){
//    QMap<QString,int> zIntData;
//    QString tempV("/////");
//    int temp = 99999;
//    bool* ok  = new bool(false);
//    if(!zFileData.empty()){
//        for(const QString &s: zIntItem) {
//            tempV = zFileData.value(s);
//            temp = tempV.toInt(ok,10);
//            if(!ok){
//                if(tempV.length() !=0 && tempV.at(0) == '/'){
//                    temp = tempV.replace("/","9").toInt(ok);
//                    if(!ok){
//                        temp = 99999;
//                    }
//                }else if(tempV.length() !=0 && tempV.at(0) == ','){
//                    temp = tempV.replace(",","9").toInt(ok);
//                    if(!ok){
//                        temp = 99999;
//                    }
//                }else{
//                   temp = 99999;
//                }
//            }
//            zIntData.insert(s, temp);
//        }
//        zIntData.insert("CH",couldHeightFromZFileData(zFileData));
//    }
//    delete ok;
//    return zIntData;
//}

//QMap<QString,QString> DataFormatUtil::zFileData2ZStringData(const QMap<QString,QString> &zFileData){
//    QMap<QString,QString> zStringData ;
//    QString missing("/////");
//    for(const QString &s: zStringItem) {
//        if(zFileData.contains(s)){
//            zStringData.insert(s, zFileData.value(s));
//        }else{
//            zStringData.insert(s, missing);
//        }
//    }
//    return zStringData;
//}

//void DataFormatUtil::amendZTimeItem(QMap<QString,int> &zIntData) {
//    int temp = 999999;
//    for(const QString &s:zTimeItem) {
//        if(zIntData.contains(s)){
//            temp = zIntData.value(s);
//            if(temp >= 2400) {
//                temp -= 2400;
//            }
//            zIntData.insert(s, temp);
//        }
//    }
//}

//int DataFormatUtil::couldHeightFromZFileData(const QMap<QString,QString> &zFileData) {
//    int temp = 999999;
//    if(zFileData.contains("CH")){
//        return zFileData.value("CH").toInt();
//    }
//    return temp;
//}

//QString DataFormatUtil::zIntData2String(int zIntData) {

//}

