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
const QString DataFormatUtil::AHDataAndZData[] =
        {
            "CA","CH","E","ET","ET10","ET15","ET160","ET20","ET320",
            "ET40","ET5","ET80","ExWD","ExWD12","ExWD6","ExWS","ExWS12",
            "ExWS6","ExWST","GT",
            "HRain","HRain12","HRain24",
            "HRain3","HRain6","LCA",
            "MaxET","MaxETT","MaxGT","MaxGTT",
            "MaxP","MaxPT","MaxT","MaxT24","MaxTT",
            "MaxWD","MaxWS","MaxWST","MinET","MinET12",
            "MinETT","MinGT","MinGTT","MinP","MinPT","MinRH",
            "MinRHT","MinT","MinT24","MinTT","MinV",
            "MinVT","P","RH","SP","SnowD","T",
            "TD","V1","V10","VP24","VP3","VT24",
            "WD","WD10","WD2","WP","WS","WS10","WS2"

        };
const QString DataFormatUtil::UIComponentName[] =
        {
            "CA","CH","E","ET","ET10","ET15","ET160","ET20","ET320",
            "ET40","ET5","ET80","ExWD","ExWD12","ExWD6","ExWS","ExWS12",
            "ExWS6","ExWST","GT",
            "HRain","HRain12","HRain24",
            "HRain3","HRain6","LCA",
            "MaxET","MaxETT","MaxGT","MaxGTT",
            "MaxP","MaxPT","MaxT","MaxT24","MaxTT",
            "MaxWD","MaxWS","MaxWST","MinET","MinET12",
            "MinETT","MinGT","MinGTT","MinP","MinPT","MinRH",
            "MinRHT","MinT","MinT24","MinTT","MinV",
            "MinVT","P","RH","SP","SnowD","T",
            "TD","V1","V10","VP24","VP3","VT24",
            "WD","WD10","WD2","WP","WS","WS10","WS2",
            "CCX","CF","CFC","EC","FE1D","FE1U","FE2D","FE2U","GA","HA","HMRain","MWW","PPHeight",
        };
const QString DataFormatUtil::itemsOnlyInAHData[] =
        {
            "FreezingRain","Frozensoliddeep","GTI","HRH","HRW","HRainR","HRainR1","Lightingfreq","MRR","MRR1","MRW","MRSC",
            "OE","WS10C","WS2C","WetT","Wireice","rsT","rsWS"

        };
const QString DataFormatUtil::itemsOnlyInZData[] =
        {
            "CCX","CF","CFC","EC","FE1D","FE1U","FE2D","FE2U","GA","HA","HMRain","MWW","PPHeight",
            "Q1CW","Q1DT","Q1MR","Q1PP","Q1RE","Q1SP","Q1TH","Q1VV","Q1WI",
            "Q2CW","Q2DT","Q2MR","Q2PP","Q2RE","Q2SP","Q2TH","Q2VV","Q2WI",
            "Q3CW","Q3DT","Q3MR","Q3PP","Q3RE","Q3SP","Q3TH","Q3VV","Q3WI",
            "QCCode","RCA","RainM","RainMT","SnowP","TRD","TRT","V","W1","W2","WT","WW",
            "awsMode","height","latitude","longitude","stationNum","time"
        };
const QString DataFormatUtil::zFileSectionID[] =
        {
            "PP","TH","RH","RE","WI","DT","VV","CW","SP","MR","MW","QC","Q1","Q2","Q3"
        };
const QString DataFormatUtil::simpleValidteItems_3Byte[] =
        {
            "RH","MinRH","WP","CA","LCA","WS","WS10","WS2","ExWS","ExWS12","ExWS6","MaxWS",
        };
const QString DataFormatUtil::simpleValidteItems_4Byte[] =
        {
            "E","ET","ET10","ET15","ET160","ET20","ET320",
            "ET40","ET5","ET80","GT",
            "MaxET","MaxGT",
            "MaxT","MaxT24",
            "MinET","MinET12",
            "MinGT",
            "MinT","MinT24",
            "T",
            "TD","VP24","VP3","VT24","SnowD"    
        };
const QString DataFormatUtil::simpleValidteItems_5Byte[] =
        {
            "P","MaxP","MinP","SP","V1","V10","MinV"
        };
const QString DataFormatUtil::rainItems[] =
        {
            "HRain","HRain3","HRain6","HRain12","HRain24",
        };
const QString DataFormatUtil::zTimeItem[] =
        {
            "MaxPT","MinPT","MaxTT","MinTT","MinRHT",
            "MaxETT","MinETT","MaxGTT","MinGTT","MinVT","MaxWST","ExWST"
        };
const QString DataFormatUtil::zManualItems[] =
        {
            "CCX","CF","CFC","EC","FE1D","FE1U","FE2D","FE2U","GA","HA",
            "QCCode","RCA","RainM","RainMT","SnowP","TRD","TRT","V","WT","awsMode"
        };
const QString DataFormatUtil::zItemsShouldMinusByThousand[] =
        {
            "T","MaxT","MinT","VT24","MaxT24","MinT24","TD",
            "ET","MaxET","MinET","MinET12","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320",
            "GT","MaxGT","MinGT","VP3","VP24"
        };
const QString DataFormatUtil::zWindDirectionItems[] =
        {
            "WD","WD10","WD2","MaxWD","ExWD","ExWD12","ExWD6",
        };
const QString DataFormatUtil::ahItemsShouldMinusThousand[] =
        {
            "WD2","WS2","WD10","WS10","WD","WS","WS2C","WS10C",
            "MWSC","MRR","HRainR","MRR1","HRainR1","MRW","HRW",
            "T","rsWS","rsT","WetT","HRH","RH","WP","TD","GT",
            "ET","GTI","ET5","ET10","ET15","ET20","ET40","ET80","ET160","ET320",
            "OE","E","CA","LCA","SnowD","FreezingRain","Wireice","Frozensoilddeep","Lightingfreq"
        };
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

void DataFormatUtil::validateAndExport2AZData(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                                              const QMap<QString,int> &ahData,
                                              const QMap<QString,QString> &zData)
{
    QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > dataOfAZ;
    QMap<QString,int> ahIntData(ahData);
    QMap<QString,QString> zStringData(zData);
    zTime2LocalTime(zStringData);
    ahItemMinusThousand(ahIntData);
    zItemMinusByThousand(zStringData);

    validateSimpleItems(dataOfAZ,ahIntData,zStringData);
    validateTimeItems(dataOfAZ,ahIntData,zStringData);
    validateWD(dataOfAZ,ahIntData,zStringData);
    validateRain(dataOfAZ,ahIntData,zStringData);
    validateManualItems(dataOfAZ,ahIntData,zStringData);
    data.unite(dataOfAZ);
}

void DataFormatUtil::validateSimpleItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                                         QMap<QString,int> &ahData,
                                         QMap<QString,QString> &zData)
{
    int zValue = 99999;
    QString zValueString("");
    int ahValue = 99999;
    QString ahValueString("");
    QString missingString = "/////";
    QString noTaskPlaceHoldeString = "-----";
    int missingNum = 99999;
    int noTaskPlaceHolderNum = 66666;
    AHQC::DataLevel dataLeval = AHQC::DataLevel::ERROR;
    for(const QString &item : simpleValidteItems_5Byte){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        ahValueString = QString::number(ahValue);
        if(zValueString != missingString){
            zValue = std::atoi(zValueString.toStdString().c_str());
            zValueString = QString::number(zValue);
        }else{
            zValue = missingNum;
        }
        if(ahValue == missingNum){
            ahValueString = missingString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else if(ahValue == noTaskPlaceHolderNum){
            ahValueString = noTaskPlaceHoldeString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else{
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                if(ahValue == zValue){
                  dataLeval = AHQC::DataLevel::INFO;
                }else{
                  dataLeval = AHQC::DataLevel::CLASH;
                }
            }
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
    missingString = "////";
    noTaskPlaceHoldeString = "----";
    missingNum = 9999;
    noTaskPlaceHolderNum = 6666;
    for(const QString &item : simpleValidteItems_4Byte){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        ahValueString = QString::number(ahValue);
        if(zValueString != missingString){
            zValue = std::atoi(zValueString.toStdString().c_str());
            zValueString = QString::number(zValue);
        }else{
            zValue = missingNum;
        }
        if(ahValue == missingNum){
            ahValueString = missingString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else if(ahValue == noTaskPlaceHolderNum){
            ahValueString = noTaskPlaceHoldeString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else{
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                if(ahValue == zValue){
                  dataLeval = AHQC::DataLevel::INFO;
                }else{
                  dataLeval = AHQC::DataLevel::CLASH;
                }
            }
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
    missingString = "///";
    noTaskPlaceHoldeString = "---";
    missingNum = 9999;
    noTaskPlaceHolderNum = 6666;
    for(const QString &item : simpleValidteItems_3Byte){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        ahValueString = QString::number(ahValue);
        if(zValueString != missingString){
            zValue = std::atoi(zValueString.toStdString().c_str());
            zValueString = QString::number(zValue);
        }else{
            zValue = missingNum;
        }
        if(ahValue == missingNum){
            ahValueString = missingString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else if(ahValue == noTaskPlaceHolderNum){
            ahValueString = noTaskPlaceHoldeString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else{
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                if(ahValue == zValue){
                  dataLeval = AHQC::DataLevel::INFO;
                }else{
                  dataLeval = AHQC::DataLevel::CLASH;
                }
            }
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
}
void DataFormatUtil::validateTimeItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                        QMap<QString,int> &ahData,
                        QMap<QString,QString> &zData){

    int zValue = 9999;
    QString zValueString("");
    int ahValue = 9999;
    QString ahValueString("");
    QString missingString = "////";
    QString noTaskPlaceHoldeString = "----";
    int missingNum = 9999;
    int noTaskPlaceHolderNum = 6666;
    AHQC::DataLevel dataLeval = AHQC::DataLevel::ERROR;
    for(const QString &item : zTimeItem){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        ahValueString = QString::number(ahValue);
        if(zValueString != missingString){
            zValue = std::atoi(zValueString.toStdString().c_str());
        }else{
            zValue = missingNum;
        }
        if(ahValue == missingNum){
            ahValueString = missingString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else if(ahValue == noTaskPlaceHolderNum){
            ahValueString = noTaskPlaceHoldeString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else{
            ahValueString = QString("%1").arg(ahValue, 4, 10, QChar('0'));
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                if(ahValue == zValue){
                  dataLeval = AHQC::DataLevel::INFO;
                }else{
                  dataLeval = AHQC::DataLevel::CLASH;
                }
            }
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
}
void DataFormatUtil::validateWD(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                       QMap<QString,int> &ahData,
                       QMap<QString,QString> &zData)
{
    QString zValueString("");
    QString ahValueString("");
    int ahValue = 9999;
    int zValue = 9999;
    QString WSItem("");
    QString WS_Z_String("");
    int WS_AH = 9999;
    int WS_Z = 9999;
    AHQC::DataLevel dataLeval = AHQC::DataLevel::ERROR;
    for(const QString &item : zWindDirectionItems){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        if(ahValue == 9999){
            ahValueString = "///";
        }else{
            ahValueString = QString("%1").arg(ahValue, 3, 10, QChar('0'));
        }
        if(!zValueString.isEmpty() && zValueString.at(0) != '/'){
            if(zValueString.at(0) != 'C'){
                zValue = std::atoi(zValueString.toStdString().c_str());
                if(ahValue != zValue){
                     dataLeval = AHQC::DataLevel::CLASH;
                }else{
                     dataLeval = AHQC::DataLevel::INFO;
                }
            }else{
                WSItem = item;
                WSItem.replace("D","S");
                WS_AH = ahData.value(WSItem);
                WS_Z_String = zData.value(WSItem);
                if(!WS_Z_String.isEmpty() && WS_Z_String.at(0) != '/'){
                    WS_Z = std::atoi(WS_Z_String.toStdString().c_str());
                    if(WS_AH < 2 && WS_Z < 2){
                        dataLeval = AHQC::DataLevel::INFO;
                    }else{
                        dataLeval = AHQC::DataLevel::ERROR;
                    }
                }else{
                    if(WS_AH < 2 ){
                       dataLeval = AHQC::DataLevel::INFO;
                    }else{
                       dataLeval = AHQC::DataLevel::CLASH;
                    }
                }
            }
        }else{
            dataLeval = AHQC::DataLevel::MISSING;
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
}

void DataFormatUtil::validateRain(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                        QMap<QString,int> &ahData,
                        QMap<QString,QString> &zData)
{
    int zValue = 99999;
    QString zValueString("");
    int ahValue = 99999;
    QString ahValueString("");
    QString missingString = "/////";
    int missingNum = 99999;
    AHQC::DataLevel dataLeval = AHQC::DataLevel::ERROR;
    for(const QString &item : rainItems){
        zValueString = zData.value(item);
        ahValue = ahData.value(item);
        ahValueString = QString::number(ahValue);
        if(zValueString != missingString){
            zValue = std::atoi(zValueString.toStdString().c_str());
            zValueString = QString::number(zValue);
        }else{
            zValue = missingNum;
        }
        if(ahValue == missingNum){
            ahValueString = missingString;
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                dataLeval = AHQC::DataLevel::SUSPECTED;
            }
        }else{
            if(zValueString == missingString){
                dataLeval = AHQC::DataLevel::MISSING;
            }else{
                if(ahValue == zValue){
                  dataLeval = AHQC::DataLevel::INFO;
                }else{
                  dataLeval = AHQC::DataLevel::CLASH;
                }
            }
        }
        QPair<QString,QString> dataPair(ahValueString,zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }
    if(data["HRain"].first.first == "/////"){
        QString second = data["HRain"].first.second;
        AHQC::DataLevel dataLevelOfHRain = data["HRain"].second;
        QPair<QString,QString> dataPair("////",second);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLevelOfHRain);
        data["HRain"] = pair;
    }

}

void DataFormatUtil::validateManualItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                        QMap<QString,int> &ahData,
                        QMap<QString,QString> &zData)
{
    QString zValueString("");
    zValueString = zData.value("CH");
    AHQC::DataLevel dataLeval = AHQC::DataLevel::INFO;
    QPair<QString,QString> dataPair("-----",zValueString);
    QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
    data.insert("CH",pair);

    data["SnowD"] = QPair<QPair<QString,QString>,AHQC::DataLevel>(data["SnowD"].first,AHQC::DataLevel::INFO);
    data["CA"] = QPair<QPair<QString,QString>,AHQC::DataLevel>(data["CA"].first,AHQC::DataLevel::INFO);
    data["LCA"] = QPair<QPair<QString,QString>,AHQC::DataLevel>(data["LCA"].first,AHQC::DataLevel::INFO);


    for(const QString &item : zManualItems){
        zValueString = zData.value(item);
        dataLeval = AHQC::DataLevel::INFO;
        QPair<QString,QString> dataPair("----",zValueString);
        QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,dataLeval);
        data.insert(item,pair);
    }

    QString w1 = zData.value("w1");
    QString w2 = zData.value("w2");
    QString WW = zData.value("WW");

    dataLeval = AHQC::DataLevel::INFO;
    QPair<QString,QString> wwWWDataPair("----",zValueString);
    QPair<QPair<QString,QString>,AHQC::DataLevel> wwWWPair(dataPair,dataLeval);
    data.insert("wwWW",wwWWPair);

}

void DataFormatUtil::zTime2LocalTime(QMap<QString,QString> &zData){
    QString zTimeString("");
    int zTime = 9999;
    for(const QString &item :zTimeItem){
        zTimeString = zData.value(item);
        if(!zTimeString.isEmpty() && zTimeString.at(0) != '/'){
            zTime = std::atoi(zTimeString.toStdString().c_str());
            zTime += 800;
            if(zTime >= 2400){
                zTime -= 2400;
            }
            zData[item] = QString("%1").arg(zTime, 4, 10, QChar('0'));
        }
    }
}
void DataFormatUtil::ahItemMinusThousand(QMap<QString,int> &ahData){
    int itemValue = 9999;
    for(const QString &item :ahItemsShouldMinusThousand){
        itemValue = ahData.value(item);
        if(itemValue < 6666){
            itemValue -= 1000;
            ahData[item] = itemValue;
        }
    }
}
void DataFormatUtil::zItemMinusByThousand(QMap<QString,QString> &zData){
    QString itemValueString("");
    int itemValue = 9999;
    for(const QString &item :zItemsShouldMinusByThousand){
        itemValueString = zData.value(item);
        if(!itemValueString.isEmpty() && itemValueString.at(0) != '/'){
            itemValue = std::atoi(itemValueString.toStdString().c_str());
            itemValue = 1000 - itemValue;
            zData[item] = QString::number(itemValue);
        }
    }
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

