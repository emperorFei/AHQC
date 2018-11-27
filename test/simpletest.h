#ifndef SIMPLETEST_H
#define SIMPLETEST_H

#include <QList>
#include <QMap>
#include <QtTest/QtTest>
#include <QObject>
#include <QSqlDatabase>
#include "util/simpleutil.h"
#include "focusScheme/shiftsscheme.h"
#include "focusScheme/dayboundscheme.h"
#include "QDebug"
#include "solvecncodeproblem.h"
#include "globalseeting.h"
#include "awsminutedata.h"
#include "zdata.h"
#include "ahdata.h"
#include "util/sqlfileexecutor.h"
#include "dbcenter.h"
#include "awsminutedaomysqlimp.h"
#include "zdatadaomysqlimp.h"

class SimpleTest : public QObject
{
    Q_OBJECT
public:
    explicit SimpleTest(QObject *parent = nullptr);
    ~SimpleTest();
signals:

public slots:

private slots:


    void testDate2AMFileName();
    void testDate2AMFileName_data();
    void testAMFileName2Date();
    void testAMFileName2Date_data();
    void testDateTime2ZFileName();
    void testDateTime2ZFileName_data();
    void testZFileName2DateTime();
    void testZFileName2DateTime_data();

    void testDateTime2AWSDay();
    void testDateTime2AWSDay_data();
    void testDateTime2AWSMonth();
    void testDateTime2AWSMonth_data();

    void testGetFocusedTimeRange();
    void testGetFocusedTimeRange_data();
    void testGetFocusedTimeRange_dayBound();
    void testGetFocusedTimeRange_dayBound_data();

    void testGetFocusedHours();
    void testGetFocusedHours_data();

    void testGetAMFileNamesFormFocusedHours();
    void testGetAMFileNamesFormFocusedHours_data();
    void testGetZFileNamesFormFocusedHours();
    void testGetZFileNamesFormFocusedHours_data();

    void testGlobalSettingInit();
    void testGlobalSettingInit_data();


    void testReadAMFile();
    void testReadAMFile_data();
    void testReadZFile();
    void testReadZFile_data();


    void testGetZFileNames();
    void testGetZFileNames_data();

    void testGetConnect();
    void testGetConnect_data();

    void testSaveAMFile();
    void testSaveAMFile_data();
    void testSaveZData();
    void testSaveZData_data();

    void testGetZData();
    void testGetZData_data();
    void testGetAHData();
    void testGetAHData_data();

//    void testSaveAWSMinuteData();
//    void testSaveAWSMinuteData_data();


//    void testExecuteSqlScript();
//    void testExecuteSqlScript_data();

};

#endif // SIMPLETEST_H
