#ifndef DBCENTER_H
#define DBCENTER_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include "globalseeting.h"

class DBCenter : public QObject
{
    Q_OBJECT
public:
    ~DBCenter();
    enum AccountType{ROOT,ADMIN,QUERY,QIU};
    static QSqlDatabase* getDBByAccountType(AccountType type);
    static QString cleanCreatedConns();
private:
    explicit DBCenter(QObject *parent = nullptr);
    static QList<QSqlDatabase *> createdDB;

signals:

public slots:
};

#endif // DBCENTER_H
