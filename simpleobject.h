﻿#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H
#include "QString"
#include "QDateTime"
#include "QDate"
#include "QTime"
enum timeRange_bound {BE, BEND,BEGINE, BEGINEND,POINT};
enum focus_scheme {AFTERSHIFTS, AFTERDAYBOUND, AFTERPREVOIUSOBTIME, INAPPOINTEDTIMERANGE};

struct  TimeRange
{
    QDateTime older;
    QDateTime later;
    timeRange_bound bound;
    explicit TimeRange(){
        older = QDateTime(QDate(1970,01,01),QTime(00,00));
        later = QDateTime(QDate(1970,01,01),QTime(23,00));
        bound = timeRange_bound::BEGINEND;
    }
    explicit TimeRange(const QDateTime &t1,QDateTime t2,timeRange_bound tr_bound) {
        bound = tr_bound;
        if(t1 > t2){
            older = t2;
            later = t1;
        }else if(t1 < t2){
            older = t1;
            later = t2;
        }else {
            older = later = t1;
            bound = timeRange_bound::POINT;
        }
    }
    TimeRange(const TimeRange& other){
        this->older = other.older;
        this->later = other.later;
        this->bound = other.bound;
    }
    QString toQString(){
        return older.toString("yyyyMMddHHmmss")+" "+later.toString("yyyyMMddHHmmss");
    }
};
struct ColInfo {
    ColInfo(QString &dataName,int &beginIndex,int &endIndex,int &length,bool separator = false)
     :dataName(dataName),
      beginIndex(beginIndex),
      endIndex(endIndex),
      length(length),
      separator(separator){}

    QString getDataName() {
        return dataName;
    }

    int getEndIndex() {
        return endIndex;
    }

    int getBeginIndex() {
        return beginIndex;
    }

    int getLength() {
        return length;
    }

    bool isSeparator() {
        return separator;
    }

    QString toString() {
        return dataName+
                "<"+QString::number(beginIndex)
                +","+QString::number(endIndex)
                +","+QString::number(length)+">"
                + ((separator == true) ? "_S": "");
    }

    QString dataName;
    int beginIndex;
    int endIndex;
    int length;
    bool separator;
};
#endif // SIMPLEOBJECT_H
