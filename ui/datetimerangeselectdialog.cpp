#include "datetimerangeselectdialog.h"

DateTimeRangeSelectDialog::DateTimeRangeSelectDialog(QWidget *parent) : QDialog(parent)
{
    marginLeft = 10;
    marginTop = 10;
    marginRight = 10;
    marginBottom = 20;
    this -> setMinimumSize(540,300);
    this -> setMaximumSize(540,300);
    dateTimeRangeString = "2018-10-01 00　～　2018-10-01 23";
    QHBoxLayout *layout_top = new QHBoxLayout;
//    this->setObjectName("this");
    this->setLayout(layout_top);

    QWidget *bgWidget = new QWidget(this);
    bgWidget->setObjectName("bgWidget");
    layout_top -> addWidget(bgWidget);

    QHBoxLayout *layout_bg = new QHBoxLayout;
    bgWidget->setLayout(layout_bg);

    QGraphicsDropShadowEffect *shadowOfDateTimeWidget = new QGraphicsDropShadowEffect(this);
    shadowOfDateTimeWidget -> setOffset(0, 0);
    shadowOfDateTimeWidget -> setColor(QColor("#888888"));
    shadowOfDateTimeWidget -> setBlurRadius(20);
    this -> setAttribute(Qt::WA_TranslucentBackground, true);
    this -> setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );
    layout_top->setContentsMargins(marginLeft,marginTop,marginRight,marginBottom);
    bgWidget -> setGraphicsEffect(shadowOfDateTimeWidget);
    layout_bg -> setContentsMargins(0,0,0,0);
    layout_bg -> setSpacing(0);

    startTimeWidget = new CalendarWidget(QDateTime::fromString("20181001 00","yyyyMMdd HH"),this);
    endTimeWidget = new CalendarWidget(QDateTime::fromString("20181001 23","yyyyMMdd HH"),this);
    startTimeWidget->setObjectName("startTimeWidget");
    endTimeWidget->setObjectName("endTimeWidget");
    startTimeWidget->connectToAnother(endTimeWidget);

    layout_bg->addWidget(startTimeWidget);
    layout_bg->addWidget(endTimeWidget);

    connect(startTimeWidget,
            &CalendarWidget::selectDateTimeChanged,
            this,
            &DateTimeRangeSelectDialog::sltCalendarTimeChanged);
    connect(endTimeWidget,
            &CalendarWidget::selectDateTimeChanged,
            this,
            &DateTimeRangeSelectDialog::sltCalendarTimeChanged);
    initStyleSheet();
}



DateTimeRangeSelectDialog::~DateTimeRangeSelectDialog(){

}

void DateTimeRangeSelectDialog::sltCalendarTimeChanged(const QDateTime&){
    emit dateTimeRangeChanged(startTimeWidget->getDateTime(),endTimeWidget->getDateTime());
}

void DateTimeRangeSelectDialog::updateCalendars(const QString &dateTimeRangeString,const QString &splicter){
    if(this->dateTimeRangeString == dateTimeRangeString){
        return;
    }
    this->dateTimeRangeString = dateTimeRangeString;
    QList<QString> dateTimes = dateTimeRangeString.split(splicter);
    startTimeWidget->setDateTime(QDateTime::fromString(dateTimes[0].trimmed(),"yyyy-MM-dd HH"));
    endTimeWidget->setDateTime(QDateTime::fromString(dateTimes[1].trimmed(),"yyyy-MM-dd HH"));
}

void DateTimeRangeSelectDialog::initStyleSheet(){
    setStyleSheet(styleSheet()+QString(
                                        "#bgWidget{\n"
                                            "background-color:white;\n"
                                        "}"
                                        ".CalendarWidget{\n"
                                            "border-style:solid;\n"
                                            "border-width:1;\n"
                                            "border-color:lightgreen;\n"
                                        "}\n"
                                       ));
}

QString DateTimeRangeSelectDialog::getDateTimeRangeString() const
{
    return dateTimeRangeString;
}

void DateTimeRangeSelectDialog::setDateTimeRangeString(const QString &value)
{
    dateTimeRangeString = value;
}
