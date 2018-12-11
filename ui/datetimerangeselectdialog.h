#ifndef DATETIMERANGESELECTDIALOG_H
#define DATETIMERANGESELECTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include "calendarwidget.h"
class DateTimeRangeSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DateTimeRangeSelectDialog(QWidget *parent = nullptr);
    ~DateTimeRangeSelectDialog();
    void updateCalendars(const QString &dateTimeRangeString,const QString &splicter);
    QString getDateTimeRangeString() const;
    void setDateTimeRangeString(const QString &value);

signals:
    void dateTimeRangeChanged(QDateTime startTime,QDateTime endTime);
public slots:
    void sltCalendarTimeChanged(const QDateTime&);
private:
    void initStyleSheet();
private:
    QString dateTimeRangeString;
    CalendarWidget *startTimeWidget;
    CalendarWidget *endTimeWidget;
    int marginLeft;
    int marginRight;
    int marginTop;
    int marginBottom;
};

#endif // DATETIMERANGESELECTDIALOG_H
