#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test/testreadxmldata.h"
#include "test/simpletest.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    TestReadXmlData tReadXml;
    SimpleTest SimpleTest;

    QTest::qExec(&tReadXml);
    QTest::qExec(&SimpleTest);
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}
