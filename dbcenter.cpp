#include "dbcenter.h"

QList<QSqlDatabase *> DBCenter::createdDB;

DBCenter::DBCenter(QObject *parent) : QObject(parent){}
DBCenter::~DBCenter(){}
QSqlDatabase* DBCenter::getDBByAccountType(AccountType type){
    QSqlDatabase *dbPointer = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    GlobalSetting  *globalSetting = GlobalSetting::getInstance();
    dbPointer -> setHostName(globalSetting -> value("dbHost").toString());
    dbPointer -> setPort(globalSetting -> value("dbPort").toInt());
    dbPointer -> setDatabaseName(globalSetting -> value("dbName").toString());
    switch(type){
    case AccountType::QUERY:
        dbPointer -> setUserName("fei");
        dbPointer -> setPassword("tiger");
        break;
    case AccountType::QIU:
        dbPointer -> setUserName("fei");
        dbPointer -> setPassword("tiger");
        break;
    case AccountType::ADMIN:
        dbPointer -> setUserName("root");
        dbPointer -> setPassword("tiger");
        break;
    case AccountType::ROOT:
        dbPointer -> setUserName("root");
        dbPointer -> setPassword("tiger");
        break;
    case AccountType::SETTING:
        dbPointer -> setUserName(globalSetting -> value("dbAccount").toString());
        dbPointer -> setPassword(globalSetting -> value("dbPassword").toString());
        break;
    }
    createdDB.append(dbPointer);
    return  dbPointer;
}
QString DBCenter::cleanCreatedConns(){
    QString cleanInfo("clean fine");
    for(QSqlDatabase * conn : createdDB){
        if( conn != Q_NULLPTR && conn->isOpen()){
            conn -> close();
        }
    }
    qDeleteAll(createdDB);
    createdDB.clear();
    return cleanInfo;
}
//QSqlDatabase* DBCenter::getDBByQueryAccount(){
//    QSqlDatabase *queryDB = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
//    GlobalSetting  *globalSetting = GlobalSetting::getInstance();
//    queryDB->setHostName(globalSetting->getDBHostName());
//    queryDB->setPort(globalSetting->getDBPort());
//    queryDB->setDatabaseName(globalSetting->getDatabaseName());
//    queryDB->setUserName("fei");
//    queryDB->setPassword("tiger");
//    createdDB.append(queryDB);
//    return  queryDB;
//}
