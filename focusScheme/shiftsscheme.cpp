#include "shiftsscheme.h"

ShiftsScheme::ShiftsScheme(QTime shiftsTime)
{
    this->shiftsTime = shiftsTime;
}
ShiftsScheme::~ShiftsScheme(){}

TimeRange ShiftsScheme::getFocusRange(){
    QDateTime now = QDateTime::currentDateTime();
    QDateTime beginTimePoint = now;

    QTime zero = QTime::fromString("000000","HHmmss");
    int secondsFromZero = -now.time().secsTo(zero);
    int secondsOfShiftsTime = -shiftsTime.secsTo(zero);
    beginTimePoint = now.addSecs(secondsOfShiftsTime-secondsFromZero);

    if(now.time() < shiftsTime){
        beginTimePoint =  beginTimePoint.addDays(-1);
    }

    TimeRange focusedTimeRange = TimeRange(beginTimePoint,now,timeRange_bound::BEND);
    return focusedTimeRange;
}
