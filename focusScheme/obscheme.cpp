#include "obscheme.h"

OBScheme::OBScheme(){}
OBScheme::~OBScheme(){}
TimeRange OBScheme::getFocusRange(){
    QDateTime now = QDateTime::currentDateTime();
    QDateTime beginTimePoint = now;
//    QTime dayBound = QTime::fromString("2000","HHmm");
//    QTime zero = QTime::fromString("000000","HHmmss");
//    int secondsFromZero = -now.time().secsTo(zero);
//    int secondsOfDayBound = -dayBound.secsTo(zero);
//    beginTimePoint = now.addSecs(secondsOfDayBound-secondsFromZero);

//    if(now.time() < dayBound){
//        beginTimePoint = beginTimePoint.addDays(-1);
//    }
//    QDateTime previousDayBound = AHQC::TimeUtil::getPreviousDayBound(now);

//    if(now < previousDayBound.addSecs(60*60)){
//        beginTimePoint = previousDayBound.addSecs(-6*60*60);
//    }else if(now < previousDayBound.addSecs((1+2*AHQC::TimeUtil::OBInterval)*60*60) ){
//        beginTimePoint = previousDayBound;
//    }else if(now < previousDayBound.addSecs((1+3*AHQC::TimeUtil::OBInterval)*60*60)){
//        beginTimePoint = previousDayBound.addSecs(2*AHQC::TimeUtil::OBInterval*60*60);
//    }


    //beginTimePoint.
    TimeRange focusedTimeRange = TimeRange(beginTimePoint,now,timeRange_bound::BEND);
    return focusedTimeRange;
}
