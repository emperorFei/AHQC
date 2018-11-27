#include "zdatadaomysqlimp.h"
QString ZDataDAOMysqlImp::checkExistsSql = "select isNull((select 1 from ZData where ObserveTime = ?),0) ";
QString ZDataDAOMysqlImp::findTByObserveTimeSql = "select tempis from ZData where ObserveTime = ?";
QString ZDataDAOMysqlImp::findOTDByOTSql = "select * from ZData where observeTime = ?";
QString ZDataDAOMysqlImp::getRecordsCountSql ="select count(*) from ZData where observeTime between ? and ?";

ZDataDAOMysqlImp::ZDataDAOMysqlImp(QSqlDatabase *conn):conn(conn)
{
    QString sBuilder("insert into ZData values(0,?,?,?,?");
    int intItems = 128;
    for(int i=0;i < intItems;i++){
        sBuilder.append(",?");
    }
    sBuilder.append(")");
    insertSql = sBuilder;
}

int ZDataDAOMysqlImp::findTempisByObserveTime(const QDateTime &observeTime){
    int temp = 0;
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
            //this point neeed report
        }
    }
    query.prepare(findTByObserveTimeSql);
    query.addBindValue(QVariant(observeTime));
    query.exec();
    if(query.next()) {
        temp = query.value(0).toInt();
    }
    return temp;
}

int ZDataDAOMysqlImp::getRecordsCount(const TimeRange &tr){
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
            //this point neeed report
        }
    }
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

bool ZDataDAOMysqlImp::saveZData(const ZData &zData){
    bool flag = false;
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            qDebug() << conn->lastError().databaseText();
            //this point neeed report
            return flag;
        }
    }
    query.prepare(insertSql);
    int qmIndex = -1;
    query.bindValue(++qmIndex, QVariant(zData.getObserveTime()));
    query.bindValue(++qmIndex, QVariant(zData.getObserveMonth()));
    query.bindValue(++qmIndex, QVariant(QDateTime::currentDateTime()));
    query.bindValue(++qmIndex, QVariant(QDateTime::currentDateTime()));
//    auto it = DataFormatUtil::zFileItem->constBegin();
//    auto end = DataFormatUtil::zFileItem->constEnd();

//    while(it != end){
//        query.bindValue(++qmIndex,QVariant(zData.value(*it)));
//        ++it;
//    }
    QString itemName("");
    for(int i = 0;i < 128;i++){
        itemName = DataFormatUtil::zFileItem[i];
        query.bindValue(++qmIndex,QVariant(zData.value(itemName)));
    }
    bool success =  query.exec();
    qDebug() << success
             <<" " << zData.getObserveTime().toString("yyyyMMdd-HHmm")
             << " " << query.lastError().databaseText();
    flag = true;
    return flag;
}

ZData ZDataDAOMysqlImp::findByOT(const QDateTime &observeTime){
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
            //this point neeed repor
        }
    }
    query.prepare(findOTDByOTSql);
    query.addBindValue(QVariant(observeTime));
    query.exec();
    ZData zData;
    if(query.next()) {
        int index = 0;
        zData.setObserveTime(query.value(++index).toDateTime());
        index += 2;
        int intDataNum = DataFormatUtil::zFileItem->length()+4;
        auto it = DataFormatUtil::zFileItem->constBegin();
        QString tempValue("");
        for(++index; index < intDataNum;++index) {
            tempValue = query.value(index).toString();
            zData.data.insert(*it,tempValue);
        }
        zData.totalInited = true;
        query.finish();
    }
    return zData;
}

bool ZDataDAOMysqlImp::exists(const QDateTime &observeTime){
    bool flag = false;
    QSqlQuery query(*conn);
    if(!conn->isOpen()){
        if(!conn->open()){
            conn->lastError().databaseText();
            //this point neeed report
            return flag;
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
