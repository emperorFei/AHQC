#ifndef DATE_H
#define DATE_H

#include <QObject>
#include <QDate>
#include <QDateTime>
#define LC_STR QString::fromLocal8Bit
class DateTimeUtil : public QObject
{
    Q_OBJECT
public:
    explicit DateTimeUtil(QObject *parent = nullptr);

    static int getFirstDayOfWeek(int year, int month);
    static int getTotalMonthDays(int year, int month);
    static int getMonthDays(int year, int month);
    static bool isLoopYaer(int year);
    inline static QDate fromInt2Date(int year,int month,int day);

signals:

public slots:
};

#endif // DATE_H
