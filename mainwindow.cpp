#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test/testreadxmldata.h"
#include "test/simpletest.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TestReadXmlData tReadXml;
    SimpleTest SimpleTest;

    QTest::qExec(&tReadXml);
    QTest::qExec(&SimpleTest);

}

MainWindow::~MainWindow()
{
    delete ui;
}
