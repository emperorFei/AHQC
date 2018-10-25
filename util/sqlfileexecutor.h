#ifndef SQLFILEEXECUTOR_H
#define SQLFILEEXECUTOR_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include "dbcenter.h"

class SqlFileExecutor : public QObject
{
    Q_OBJECT
public:
    explicit SqlFileExecutor(QObject *parent = nullptr);
    void execute(QSqlDatabase *conn, const QString &sqlFileName);
    void execute(const QString &sqlFileName);
private:
    QList<QString> loadSql(const QString &sqlFileName);

signals:

public slots:
};

#endif // SQLFILEEXECUTOR_H
