#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test/testreadxmldata.h"
#include "test/simpletest.h"
#include "test/qtfeaturetest.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    TestReadXmlData tReadXml;
//    SimpleTest simpleTest;
//   QtFeatureTest qtFeatureTest;
//    QTest::qExec(&qtFeatureTest);
//    QTest::qExec(&tReadXml);
//    QTest::qExec(&simpleTest);
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}
