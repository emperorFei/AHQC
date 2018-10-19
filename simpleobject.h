#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H
#include "QString"
#include "QDateTime"
#include "QDate"
#include "QTime"
enum timeRange_bound {BE, BEND,BEGINE, BEGINEND,POINT};
enum focus_scheme {AFTERSHIFTS, AFTERDAYBOUND, AFTERPREVOIUSOBTIME, INAPPOINTEDTIMERANGE};
struct ColsInfo{
    QString dataName;
    int beginIndex;
    int endIndex;
    ColsInfo(QString name,int bIndex,int eIndex):dataName(name),beginIndex(bIndex),endIndex(eIndex){}
};
struct  TimeRange
{
    QDateTime older;
    QDateTime later;
    timeRange_bound bound;
    explicit TimeRange(QDateTime& t1,QDateTime& t2,timeRange_bound tr_bound) {
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
    QString toQString(){
        return older.toString("yyyyMMddHHmmss")+" "+later.toString("yyyyMMddHHmmss");
    }
};
#endif // SIMPLEOBJECT_H
