#include "sqlfileexecutor.h"

SqlFileExecutor::SqlFileExecutor(QObject *parent) : QObject(parent)
{

}

QList<QString> SqlFileExecutor::loadSql(const QString &sqlFileName){
    QList<QString> sqlList;
    QString tempSqlString("--beforeInited;");
    QStringList  sqlStringList;
    QString line("before inited");
    QFile sqlFile(sqlFileName);
    if(sqlFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream amIn(&sqlFile);
        line = amIn.readAll();
        sqlFile.close();
    }
    line = line.trimmed().replace("\n","");
    sqlStringList = line.split(";");
    QList<QString>::iterator it = sqlStringList.begin();
    QList<QString>::iterator endIt = sqlStringList.end();
    while(it != endIt){
        tempSqlString = it->replace("--.*", "").trimmed();
        if(tempSqlString != ""){
            sqlList.append(tempSqlString);
        }
        ++it;
    }
    return sqlList;


//    // Windows 下换行是 /r/n, Linux 下是 /n
//    //String[] sqlArr = sqlSb.toString().split("(;//s*//r//n)|(;//s*//n)");


}
void SqlFileExecutor::execute(QSqlDatabase *conn, const QString &sqlFileName){
    if(conn->open()){
        QSqlQuery query(*conn);
        QList<QString> sqlList = loadSql(sqlFileName);
        for(QString &s : sqlList){
            query.exec(s);
        }
        query.finish();
        conn -> commit();
        conn -> close();
    }else{

    }
}
void SqlFileExecutor::execute(const QString &sqlFileName){
    this -> execute(DBCenter::getDBByAccountType(DBCenter::AccountType::ADMIN),sqlFileName);
}
