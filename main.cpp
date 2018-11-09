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
#include "settingwidget.h"
#include <QRegExp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    singleton<GlobalSetting>::GetInstance();
    QString path1("D:\\CTS2\\TransferClient\\log\\SendDataAck");
    QString path2("D:\\CTS2\\Transfer Client\\log\\SendData Ack");
    QString path3("D:\\CTS2\\TransferClient\\log\\SendData Ack");

    QRegExp reg1("\\\\[^\\\\]+$");


    int tailIndex = reg1.indexIn(path2,0);
//    qDebug() << tailIndex;
//    path2 = path2.remove(tailIndex,path2.length()-tailIndex);
//    qDebug() << path2;

//    tailIndex = reg1.indexIn(path2,0);
//    qDebug() << tailIndex;
//    path2 = path2.remove(tailIndex,path2.length()-tailIndex);
//    qDebug() << path2;

//    tailIndex = reg1.indexIn(path2,0);
//    qDebug() << tailIndex;
//    path2 = path2.remove(tailIndex,path2.length()-tailIndex);
//    qDebug() << path2;

//    tailIndex = reg1.indexIn(path2,0);
//    qDebug() << tailIndex;
//    path2 = path2.remove(tailIndex,path2.length()-tailIndex);
//    qDebug() << path2;

    QRegExp reg2("-");
    QString oTimes("20-10;15-48-16");
    tailIndex = reg2.indexIn(oTimes,0);
    qDebug() << tailIndex;
    //oTimes = oTimes.replace(reg2,",");
    oTimes = oTimes.replace("-",",");
    qDebug() << oTimes;


//    MainWindow w;
//    w.show();
    SettingWidget settingWidget;
    settingWidget.show();

    return a.exec();
}
