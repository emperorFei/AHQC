#include "zdatadaomysqlimp.h"
QString ZDataDAOMysqlImp::insertSql = "";
QString ZDataDAOMysqlImp::findTByObserveTimeSql = "select tempis from ZData where ObserveTime = ?";
QString ZDataDAOMysqlImp::findOTDByOTSql = "select * from ZData where observeTime = ?";
QString ZDataDAOMysqlImp::getRecordsCountSql ="select count(*) from ZData where observeTime between ? and ?";
ZDataDAOMysqlImp::ZDataDAOMysqlImp(QSqlDatabase *conn):conn(conn)
{
    this -> conn = conn;
    QString sBuilder("insert into ZData values(0,?,?,?");
    int intItems = DataFormatUtil::zFileItem->length();
    for(int i=0;i < intItems;i++){
        sBuilder.append(",?");
    }
    sBuilder.append(")");
    insertSql = sBuilder;
}

int ZDataDAOMysqlImp::findTempisByObserveTime(const QDateTime &observeTime){

}
int ZDataDAOMysqlImp::getRecordsCount(const TimeRange &tr){

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
        QString tempValue("");
        for(++index; index < intDataNum;++index) {
            tempValue = query.value(index).toString();
            //zData.data.insert(,tempValue);
        }

        zData.totalInited = true;
        query.finish();
    }
    return zData;
}
