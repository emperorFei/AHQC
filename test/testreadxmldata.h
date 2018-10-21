#ifndef TESTREADXMLDATA_H
#define TESTREADXMLDATA_H

#include <QtTest/QtTest>
#include <QObject>
#include "xmlProcessor/myxmlprocessor.h"

class TestReadXmlData : public QObject
{
    Q_OBJECT
public:
    explicit TestReadXmlData(QObject *parent = nullptr);
    ~TestReadXmlData();

signals:

public slots:

private slots:
    void testReadFine();
    void testReadFine_data();
    void testWriteFine();
    void testWriteFine_data();
};

#endif // TESTREADXMLDATA_H
