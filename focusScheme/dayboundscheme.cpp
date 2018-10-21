#include "dayboundscheme.h"

DayBoundScheme::DayBoundScheme(){}
DayBoundScheme::~DayBoundScheme(){}

TimeRange DayBoundScheme::getFocusRange() {
    QDateTime now = QDateTime::currentDateTime();
    QDateTime beginTimePoint = now;
    QTime dayBound = QTime::fromString("2000","HHmm");
    QTime zero = QTime::fromString("000000","HHmmss");
    int secondsFromZero = -now.time().secsTo(zero);
    int secondsOfDayBound = -dayBound.secsTo(zero);
    beginTimePoint = now.addSecs(secondsOfDayBound-secondsFromZero);

    if(now.time() < dayBound){
        beginTimePoint = beginTimePoint.addDays(-1);
    }

    TimeRange focusedTimeRange = TimeRange(beginTimePoint,now,timeRange_bound::BEND);
    return focusedTimeRange;
}
