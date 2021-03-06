﻿#ifndef QTFEATURETEST_H
#define QTFEATURETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QList>
#include <QMap>
#include <QDebug>
#include <QDateTime>
#include <QRegExp>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QValidator>

class QtFeatureTest : public QObject
{
    Q_OBJECT
public:
    explicit QtFeatureTest(QObject *parent = nullptr);
    ~QtFeatureTest();

signals:

public slots:
private slots:
    void testQString2Int();
    void testQString2Int_data();    
    void testReadNull();
    void testReadNull_data();
    void testRegLookBehind();
    void testRegLookBehind_data();
    void testInsertCause();
    void testInsertCause_data();


};

#endif // QTFEATURETEST_H
