#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyledItemDelegate>
#include <QDateTime>
#include <QIcon>
#include "daylabel.h"
#include "hourlabel.h"
#include "clickablelabel.h"

#include "date.h"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    typedef enum{
        USEAS_SINGLE,USEAS_BEGINE,USEAS_END
    }USE_TYPE;
public:
    //explicit CalendarWidget(QWidget *parent = nullptr);
    explicit CalendarWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~CalendarWidget();



    void jumpToDateTime(const QDateTime& dt);
    void setDateTimeRange(const QDateTime &min, const QDateTime &max);
    void dateTimeRange(QDateTime &min, QDateTime &max);
    void connectToAnother(CalendarWidget *);

    int year() const;
    void setYear(int year);
    int month() const;
    void setMonth(int month);
    int day() const;
    void setDay(int day);
    int hour() const;
    void setHour(int h);
    USE_TYPE getUsedType() const;
    void setUsedType(const USE_TYPE &value);
    QDateTime getDateTime() const;


signals:
//    void dayClicked(const QDateTime&);
    void selectDateTimeChanged(const QDateTime&,const QDateTime&);
private:

    QWidget *widgetTitle;
    QWidget *widgetTitleCenter;
    QWidget *widgetShowDate;
    QWidget *widgetYear;
    QWidget *widgetMonth;
    QWidget *widgetDate;
    QWidget *widgetWeek;
    QWidget *widgetDateBody;
    QWidget *widgetHour;

    QVBoxLayout *verLayoutCalendar;
    QHBoxLayout *horLayoutTiTle;
    QHBoxLayout *horLayoutTiTleCenter;
    QHBoxLayout *horLayoutShowDate;
    QGridLayout *gridLayoutYear;
    QGridLayout *gridLayoutMonth;
    QVBoxLayout *verLayoutDate;
    QHBoxLayout *horLayoutWeek;
    QGridLayout *gridLayoutDateBody;
    QGridLayout *gridLayoutHour;

    ClickableLabel *labelYear[10];
    ClickableLabel *labelMonth[12];
    QLabel *labelWeek[7];
    DayLabel *labelDay[42];
    HourLabel *labelHour[36];

    ClickableLabel *labelShowYear;
    ClickableLabel *labelShowMonth;
    ClickableLabel *labelShowDay;
    QPushButton *nextYearBtn;
    QPushButton *nextMonthBtn;
    QPushButton *nextDayBtn;
    QPushButton *previousYearBtn;
    QPushButton *previousMonthBtn;
    QPushButton *previousDayBtn;
    QWidget *currentWidgetShowed = Q_NULLPTR;
private:
    void initWidget();
    void initTitleWidget();
    void initTitleCenterWidget();
    void initMonthWidget();
    void initYearWidget();
    void initDateWidget();
    void initHourWidget();
    void initICons();
    void initStyleSheet();
    void updateWidgets();
    void updateTitle();
    void updateTitleCenter();
    void updateYearWidget();
    void updateMonthWidget();
    void updateDateWidget();
    void updateHourWidget();
    DayLabel* getDayLabel(int y, int m, int d);
    QLabel* getHourLabel(int y, int m, int d, int hour);
    void changeCurrentSelectDay();

private:
    int m_nYear = 2018;
    int m_nMonth = 11;
    int m_nDay = 17;
    int m_nHour = 00;

    USE_TYPE usedType = USE_TYPE::USEAS_SINGLE;

    QDateTime m_maxDt;
    QDateTime m_minDt;
    DayLabel* m_pCrtSelect;
    QDateTime selectedDateTime = QDateTime(QDate(2018,11,17),QTime(00,00));
    QDateTime pairedDateTime = QDateTime(QDate(2018,11,20),QTime(15,00));

    static const QString s_strWeek[];
    static const QString s_strMonth[];

//    QIcon previousYear_normal_ico;
//    QIcon previousYear_hover_ico;
//    QIcon previousMonth_normal_ico;
//    QIcon previousMonth_hover_ico;
//    QIcon previousDay_normal_ico;
//    QIcon previousDay_hover_ico;
//    QIcon nextYear_normal_ico;
//    QIcon nextYear_hover_ico;
//    QIcon nextMonth_normal_ico;
//    QIcon nextMonth_hover_ico;
//    QIcon nextDay_normal_ico;
//    QIcon nextDay_hover_ico;
protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void setDateTime(const QDateTime &value);

    void sltPairedDateTimeChanged(const QDateTime &,const QDateTime &);
    void sltSelfDateTimeChanged(const QDateTime &,const QDateTime &);


    void sltLabelShowYearClicked(ClickableLabel *);
    void sltLabelShowMonthClicked(ClickableLabel *);
    void sltLabelShowDayClicked(ClickableLabel *);
    void sltYearLabelClicked(ClickableLabel *);
    void sltMonthLabelClicked(ClickableLabel *);
    void sltDayLabelClicked(QDate,int);
    void sltHourLabelClicked(QDateTime,HourLabel::E_HOUR);
    void sltPreviousYearBtnClicked(bool);
    void sltPreviousMonthBtnClicked(bool);
    void sltPreviousDayBtnClicked(bool);
    void sltNextYearBtnClicked(bool);
    void sltNextMonthBtnClicked(bool);
    void sltNextDayBtnClicked(bool);


    void sltMonthLabelRightClicked(bool);
    void sltDayLabelRightClicked(bool);
    void sltHourLabelRightClicked(bool);
};

#endif // CALENDARWIDGET_H
