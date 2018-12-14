#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QSqlError>
#include <QVariant>
#include <QSettings>
#include <QFile>
#include <iostream>
#include <QFileInfo>
#include <QResource>
#include "settingdialog.h"
#include <QRegExp>
int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    singleton<GlobalSetting>::GetInstance();
    MainWindow w;
    w.show();

    return a.exec();
}
