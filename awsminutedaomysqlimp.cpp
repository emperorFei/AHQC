#include "awsminutedaomysqlimp.h"

QString AWSMinuteDAOMySqlImp::findTByObserveTimeSql = "select tempis from AWSMinute where ObserveTime = ?";
QString AWSMinuteDAOMySqlImp::findOTDByOTSql = "select * from AWSMinute where observeTime = ?";
QString AWSMinuteDAOMySqlImp::getRecordsCountSql ="select count(*) from AWSMinute where observeTime between ? and ?";
QString AWSMinuteDAOMySqlImp::checkExistsSql = "select 1 from AWSMinute where ObserveTime = ?";

//max
QString AWSMinuteDAOMySqlImp::getMaxTByOnTimeSql = "select max(tempis)  from "
        "(select tempis from AWSMinute where observeTime between ? and ? ) as total "
        "where tempis!= 6666 and tempis != 9999";
QString AWSMinuteDAOMySqlImp::getMaxETByOnTimeSql = "select max(Groundtemppt)  from "
        "(select Groundtemppt from AWSMinute where observeTime between ? and ? ) as total "
        "where Groundtemppt != 6666 and Groundtemppt != 9999";
QString AWSMinuteDAOMySqlImp::getMaxGTByOnTimeSql = "select max(Grasstemp)  from "
        "(select Grasstemp from AWSMinute where observeTime between ? and ? ) as total "
        "where Grasstemp != 6666 and Grasstemp != 9999";
QString AWSMinuteDAOMySqlImp::getMaxPByOnTimeSql =  "select max(Pressure)  from "
        "(select Pressure from AWSMinute where observeTime between ? and ? ) as total "
        "where Pressure != 6666 and Pressure != 9999";
QString AWSMinuteDAOMySqlImp::getMaxWSByOnTimeSql =  "select max(Windspeed10)  from "
        "(select Windspeed10 from AWSMinute where observeTime between ? and ? ) as total "
        "where Windspeed10 != 6666 and Windspeed10 != 9999";
QString AWSMinuteDAOMySqlImp::getExWSByOnTimeSql =  "select max(Windspeed)  from "
        "(select Windspeed from AWSMinute where observeTime between ? and ? ) as total "
        "where Windspeed != 6666 and Windspeed != 9999";

//min
QString AWSMinuteDAOMySqlImp::getMinTByOnTimeSql = "select min(tempis)  from "
        "(select tempis from AWSMinute where observeTime between ? and ? ) as total "
        "where tempis!= 6666 and tempis != 9999";
QString AWSMinuteDAOMySqlImp::getMinETByOnTimeSql = "select min(Groundtemppt)  from "
        "(select Groundtemppt from AWSMinute where observeTime between ? and ? ) as total "
        "where Groundtemppt != 6666 and Groundtemppt != 9999";
QString AWSMinuteDAOMySqlImp::getMinGTByOnTimeSql = "select min(Grasstemp)  from "
        "(select Grasstemp from AWSMinute where observeTime between ? and ? ) as total "
        "where Grasstemp != 6666 and Grasstemp != 9999";
QString AWSMinuteDAOMySqlImp::getMinRHByOnTimeSql = "select min(Rh) from "
        "(select Rh from AWSMinute where observeTime between ? and ? ) as total "
        "where Rh != 6666 and Rh != 9999";
QString AWSMinuteDAOMySqlImp::getMinPByOnTimeSql = "select min(Pressure) from "
        "(select Pressure from AWSMinute where observeTime between ? and ? ) as total "
        "where Pressure != 6666 and Pressure != 9999";
QString AWSMinuteDAOMySqlImp::getMinVByOnTimeSql = "select min(Vis_10min) from "
        "(select Vis_10min from AWSMinute where observeTime between ? and ? ) as total "
        "where Vis_10min != 66666 and Vis_10min != 99999";
//rain
QString AWSMinuteDAOMySqlImp::getRainSql = "select sum(MRainweight-1000) from "
        "(select MRainweight from AWSMinute where observeTime between ? and ?) as total"
        " where MRainweight < 6666" ;
//sp
QString AWSMinuteDAOMySqlImp::getValue4SPSql = "select Pressure,tempis from AWSMinute "
        "where observeTime = ? "
        "union "
        "select Pressure,tempis from AWSMinute where observeTime = ?";
//extremum that not visible
QString AWSMinuteDAOMySqlImp::getVPSql = "select Pressure from AWSMinute "
                                         "where observeTime = ? "
                                         "union "
                                         "select Pressure from AWSMinute where observeTime = ?";
QString AWSMinuteDAOMySqlImp::getVTSql = "select tempis from AWSMinute "
                                         "where observeTime = ? "
                                         "union "
                                         "select tempis from AWSMinute where observeTime = ?";
QString AWSMinuteDAOMySqlImp::getMinTSql = "select min(tempis)  from "
        "(select tempis from AWSMinute where observeTime between ? and ? ) as total "
        "where tempis!= 6666 and tempis != 9999";
QString AWSMinuteDAOMySqlImp::getMaxTSql =  "select max(tempis)  from "
        "(select tempis from AWSMinute where observeTime between ? and ? ) as total "
        "where tempis!= 6666 and tempis != 9999";
QString AWSMinuteDAOMySqlImp::getExWSSql = "select max(Windspeed)  from "
        "(select Windspeed from AWSMinute where observeTime between ? and ? ) as total "
        "where Windspeed != 6666 and Windspeed != 9999";
QString AWSMinuteDAOMySqlImp::getExWDSql = "select WindDir from "
        " AWSMinute "
        " where observeTime = "
        "(select min(wst) from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as ttable "
        "where ws "
        "= (select max(ws)  from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as ttablet "
        " where ws != 6666 and ws != 9999))";
QString AWSMinuteDAOMySqlImp::getMinETSql = "select min(Groundtemppt)  from "
        "(select Groundtemppt from AWSMinute where observeTime between ? and ? ) as total "
        "where Groundtemppt != 6666 and Groundtemppt != 9999";
//maxT
QString AWSMinuteDAOMySqlImp::getMaxTTByOnTimeSql = "select min(tt) from "
        "(select observeTime as tt , tempis as t from AWSMinute where observeTime between ? and ?) as ttable "
        "where t = "
        "(select max(t) from "
        "(select observeTime as tt , tempis as t from AWSMinute where observeTime between ? and ?) as ttablet "
        "where t != 6666 and t != 9999)";
QString AWSMinuteDAOMySqlImp::getMaxETTByOnTimeSql = "select min(ett) from "
        "(select observeTime as ett , Groundtemppt as et from AWSMinute where observeTime between ? and ?) as ttable "
        "where et = "
        "(select max(et) from "
        "(select observeTime as ett , Groundtemppt as et from AWSMinute where observeTime between ? and ?) as ttablet "
        "where et != 6666 and et != 9999)";
QString AWSMinuteDAOMySqlImp::getMaxGTTByOnTimeSql = "select min(gtt) from "
        "(select observeTime as gtt , Grasstemp as gt from AWSMinute where observeTime between ? and ?) as ttable "
        "where gt = "
        "(select max(gt) from "
        "(select observeTime as gtt , Grasstemp as gt from AWSMinute where observeTime between ? and ?) as ttablet "
        "where gt != 6666 and gt != 9999)";
QString AWSMinuteDAOMySqlImp::getMaxPTByOnTimeSql = "select min(pt) from "
        "(select observeTime as pt , Pressure as p from AWSMinute where observeTime between ? and ?) as ttable "
        "where p = "
        "(select max(p) from "
        "(select observeTime as pt , Pressure as p from AWSMinute where observeTime between ? and ?) as ttablet "
        "where p != 6666 and p != 9999)";
QString AWSMinuteDAOMySqlImp::getMaxWSTByOnTimeSql = "select min(ws10t) from "
        "(select observeTime as ws10t , Windspeed10 as ws10 from AWSMinute where observeTime between ? and ?) as ttable "
        "where ws10 = "
        "(select max(ws10) from "
        "(select observeTime as ws10t , Windspeed10 as ws10 from AWSMinute where observeTime between ? and ?) as ttablet "
        "where ws10 != 6666 and ws10 != 9999)";
QString AWSMinuteDAOMySqlImp::getExWSTByOnTimeSql = "select min(wst) from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as ttable "
        "where ws = "
        "(select max(ws) from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as ttablet "
        "where ws != 6666 and ws != 9999)";
//minT
QString AWSMinuteDAOMySqlImp::getMinTTByOnTimeSql = "select min(tt) from "
        "(select observeTime as tt , tempis as t from AWSMinute where observeTime between ? and ?) as ttable "
        "where t = "
        "(select min(t) from "
        "(select observeTime as tt , tempis as t from AWSMinute where observeTime between ? and ?) as ttablet "
        "where t != 6666 and t != 9999)";
QString AWSMinuteDAOMySqlImp::getMinETTByOnTimeSql = "select min(ett) from "
        "(select observeTime as ett , Groundtemppt as et from AWSMinute where observeTime between ? and ?) as ttable "
        "where et = "
        "(select min(et) from "
        "(select observeTime as ett , Groundtemppt as et from AWSMinute where observeTime between ? and ?) as ttablet "
        "where et != 6666 and et != 9999)";
QString AWSMinuteDAOMySqlImp::getMinGTTByOnTimeSql = "select min(gtt) from "
        "(select observeTime as gtt , Grasstemp as gt from AWSMinute where observeTime between ? and ?) as ttable "
        "where gt = "
        "(select min(gt) from "
        "(select observeTime as gtt , Grasstemp as gt from AWSMinute where observeTime between ? and ?) as ttablet "
        "where gt != 6666 and gt != 9999)";
QString AWSMinuteDAOMySqlImp::getMinPTByOnTimeSql = "select min(pt) from "
        "(select observeTime as pt , Pressure as p from AWSMinute where observeTime between ? and ?) as ttable "
        "where p = "
        "(select min(p) from "
        "(select observeTime as pt , Pressure as p from AWSMinute where observeTime between ? and ?) as ttablet "
        "where p != 6666 and p != 9999)";
QString AWSMinuteDAOMySqlImp::getMinRHTByOnTimeSql = "select min(rht) from "
        "(select observeTime as rht , Rh as rh from AWSMinute where observeTime between ? and ?) as ttable "
        "where rh = "
        "(select min(rh) from "
        "(select observeTime as rht , Rh as rh from AWSMinute where observeTime between ? and ?) as ttablet "
        "where rh != 6666 and rh != 9999)";
QString AWSMinuteDAOMySqlImp::getMinVTByOnTimeSql = "select vt from "
        "(select observeTime as vt , Vis_10min as v from AWSMinute where observeTime between ? and ?) as ttable "
        "where v = "
        "(select min(v) from "
        "(select observeTime as vt , Vis_10min as v from AWSMinute where observeTime between ? and ?) as ttablet "
        "where v != 6666 and v != 9999)";
//WindDir
QString AWSMinuteDAOMySqlImp::getMaxWSDByOnTimeSql = "select WindDir10 from AWSMinute "
        " where observeTime = "
        "(select min(ws10t) from "
        "(select observeTime as ws10t , Windspeed10 as ws10 from AWSMinute where observeTime between ? and ?) as ttable "
        "where ws10 = "
        "(select max(ws10) from "
        "(select observeTime as ws10t , Windspeed10 as ws10 from AWSMinute where observeTime between ? and ?) as tandwstable "
        "where ws10 != 6666 and ws10 != 9999))";
QString AWSMinuteDAOMySqlImp::getExWSDByOnTimeSql = "select WindDir from AWSMinute "
        "where observeTime = "
        "(select min(wst) from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as ttable "
        "where ws = "
        "(select max(ws) from "
        "(select observeTime as wst , Windspeed as ws from AWSMinute where observeTime between ? and ?) as wstandwstable "
        "where ws != 6666 and ws != 9999))";



AWSMinuteDAOMySqlImp::AWSMinuteDAOMySqlImp(QSqlDatabase *conn, QObject *parent) : QObject(parent){
    this -> conn = conn;
    QString sBuilder("insert into AWSMinute values(0,?,?,?,?,");
    int intItems = GlobalSetting::getInstance() -> getColInfos() ->size() - 2;
    for(int i=0;i < intItems;i++){
        sBuilder.append("?,");
    }
    sBuilder.append("?,?)");
    insertSql = sBuilder;
}

bool AWSMinuteDAOMySqlImp::saveAWSMinuteData(const AWSMinuteData &amData){
    bool flag = false;
    QSqlQuery query(*conn);
    query.prepare(insertSql);
    int qmIndex = 0;    
    query.bindValue(++qmIndex, QVariant(amData.getObserveTime()));
    query.bindValue(++qmIndex, QVariant(amData.getObserveMonth()));
    query.bindValue(++qmIndex, QDateTime::currentDateTime());
    query.bindValue(++qmIndex, QVariant(QVariant::DateTime));
    QList<int> minuteData = amData.getData();
    for(int i: minuteData) {
         query.bindValue(++qmIndex, QVariant(i));
    }
    query.bindValue(++qmIndex, QVariant(amData.getWeatherphcode()));
    query.bindValue(++qmIndex, QVariant(amData.getDataQulity()));
    query.exec();
    conn->commit();
    query.finish();
    flag = true;
    return flag;
}

bool AWSMinuteDAOMySqlImp::saveAMFile(const QString &amFileName){
    bool flag = false;
    QString line("beforeInit");
    QList<AWSMinuteData> awsMinuteDatas;
    QFile amFile(amFileName);
    if(amFile.exists()){
        if(amFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream amIn(&amFile);
            QDate awsDay = AHQC::FileNameUtil::AMFileName2Date(amFileName);
            if(!amIn.atEnd()){
                line = amIn.readLine();
                while(!amIn.atEnd()){
                    line = amIn.readLine();
                    if(line.compare("") != 0 && line.at(0) != '-'){
                        AWSMinuteData awsMinuteData(awsDay,line);
                        awsMinuteDatas.append(awsMinuteData);
                    }
                }
            }
            amFile.close();
        }else{
            qDebug() << "file: " << amFileName << "can't open";
            return flag;
        }
    }else{
        qDebug() << "file: " << amFileName << "not exists";
        return flag;
    }
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
            //this point neeed report
            return flag;
        }
    }
    query.prepare(insertSql);
    QSqlQuery transaction_start(*conn);
    QSqlQuery transaction_COMMIT(*conn);
    QSqlQuery transaction_ROLLBACK(*conn);
    QDateTime beginExecBatch = QDateTime::currentDateTime();
    transaction_start.exec("START TRANSACTION");
    for(AWSMinuteData amData:awsMinuteDatas){
        int qmIndex = -1;
        query.bindValue(++qmIndex, QVariant(amData.getObserveTime()));
        query.bindValue(++qmIndex, QVariant(amData.getObserveMonth()));
        query.bindValue(++qmIndex, QDateTime::currentDateTime());
        query.bindValue(++qmIndex, QDateTime::currentDateTime());
        QList<int> minuteData = amData.getData();
        for(int i: minuteData) {
             query.bindValue(++qmIndex, QVariant(i));
        }
        query.bindValue(++qmIndex, QVariant(amData.getWeatherphcode()));
        query.bindValue(++qmIndex, QVariant(amData.getDataQulity()));

        bool seccess = query.exec();

//        qDebug() << seccess
//                 <<" " << amData.getObserveTime().toString("yyyyMMdd-HHmm")
//                 << " " << query.lastError().databaseText();
    }

    flag = transaction_COMMIT.exec("COMMIT");
//    QDateTime endExecBatch = QDateTime::currentDateTime();
//    flag = true;
    return flag;
}

int AWSMinuteDAOMySqlImp::getRecordsCount(const TimeRange &tr){
    QSqlQuery query(*conn);
    query.prepare(getRecordsCountSql);
    query.addBindValue(QVariant(tr.older));
    query.addBindValue(QVariant(tr.later));
    if(query.next()) {
        int count = query.value(0).toInt();
        return count;
    }
    query.finish();
    return 0;
}

bool AWSMinuteDAOMySqlImp::exists(const QDateTime &observeTime){
    bool flag = false;
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
        }
    }
    query.prepare(checkExistsSql);
    query.bindValue(0, QVariant(observeTime));
    query.exec();
    if(query.next()) {
        int result = query.value(0).toInt();
        result == 1 ? flag = true :flag = false;
        return flag;
    }
    return flag;
}
//find tempis for check data within db
int AWSMinuteDAOMySqlImp::findTempisByObserveTime(const QDateTime &observeTime){
    int temp = 0;
    QSqlQuery query(*conn);
    query.prepare(findTByObserveTimeSql);
    query.addBindValue(QVariant(observeTime));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
    }
    return temp;
}

//获得所有正点数据
AWSMinuteData AWSMinuteDAOMySqlImp::findByOT(const QDateTime &observeTime){
    QSqlQuery query(*conn);
    query.prepare(findOTDByOTSql);
    query.addBindValue(QVariant(observeTime));
    query.exec();
    AWSMinuteData ad;
    if(query.next()) {
        int index = 0;
        ad.setObserveTime(query.value(++index).toDateTime());
        ad.setObserveMonth(query.value(++index).toDate());
        ad.setMinute(ad.observeTime.time().toString("HHmm").toInt());
        ad.setObserveDay(AHQC::TimeUtil::dateTime2AWSDay(ad.observeTime));
        index += 2;
        QList<int> &intData = ad.data;
        int tempValue = 99999;
        int intDataNum = GlobalSetting::getInstance()->value("intDataNum").toInt()+5;
        for(++index; index < intDataNum;++index) {
            tempValue = query.value(index).toInt();
            intData.append(tempValue);
        }
        ad.setWeatherphcode(query.value(index).toString());
        ad.setDataQulity(query.value(++index).toString());
        ad.inited = true;
        query.finish();
    }
    return ad;
}

//获得所有极值
QMap<QString,int> AWSMinuteDAOMySqlImp::getExtremums(const QDateTime &observeTime){
    int temp = 99999;
    QMap<QString,int> extremums;
    //温
    temp = getMaxTByOT(observeTime);
    extremums.insert("MaxT", temp);
    temp = getMaxTTByOT(observeTime);
    extremums.insert("MaxTT", temp);
    temp = getMinTByOT(observeTime);
    extremums.insert("MinT", temp);
    temp = getMinTTByOT(observeTime);
    extremums.insert("MinTT", temp);
    temp = getMinT24ByOT(observeTime);
    extremums.insert("MinT24", temp);
    temp = getMaxT24ByOT(observeTime);
    extremums.insert("MaxT24", temp);

    temp = getMaxGTByOT(observeTime);
    extremums.insert("MaxGT", temp);
    temp = getMaxGTTByOT(observeTime);
    extremums.insert("MaxGTT", temp);
    temp = getMinGTByOT(observeTime);
    extremums.insert("MinGT", temp);
    temp = getMinGTTByOT(observeTime);
    extremums.insert("MinGTT", temp);

    temp = getMaxETByOT(observeTime);
    extremums.insert("MaxET", temp);
    temp = getMaxETTByOT(observeTime);
    extremums.insert("MaxETT", temp);
    temp = getMinETByOT(observeTime);
    extremums.insert("MinET", temp);
    temp = getMinETTByOT(observeTime);
    extremums.insert("MinETT", temp);
    temp = getMinET12ByOT(observeTime);
    extremums.insert("MinET12", temp);

    //压
    temp = getMaxPByOT(observeTime);
    extremums.insert("MaxP", temp);
    temp = getMaxPTByOT(observeTime);
    extremums.insert("MaxPT", temp);
    temp = getMinPByOT(observeTime);
    extremums.insert("MinP", temp);
    temp = getMinPTByOT(observeTime);
    extremums.insert("MinPT", temp);
    //湿
    temp = getMinRHByOT(observeTime);
    extremums.insert("MinRH", temp);
    temp = getMinRHTByOT(observeTime);
    extremums.insert("MinRHT", temp);
    //风
    temp = getMaxWSByOT(observeTime);
    extremums.insert("MaxWS", temp );
    temp = getMaxWSDByOT(observeTime);
    extremums.insert("MaxWD", temp );
    temp = getMaxWSTByOT(observeTime);
    extremums.insert("MaxWST", temp);
    temp = getExWSByOT(observeTime);
    extremums.insert("ExWS", temp );
    temp = getExWSDByOT(observeTime);
    extremums.insert("ExWD", temp);
    temp = getExWSTByOT(observeTime);
    extremums.insert("ExWST", temp);
    temp = getExWS6ByOT(observeTime);
    extremums.insert("ExWS6", temp );
    temp = getExWS12ByOT(observeTime);
    extremums.insert("ExWS12", temp );
    temp = getExWD6ByOT(observeTime);
    extremums.insert("ExWD6", temp );
    temp = getExWD12ByOT(observeTime);
    extremums.insert("ExWD12", temp );

    //能见度
    temp = getMinVByOT(observeTime);
    extremums.insert("MinV", temp);
    temp = getMinVTByOT(observeTime);
    extremums.insert("MinVT", temp);

//    //雨量
//    extremums.insert("HRain", temp);
//    temp = getHRain3ByOT(observeTime);
//    extremums.insert("HRain3",temp);
//    temp = getHRain6ByOT(observeTime);
//    extremums.insert("HRain6", temp);
//    temp = getHRain12ByOT(observeTime);
//    extremums.insert("HRain12",temp);
//    temp = getHRain24ByOT(observeTime);
//    extremums.insert("HRain24",temp);


    return extremums;
}

//获取变化值，雨量，海平面气压
QMap<QString,int> AWSMinuteDAOMySqlImp::getVAndRain(const QDateTime &observeTime){
    int temp = 99999;
    QMap<QString,int> VAndRain;
    temp = getVP3ByOT(observeTime);
    VAndRain.insert("VP3",temp);
    temp = getVP24ByOT(observeTime);
    VAndRain.insert("VP24",temp);
    temp = getVT24ByOT(observeTime);
    VAndRain.insert("VT24",temp);
    temp = getHRainByOT(observeTime);
    VAndRain.insert("HRain", temp);
    temp = getHRain3ByOT(observeTime);
    VAndRain.insert("HRain3",temp);
    temp = getHRain6ByOT(observeTime);
    VAndRain.insert("HRain6", temp);
    temp = getHRain12ByOT(observeTime);
    VAndRain.insert("HRain12",temp);
    temp = getHRain24ByOT(observeTime);
    VAndRain.insert("HRain24",temp);
    temp = getSPByOT(observeTime);
    VAndRain.insert("SP",temp);
    return VAndRain;
}

//real work functions
//functions that real access DB
int AWSMinuteDAOMySqlImp::getMaxByOnTime(QDateTime onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType){
    int temp = 99999;
    QString sql = getMaxSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime firstMinute = onTimeDate.addSecs(-59*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    bool success = query.exec();
    QString errorMessage(query.lastError().databaseText());
//    qDebug() << success << " : " << query.lastError().databaseText();
    if(query.next()) {
        temp = query.value(0).toInt();
        if(awsItemType != V && awsItemType!= P){
            temp -= 1000;
        }
    }
    return temp;
}
int AWSMinuteDAOMySqlImp::getMinByOnTime(const QDateTime &onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType){
    int temp = 99999;
    QString sql = getMinSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime firstMinute = onTimeDate.addSecs(-59*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
        if(awsItemType != V && awsItemType!= P){
            temp -= 1000;
        }
    }
    return temp;
}
int AWSMinuteDAOMySqlImp::getMaxTimeByOnTime(const QDateTime &onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType){
    int temp = 99999;
    QString sql = getMaxTimeSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime firstMinute = onTimeDate.addSecs(-59*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.exec();
    if(query.next()) {
        temp = std::atoi(query.value(0).toDateTime().time().toString("HHmm").toStdString().c_str());
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getMinTimeByOnTime(const QDateTime &onTimeDate,AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    int temp = 99999;
    QString sql = getMinTimeSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime firstMinute = onTimeDate.addSecs(-59*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.exec();
    if(query.next()) {
        temp = std::atoi(query.value(0).toDateTime().time().toString("HHmm").toStdString().c_str());
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getWDByOnTime(const QDateTime &onTimeDate, AWSMinuteDAOMySqlImp::AWSItemType awsItemType){
    int temp = 99999;
    QString sql = getMaxSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime firstMinute = onTimeDate.addSecs(-59*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
        temp -= 1000;
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getNVWD(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    int temp = 99999;
    QString sql = getNVSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime startTime = tr.older;
    QDateTime endTime  = tr.later;
    query.addBindValue(QVariant(startTime));
    query.addBindValue(QVariant(endTime));
    query.addBindValue(QVariant(startTime));
    query.addBindValue(QVariant(endTime));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
        temp -= 1000;
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getNVExtremum(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    int temp = 99999;
    QString sql = getNVSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime startTime = tr.older;
    QDateTime endTime  = tr.later;
    query.addBindValue(QVariant(startTime));
    query.addBindValue(QVariant(endTime));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
        temp -= 1000;
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getVariatedValue(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    int missingNum = 99999;
    if(awsItemType == AWSMinuteDAOMySqlImp::AWSItemType::VT24){
        missingNum = 9999;
    }
    int valueBefore = missingNum;
    int valueLater = missingNum;
    int temp = missingNum;

    QString sql = getNVSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime startTime = tr.older;
    QDateTime endTime  = tr.later;
    query.addBindValue(QVariant(startTime));
    query.addBindValue(QVariant(endTime));
    query.exec();
    if(query.next()) {
        valueBefore = query.value(0).toInt();
    }
    if(query.next()) {
        valueLater = query.value(0).toInt();
    }
    if(valueBefore != missingNum && valueLater != missingNum ) {
        temp = valueLater - valueBefore;
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getRain(const TimeRange &tr,AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    int temp = 99999;
    QString sql = getRainSqlString(awsItemType);
    QSqlQuery query(*conn);
    query.prepare(sql);
    QDateTime startTime = tr.older;
    QDateTime endTime  = tr.later;
    query.addBindValue(QVariant(startTime));
    query.addBindValue(QVariant(endTime));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
    }
    query.finish();
    return temp;
}
int AWSMinuteDAOMySqlImp::getSP(const QDateTime &onTimeDate) {
    int temp = 99999;
    int t12  = 99999;
    int t0 = 99999;
    int pressure = 99999;
    QSqlQuery query(*conn);
    query.prepare(getValue4SPSql);
    QDateTime firstMinute = onTimeDate.addSecs(-12*60*60);
    QDateTime lastMinute  = onTimeDate;
    query.addBindValue(QVariant(firstMinute));
    query.addBindValue(QVariant(lastMinute));
    query.exec();
    if(query.next()) {
        t12 = query.value(1).toInt();
    }
    if(query.next()) {
        pressure = query.value(0).toInt();
        t0 = query.value(1).toInt();
    }
    if(t12 != 99999 && pressure != 99999 && t0 != 99999) {
        t12 -= 1000;
        t0 -= 1000;
        double dt12 = t12/10;
        double dt0 = t0/10;
        double ph = GlobalSetting::getInstance() -> value("presureHeight").toDouble();
        temp = qRound(pressure * qPow(10, (ph/(18400*(1+(((dt0+dt12)/2+(ph/400))/273))))));
    }
    query.finish();
    return temp;
}



//functions for get sql Strings
QString AWSMinuteDAOMySqlImp::getMinSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch (awsItemType){
    case AWSItemType::T:
        return getMinTByOnTimeSql;
    case AWSItemType::GT:
        return getMinGTByOnTimeSql;
    case AWSItemType::ET:
        return getMinETByOnTimeSql;
    case AWSItemType::P:
        return getMinPByOnTimeSql;
    case AWSItemType::Rh:
        return getMinRHByOnTimeSql;
    case AWSItemType::V:
        return getMinVByOnTimeSql;
    default:
        return "";
    }
}
QString AWSMinuteDAOMySqlImp::getMinTimeSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch (awsItemType){
    case AWSItemType::T:
        return getMinTTByOnTimeSql;
    case AWSItemType::GT:
        return getMinGTTByOnTimeSql;
    case AWSItemType::ET:
        return getMinETTByOnTimeSql;
    case AWSItemType::P:
        return getMinPTByOnTimeSql;
    case AWSItemType::Rh:
        return getMinRHTByOnTimeSql;
    case AWSItemType::V:
        return getMinVTByOnTimeSql;
    default:
        return "";
    }
}
QString AWSMinuteDAOMySqlImp::getMaxSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch (awsItemType){
    case AWSItemType::T:
        return getMaxTByOnTimeSql;
    case AWSItemType::GT:
        return getMaxGTByOnTimeSql;
    case AWSItemType::ET:
        return getMaxETByOnTimeSql;
    case AWSItemType::P:
        return getMaxPByOnTimeSql;
    case AWSItemType::WS:
        return getMaxWSByOnTimeSql;
    case AWSItemType::exWS:
        return getExWSByOnTimeSql;
    case AWSItemType::WSD:
        return getMaxWSDByOnTimeSql;
    case AWSItemType::exWSD:
        return getExWSDByOnTimeSql;
    default:
        return "";
    }
}
QString AWSMinuteDAOMySqlImp::getMaxTimeSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch (awsItemType){
    case AWSItemType::T:
        return getMaxTTByOnTimeSql;
    case AWSItemType::GT:
        return getMaxGTTByOnTimeSql;
    case AWSItemType::ET:
        return getMaxETTByOnTimeSql;
    case AWSItemType::P:
        return getMaxPTByOnTimeSql;
    case AWSItemType::WS:
        return getMaxWSTByOnTimeSql;
    case AWSItemType::exWS:
        return getExWSTByOnTimeSql;
    default:
        return "";
    }
}
QString AWSMinuteDAOMySqlImp::getNVSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch(awsItemType) {
    case AWSItemType::VP3:
        return getVPSql;
    case AWSItemType::VP24:
        return getVPSql;
    case AWSItemType::VT24:
        return getVTSql;
    case AWSItemType::ExWS6:
        return getExWSSql;
    case AWSItemType::ExWD6:
        return getExWDSql;
    case AWSItemType::ExWS12:
        return getExWSSql;
    case AWSItemType::ExWD12:
        return getExWDSql;
    case AWSItemType::MinT24:
        return getMinTSql;
    case AWSItemType::MaxT24:
        return getMaxTSql;
    case AWSItemType::MinET12:
        return getMinETSql;
    default:
        return "";
    }
}
QString AWSMinuteDAOMySqlImp::getRainSqlString(AWSMinuteDAOMySqlImp::AWSItemType awsItemType) {
    switch(awsItemType) {
    case AWSItemType::HRain:
        return getRainSql;
    case AWSItemType::HRain3:
        return getRainSql;
    case AWSItemType::HRain6:
        return getRainSql;
    case AWSItemType::HRain12:
        return getRainSql;
    case AWSItemType::HRain24:
        return getRainSql;
    default:
        return "";
    }
}

//T
int AWSMinuteDAOMySqlImp::getMaxTByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,T);
}
int AWSMinuteDAOMySqlImp::getMaxTTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,T);
}
int AWSMinuteDAOMySqlImp::getMinTByOT(QDateTime onTime){
    return getMinByOnTime(onTime,T);
}
int AWSMinuteDAOMySqlImp::getMinTTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,T);
}
int AWSMinuteDAOMySqlImp::getMinT24ByOT(QDateTime onTime){
    return getNVExtremum(AHQC::TimeUtil::getTimeRange4Sum(onTime, 24),MinT24);
}
int AWSMinuteDAOMySqlImp::getMaxT24ByOT(QDateTime onTime){
    return getNVExtremum(AHQC::TimeUtil::getTimeRange4Sum(onTime, 24),MaxT24);
}
int AWSMinuteDAOMySqlImp::getVT24ByOT(QDateTime onTime){
    return getVariatedValue(AHQC::TimeUtil::getTimeRange(onTime, 24),VT24);
}
//getGT

int AWSMinuteDAOMySqlImp::getMaxGTByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,GT);
}
int AWSMinuteDAOMySqlImp::getMaxGTTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,GT);
}
int AWSMinuteDAOMySqlImp::getMinGTByOT(QDateTime onTime){
    return getMinByOnTime(onTime,GT);
}
int AWSMinuteDAOMySqlImp::getMinGTTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,GT);
}
//getET

int AWSMinuteDAOMySqlImp::getMaxETByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,ET);
}
int AWSMinuteDAOMySqlImp::getMaxETTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,ET);
}
int AWSMinuteDAOMySqlImp::getMinETByOT(QDateTime onTime){
    return getMinByOnTime(onTime,ET);
}
int AWSMinuteDAOMySqlImp::getMinETTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,ET);
}
int AWSMinuteDAOMySqlImp::getMinET12ByOT(QDateTime onTime){
    return getNVExtremum(AHQC::TimeUtil::getTimeRange4Sum(onTime, 12),MinET12);
}
//getP

//P
int AWSMinuteDAOMySqlImp::getMaxPByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,P);
}
int AWSMinuteDAOMySqlImp::getMaxPTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,P);
}
int AWSMinuteDAOMySqlImp::getMinPByOT(QDateTime onTime){
    return getMinByOnTime(onTime,P);
}
int AWSMinuteDAOMySqlImp::getMinPTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,P);
}
int AWSMinuteDAOMySqlImp::getVP3ByOT(QDateTime onTime){
    return getVariatedValue(AHQC::TimeUtil::getTimeRange(onTime, 3),VP3);
}
int AWSMinuteDAOMySqlImp::getVP24ByOT(QDateTime onTime){
    return getVariatedValue(AHQC::TimeUtil::getTimeRange(onTime, 24),VP24);
}
int AWSMinuteDAOMySqlImp::getSPByOT(QDateTime onTime){
    return getSP(onTime);
}
//getRh

//RH
int AWSMinuteDAOMySqlImp::getMinRHByOT(QDateTime onTime){
    return getMinByOnTime(onTime,Rh);
}
int AWSMinuteDAOMySqlImp::getMinRHTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,Rh);
}
//getWind

//wind
int AWSMinuteDAOMySqlImp::getMaxWSByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,WS);
}
int AWSMinuteDAOMySqlImp::getMaxWSTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,WS);
}
int AWSMinuteDAOMySqlImp::getMaxWSDByOT(QDateTime onTime){
    return getWDByOnTime(onTime,WSD);
}
int AWSMinuteDAOMySqlImp::getExWSByOT(QDateTime onTime){
    return getMaxByOnTime(onTime,exWS);
}
int AWSMinuteDAOMySqlImp::getExWSTByOT(QDateTime onTime){
    return getMaxTimeByOnTime(onTime,exWS);
}
int AWSMinuteDAOMySqlImp::getExWSDByOT(QDateTime onTime){
    return getWDByOnTime(onTime,exWSD);
}
int AWSMinuteDAOMySqlImp::getExWS6ByOT(QDateTime onTime){
    return getNVExtremum(AHQC::TimeUtil::getTimeRange4Sum(onTime, 6),ExWS6);
}
int AWSMinuteDAOMySqlImp::getExWS12ByOT(QDateTime onTime){
    return getNVExtremum(AHQC::TimeUtil::getTimeRange4Sum(onTime, 12),ExWS12);
}
int AWSMinuteDAOMySqlImp::getExWD6ByOT(QDateTime onTime){
    return getNVWD(AHQC::TimeUtil::getTimeRange4Sum(onTime, 6),ExWD6);
}
int AWSMinuteDAOMySqlImp::getExWD12ByOT(QDateTime onTime){
    return getNVWD(AHQC::TimeUtil::getTimeRange4Sum(onTime, 12),ExWD12);
}
//getRain

//Rain
int AWSMinuteDAOMySqlImp::getHRainByOT(QDateTime onTime){
    return getRain(AHQC::TimeUtil::getTimeRange4Sum(onTime, 1),HRain);
}
int AWSMinuteDAOMySqlImp::getHRain3ByOT(QDateTime onTime){
    return AWSMinuteDAOMySqlImp::getRain(AHQC::TimeUtil::getTimeRange4Sum(onTime, 3),HRain3);
}
int AWSMinuteDAOMySqlImp::getHRain6ByOT(QDateTime onTime){
    return getRain(AHQC::TimeUtil::getTimeRange4Sum(onTime, 6),HRain6);
}
int AWSMinuteDAOMySqlImp::getHRain12ByOT(QDateTime onTime){
    return getRain(AHQC::TimeUtil::getTimeRange4Sum(onTime, 12),HRain12);
}
int AWSMinuteDAOMySqlImp::getHRain24ByOT(QDateTime onTime){
    return getRain(AHQC::TimeUtil::getTimeRange4Sum(onTime, 24),HRain24);
}

//Visibility
int AWSMinuteDAOMySqlImp::getMinVByOT(QDateTime onTime){
    return getMinByOnTime(onTime,V);
}
int AWSMinuteDAOMySqlImp::getMinVTByOT(QDateTime onTime){
    return getMinTimeByOnTime(onTime,V);
}

