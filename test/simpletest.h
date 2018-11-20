#ifndef SIMPLETEST_H
#define SIMPLETEST_H

#include <QList>
#include <QMap>
#include <QtTest/QtTest>
#include <QObject>
#include "util/simpleutil.h"
#include "focusScheme/shiftsscheme.h"
#include "focusScheme/dayboundscheme.h"
#include "QDebug"
#include "solvecncodeproblem.h"
#include "globalseeting.h"
#include "awsminutedata.h"
#include "util/sqlfileexecutor.h"

class SimpleTest : public QObject
{
    Q_OBJECT
public:
    explicit SimpleTest(QObject *parent = nullptr);
    ~SimpleTest();
signals:

public slots:

private slots:


    void testDateFromSOMFileName();
    void testDateFromSOMFileName_data();
    void testDate2SOMFileName();
    void testDate2SOMFileName_data();
    void testDateTime2AWSDay();
    void testDateTime2AWSDay_data();
    void testGetFocusedTimeRange();
    void testGetFocusedTimeRange_data();

    void testGetFocusedTimeRange_dayBound();
    void testGetFocusedTimeRange_dayBound_data();

    void testGetFocusedHours();
    void testGetFocusedHours_data();

    void testGetAMFileNamesFormFocusedHours();
    void testGetAMFileNamesFormFocusedHours_data();

    void testGlobalSettingInit();
    void testGlobalSettingInit_data();

    void testReadNull();
    void testReadNull_data();

    void testReadAMFile();
    void testReadAMFile_data();

    void testGetZFileNames();
    void testGetZFileNames_data();


//    void testExecuteSqlScript();
//    void testExecuteSqlScript_data();

};

#endif // SIMPLETEST_H
