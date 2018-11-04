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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("10.126.148.92");
//    db.setPort(3306);
//    db.setDatabaseName("ontimedata");
//      //这里输入你的数据库名
//    db.setUserName("fei");
//    db.setPassword("tiger");   //这里输入你的密码
//    qDebug() << db.databaseName();
//    qDebug() << db.hostName();
//    qDebug() << db.userName();
//    qDebug() << db.password();
//    if (!db.open()) {
//        QMessageBox::critical(Q_NULLPTR, QObject::tr("无法打开数据库"),
//        "无法创建数据库连接！ ", QMessageBox::Cancel);

//    }else{
//        QSqlQuery query(db);
//        //query.exec("use tempdb");
//        query.prepare("select Pressure,tempis from AWSMinute "
//                   "where observeTime = ? ");

//        //query.addBindValue(QVariant(time));
//        query.addBindValue(QVariant(QDateTime::fromString("2018-10-24 13:00:00","yyyy-MM-dd HH:mm:ss")));
//        query.exec();
//        if(query.next()){
//            qDebug() << query.value(0).toInt() << " " << query.value(1).toInt();
//        }else{
//            qDebug() << query.lastError();
//        }

//        query.finish();
//        db.close();
//    }

    //QSettings *dataSetting = new QSettings(":/conf/dataSetting",QSettings::IniFormat);
//    QResource re("");

//    QFile file("configs/dataSetting.ini");
//    QFileInfo fInfo(":/conf/dataSetting");
//    QString fileName = file.fileName();
//    QString absfileName = fInfo.absoluteFilePath();
//    qDebug() << fileName;
//    qDebug() << absfileName;


//    if(file.exists()){
//        qDebug() << "file " << fileName << "exists";
//        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
//            QTextStream ts(&file);
//            QString temp("string before init");
//            if(!ts.atEnd()){
//                temp = ts.readLine();
//                qDebug() << "file " << fileName << " line1: " << temp << " endl.";
//            }else{
//                qDebug() << "file " << fileName << " empty.";
//            }
//        }else{
//            qDebug() << "file " << fileName << "open fault";
//        }
//    }else{
//        qDebug() << "file " << fileName << " not exists.";
//    }

    //QString value = dataSetting->value("stationNum", "58343").toString();

    //qDebug() << value ;
    //std::cout << value.toStdString().c_str() << std::endl;

//    MainWindow w;
//    w.show();
    SettingWidget settingWidget;
    settingWidget.show();

    //delete dataSetting;

    return a.exec();
}
