#include "zdatadaomysqlimp.h"
QString ZDataDAOMysqlImp::insertSql = "";
QString ZDataDAOMysqlImp::findTByObserveTimeSql = "select tempis from ZData where ObserveTime = ?";
QString ZDataDAOMysqlImp::findOTDByOTSql = "select * from ZData where observeTime = ?";
QString ZDataDAOMysqlImp::getRecordsCountSql ="select count(*) from ZData where observeTime between ? and ?";

ZDataDAOMysqlImp::ZDataDAOMysqlImp(QSqlDatabase *conn):conn(conn)
{
    QString sBuilder("insert into ZData values(0,?,?,?");
    int intItems = DataFormatUtil::zFileItem->length();
    for(int i=0;i < intItems;i++){
        sBuilder.append(",?");
    }
    sBuilder.append(")");
    insertSql = sBuilder;
}

int ZDataDAOMysqlImp::findTempisByObserveTime(const QDateTime &observeTime){
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

int ZDataDAOMysqlImp::getRecordsCount(const TimeRange &tr){
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

bool ZDataDAOMysqlImp::saveZData(const ZData &zData){
    bool flag = false;
    QSqlQuery query(*conn);
    query.prepare(insertSql);
    int qmIndex = 0;
    query.bindValue(++qmIndex, QVariant(zData.getObserveTime()));
    auto it = DataFormatUtil::zFileItem->constBegin();
    auto end = DataFormatUtil::zFileItem->constEnd();
    while(it != end){
        query.bindValue(++qmIndex,QVariant(zData.value(*it)));
        ++it;
    }
    query.exec();
    conn->commit();
    query.finish();
    flag = true;
    return flag;
}

ZData ZDataDAOMysqlImp::findByOT(const QDateTime &observeTime){
    QSqlQuery query(*conn);
    query.prepare(findOTDByOTSql);
    query.addBindValue(QVariant(observeTime));
    query.exec();
    ZData zData;
    if(query.next()) {
        int index = 0;
        zData.setObserveTime(query.value(++index).toDateTime());
        zData.setInsertTime(query.value(++index).toDateTime());
        zData.setUpdateTime(query.value(++index).toDateTime());
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
