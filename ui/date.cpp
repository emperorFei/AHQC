#include "date.h"

DateTimeUtil::DateTimeUtil(QObject *parent) : QObject(parent)
{

}
int DateTimeUtil::getFirstDayOfWeek(int year, int month)
{
    int week = 0;
    // 获取当年1月1日是星期几
    week = (year + (year- 1) / 4 -(year - 1) / 100 + (year - 1) / 400) % 7;
    week += getTotalMonthDays(year, month);
    return week % 7;
}

int DateTimeUtil::getTotalMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays =   0;            break;
    case  2: nDays =  31;            break;
    case  3: nDays =  59 + nLoopDay; break;
    case  4: nDays =  90 + nLoopDay; break;
    case  5: nDays = 120 + nLoopDay; break;
    case  6: nDays = 151 + nLoopDay; break;
    case  7: nDays = 181 + nLoopDay; break;
    case  8: nDays = 212 + nLoopDay; break;
    case  9: nDays = 243 + nLoopDay; break;
    case 10: nDays = 273 + nLoopDay; break;
    case 11: nDays = 304 + nLoopDay; break;
    case 12: nDays = 334 + nLoopDay; break;
    default: nDays = 0; break;
    }
    return nDays;
}

int DateTimeUtil::getMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays = 31;            break;
    case  2: nDays = 28 + nLoopDay; break;
    case  3: nDays = 31;            break;
    case  4: nDays = 30;            break;
    case  5: nDays = 31;            break;
    case  6: nDays = 30;            break;
    case  7: nDays = 31;            break;
    case  8: nDays = 31;            break;
    case  9: nDays = 30;            break;
    case 10: nDays = 31;            break;
    case 11: nDays = 30;            break;
    case 12: nDays = 31;            break;
    default: nDays = 30;            break;
    }
    return nDays;
}
bool DateTimeUtil::isLoopYaer(int year)
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

QDate DateTimeUtil::fromInt2Date(int year,int month,int day){
   return QDate::fromString(
                     QString("%1").arg(year, 4, 10, QChar('0'))+
                     QString("%1").arg(month, 2, 10, QChar('0'))+
                     QString("%1").arg(day, 2, 10, QChar('0')),
                     "yyyyMMdd");
}
