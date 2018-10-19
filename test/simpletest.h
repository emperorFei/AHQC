#ifndef SIMPLETEST_H
#define SIMPLETEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "util/simpleutil.h"
#include "focusScheme/shiftsscheme.h"
#include "focusScheme/dayboundscheme.h"
#include "QDebug"

class SimpleTest : public QObject
{
    Q_OBJECT
public:
    explicit SimpleTest(QObject *parent = nullptr);
    ~SimpleTest();
signals:

public slots:

private slots:
    void testTransformDateFromSOMFileName();
    void testTransformDateFromSOMFileName_data();
    void testTransformDate2SOMFileName();
    void testTransformDate2SOMFileName_data();
    void testTranslateDateTime2AWSDay();
    void testTranslateDateTime2AWSDay_data();
    void testGetFocusedTimeRange();
    void testGetFocusedTimeRange_data();

    void testGetFocusedTimeRange_dayBound();
    void testGetFocusedTimeRange_dayBound_data();

    void testGetFocusedHours();
    void testGetFocusedHours_data();
};

#endif // SIMPLETEST_H
