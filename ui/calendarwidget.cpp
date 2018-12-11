#include "calendarwidget.h"

const QString CalendarWidget::s_strWeek[]{
       QString("日"), QString("一"), QString("二"),
       QString("三"), QString("四"), QString("五"),
       QString("六"),
};

const QString CalendarWidget::s_strMonth[]{
       QString("1月"), QString("2月"), QString("3月"),
       QString("4月"), QString("5月"), QString("6月"),
       QString("7月"), QString("8月"), QString("9月"),
       QString("10月"), QString("11月"), QString("12月")
};

CalendarWidget::CalendarWidget(QWidget *parent,Qt::WindowFlags f) : QWidget(parent,f)
{
    //initICons();
    initWidget();
    initStyleSheet();
    connect(this,&CalendarWidget::selectDateTimeChanged,this,&CalendarWidget::sltSelfDateTimeChanged);
}

CalendarWidget::CalendarWidget(const QDateTime dateTime,QWidget *parent,Qt::WindowFlags f) : CalendarWidget(parent,f)
{
    this->setDateTime(dateTime);
}

CalendarWidget::~CalendarWidget(){}

void CalendarWidget::connectToAnother(CalendarWidget *another){
    this->pairedDateTime = another->getDateTime();
    another->pairedDateTime = this->getDateTime();
    if(this->getDateTime() <= another->getDateTime()){
        this->setUsedType(USEAS_BEGINE);
        another->setUsedType(USEAS_END);
    }else{
        another->setUsedType(USEAS_BEGINE);
        this->setUsedType(USEAS_END);
    }
    connect(this,&CalendarWidget::selectDateTimeChanged,another,&CalendarWidget::sltPairedDateTimeChanged);
    connect(another,&CalendarWidget::selectDateTimeChanged,this,&CalendarWidget::sltPairedDateTimeChanged);
    updateWidgets();
    another->updateWidgets();
}


DayLabel *CalendarWidget::getDayLabel(int y, int m, int d)
{
    int nWeek  = DateTimeUtil::getFirstDayOfWeek(y, m);
    nWeek = (0 == nWeek ? 7 : nWeek);
    // 显示当前天数
    return labelDay[d + nWeek - 1];
}





void CalendarWidget::initWidget()
{
    //this->setMinimumSize(246, 235);
    this->setMinimumSize(266, 255);
    this->setObjectName("widgetCalendar");
    verLayoutCalendar = new QVBoxLayout(this);
    verLayoutCalendar->setContentsMargins(10, 10, 10, 10);
    verLayoutCalendar->setSpacing(5);
    initTitleWidget();
    initYearWidget();
    widgetYear->hide();
    initMonthWidget();
    widgetMonth->hide();
    initDateWidget();
    widgetDate->hide();
    initHourWidget();
    widgetHour->hide();

    updateWidgets();
//    updateTitle();
////    updateYearWidget();
////    updateMonthWidget();
    updateDateWidget();
    updateHourWidget();
    verLayoutCalendar->addWidget(widgetTitle);    
    verLayoutCalendar->addWidget(widgetHour);
    widgetHour->show();
    currentWidgetShowed = widgetHour;


}
void CalendarWidget::initStyleSheet()
{
    setStyleSheet(QString(
                      ".CalendarWidget{\n"
                            "background-color:white;\n"
                      "}\n"
                      "QPushButton{\n"
                            "background-color: transparent;\n"
                            "border: 0px;\n"
                      "}\n"
//                      "#widgetTitle{\n"
//                            "background-color: blue;\n"
//                            "border: 0px;\n"
//                      "}\n"
//                      "#widgetTitleCenter{\n"
//                            "background-color: green;\n"
//                            "border: 0px;\n"
//                      "}\n"
//                      "#widgetHour{\n"
//                            "background-color: orange;\n"
//                            "border: 0px;\n"
//                      "}\n"
                      "#widgetWeek{\n"
                   //         "background-color: pink;\n"
                            "border: 0px;\n"
                      "}\n"
//                      "#widgetDate{\n"
//                            "background-color: yellow;\n"
//                            "border: 0px;\n"
//                      "}\n"
                      "#widgetDateBody{\n"
                            "background-color: lightblue;\n"
                            "border: 0px;\n"
                      "}\n"
                      "#labelShowDay:hover,#labelShowMonth:hover,#labelShowYear:hover{\n"
                            "color: rgb(18,132,231);\n"
                      "}\n"
                      "#previousYearBtn{\n"
                           "image: url(:/ico/previousYear_normal);\n"
                      "}\n"
                      "#previousMonthBtn{\n"
                           "image: url(:/ico/previousMonth_normal);\n"
                      "}\n"
                      "#previousDayBtn{\n"
                           "image: url(:/ico/previousDay_normal);\n"
                      "}\n"
                      "#nextYearBtn{\n"
                           "image: url(:/ico/nextYear_normal);\n"
                      "}\n"
                      "#nextMonthBtn{\n"
                           "image: url(:/ico/nextMonth_normal);\n"
                      "}\n"
                      "#nextDayBtn{\n"
                           "image: url(:/ico/nextDay_normal);\n"
                      "}\n"

                      "#previousYearBtn:hover{\n"
                           "image: url(:/ico/previousYear_hover);\n"
                      "}\n"
                      "#previousMonthBtn:hover{\n"
                           "image: url(:/ico/previousMonth_hover);\n"
                      "}\n"
                      "#previousDayBtn:hover{\n"
                           "image: url(:/ico/previousDay_hover);\n"
                      "}\n"
                      "#nextYearBtn:hover{\n"
                           "image: url(:/ico/nextYear_hover);\n"
                      "}\n"
                      "#nextMonthBtn:hover{\n"
                           "image: url(:/ico/nextMonth_hover);\n"
                      "}\n"
                      "#nextDayBtn:hover{\n"
                           "image: url(:/ico/nextDay_hover);\n"
                      "}\n"





//                      "#widgetMonth .ClickableLabel[selected = true]{\n"
//                           "background-color: rgb(18,132,231);\n"
//                           "color: white;\n"
//                      "}\n"
//                      "#widgetYear .ClickableLabel[selected = true]{\n"
//                           "background-color: rgb(18,132,231);\n"
//                           "color: white;\n"
//                      "}\n"

//                      "#widgetMonth .ClickableLabel[selected = false]{\n"
//                           "background-color: transparent;\n"
//                           "color: black;\n"
//                      "}\n"
//                      "#widgetYear .ClickableLabel[selected = false]{\n"
//                           "background-color: transparent;\n"
//                           "color: black;\n"
//                      "}\n"
                      "#widgetMonth .ClickableLabel:hover{\n"
                           "background-color: rgb(220,248,255);\n"
                           "color: black;\n"
                      "}\n"
                      "#widgetYear .ClickableLabel:hover{\n"
                           "background-color: rgb(220,248,255);\n"
                           "color: black;\n"
                      "}\n"
//                      "#widgetYear .ClickableLabel:hover [selected = 'selected']{\n"
//                           "background-color: rgb(18,132,231);\n"
//                           "color: black;\n"
//                      "}\n"
                      )
                  );
}

void CalendarWidget::updateWidgets(){
    updateTitle();
    updateYearWidget();
    updateMonthWidget();
    updateDateWidget();
    updateHourWidget();
}

void CalendarWidget::updateTitle(){
    updateTitleCenter();
    if(currentWidgetShowed == widgetYear || currentWidgetShowed == widgetMonth){
        previousMonthBtn->hide();
        previousDayBtn->hide();
        nextMonthBtn->hide();
        nextDayBtn->hide();
        labelShowDay->hide();
    }else if(currentWidgetShowed == widgetDate){
        previousMonthBtn->show();
        previousDayBtn->hide();
        nextMonthBtn->show();
        nextDayBtn->hide();
        labelShowDay->hide();
    }else if(currentWidgetShowed == widgetHour){
        previousMonthBtn->show();
        previousDayBtn->show();
        nextMonthBtn->show();
        nextDayBtn->show();
        labelShowDay->show();
    }
}

void CalendarWidget::updateTitleCenter(){
    labelShowYear->setText(QString::number(m_nYear)+"年");
    labelShowMonth->setText(QString::number(m_nMonth)+"月");
    labelShowDay->setText(QString::number(m_nDay)+"日");
}

void CalendarWidget::updateYearWidget(){
    for(int i=0;i<10;++i){
       int yearOfThelabel = labelYear[i]->text().toInt();
       if(yearOfThelabel == m_nYear){
           labelYear[i]->setStyleSheet("background-color: rgb(18,132,231);\n color:white");
       }else{
           labelYear[i]->setStyleSheet("");
           labelYear[i]->update();
       }
    }
}

void CalendarWidget::updateMonthWidget(){
    for(int i=0;i<12;++i){
       labelMonth[i]->setStyleSheet("");
       labelMonth[i]->update();
    }
    labelMonth[m_nMonth-1]->setStyleSheet("background-color: rgb(18,132,231);\n color:white");
    labelMonth[m_nMonth-1]->update();
    widgetMonth->update();
}

void CalendarWidget::updateDateWidget(){
    int nWeek  = DateTimeUtil::getFirstDayOfWeek(m_nYear, m_nMonth);
    int nMonthDays = DateTimeUtil::getMonthDays(m_nYear, m_nMonth);
    int nPreMonDays = DateTimeUtil::getMonthDays(1 == m_nMonth ?
                                             m_nYear - 1 :
                                             m_nYear,
                                         1 == m_nMonth ?
                                             12 :
                                             m_nMonth - 1);

    int year4Label = m_nYear;
    int month4Label = m_nMonth;
    int day4label = m_nDay;
    // 显示上、下月天数
    if (0 == nWeek) {
        year4Label = (1 == m_nMonth ? m_nYear - 1 : m_nYear);
        month4Label = (1 == m_nMonth ? 12 : m_nMonth - 1);
        for (int i = 0; i < 7; i++) {
            day4label = nPreMonDays - 7 + i + 1;
            labelDay[i]->showDay(day4label);
            labelDay[i]->setType(DayLabel::E_DAY::PREV_MONTH_DAY);
            labelDay[i]->setDate(QDate(year4Label,month4Label,day4label));
            labelDay[i]->setText(QString("%1").arg(day4label, 2, 10, QChar('0')));
        }
        year4Label = (12 == m_nMonth ? m_nYear + 1 : m_nYear);
        month4Label = (12 == m_nMonth ? 1 : m_nMonth + 1);
        for (int i = 0; i < (42 - nMonthDays - 7); i++) {
            day4label = i + 1;
            labelDay[nMonthDays + 7 + i]->showDay(day4label);
            labelDay[nMonthDays + 7 + i]->setType(DayLabel::E_DAY::NEXT_MONTH_DAY);
            labelDay[i]->setDate(QDate(year4Label,month4Label,day4label));
            labelDay[i]->setText(QString("%1").arg(day4label, 2, 10, QChar('0')));
        }
    } else {
        year4Label = (1 == m_nMonth ? m_nYear - 1 : m_nYear);
        month4Label = (1 == m_nMonth ? 12 : m_nMonth - 1);
        for (int i = 0; i < nWeek; i++) {
            day4label = nPreMonDays - nWeek + i + 1;
            labelDay[i]->showDay(day4label);
            labelDay[i]->setType(DayLabel::E_DAY::PREV_MONTH_DAY);
            labelDay[i]->setDate(QDate(year4Label,month4Label,day4label));
            labelDay[i]->setText(QString("%1").arg(day4label, 2, 10, QChar('0')));
        }
        year4Label = (12 == m_nMonth ? m_nYear + 1 : m_nYear);
        month4Label = (12 == m_nMonth ? 1 : m_nMonth + 1);
        for (int i = (nWeek + nMonthDays); i < 42; i++) {
            day4label = i - (nWeek + nMonthDays) + 1;
            labelDay[i]->showDay(day4label);
            labelDay[i]->setType(DayLabel::E_DAY::NEXT_MONTH_DAY);
            labelDay[i]->setDate(QDate(year4Label,month4Label,day4label));
            labelDay[i]->setText(QString("%1").arg(day4label, 2, 10, QChar('0')));
        }
    }
    year4Label = m_nYear;
    month4Label = m_nMonth;
    day4label = m_nDay;
    // 显示选择月
    int index = 0;
    for (int i = nWeek; i < (nMonthDays + nWeek); i++) {
        index = (0 == nWeek ? (i + 7) : i);
        day4label = i - nWeek + 1;
        labelDay[index]->showDay(day4label);
        labelDay[index]->setType(DayLabel::E_DAY::CURR_MONTH_DAY);
        labelDay[i]->setDate(QDate(year4Label,month4Label,day4label));
        labelDay[i]->setText(QString("%1").arg(day4label, 2, 10, QChar('0')));
    }

    for(int i = 0 ;i < 42 ; ++i){
        QDateTime lastHourOfTheDay = QDateTime(labelDay[i]->getDate(),QTime::fromString("23","HH"));
        QDateTime firstHourOfTheDay = QDateTime(labelDay[i]->getDate(),QTime::fromString("00","HH"));
        labelDay[i]->setSelected(false);
        if(USE_TYPE::USEAS_BEGINE == usedType){
            if(firstHourOfTheDay > pairedDateTime){
               labelDay[i]->setInErrorRange(true);
               labelDay[i]->setInRange(false);

            }else if(lastHourOfTheDay >= selectedDateTime){
               labelDay[i]->setInErrorRange(false);
               labelDay[i]->setInRange(true);
            }else{
               labelDay[i]->setInErrorRange(false);
               labelDay[i]->setInRange(false);
            }
        }else if(USE_TYPE::USEAS_END == usedType){
            if(lastHourOfTheDay < pairedDateTime){
               labelDay[i]->setInErrorRange(true);
               labelDay[i]->setInRange(false);
            }else if(firstHourOfTheDay <= selectedDateTime){
               labelDay[i]->setInErrorRange(false);
               labelDay[i]->setInRange(true);
            }else{
               labelDay[i]->setInErrorRange(false);
               labelDay[i]->setInRange(false);
            }
        }else{
            labelDay[i]->setInErrorRange(false);
            labelDay[i]->setInRange(false);
            if(firstHourOfTheDay <= selectedDateTime &&
                    selectedDateTime <= lastHourOfTheDay){
               labelDay[i]->setSelected(true);
            }else{
               labelDay[i]->setSelected(false);
            }
        }
    }


}

void CalendarWidget::updateHourWidget(){
    QDateTime previousDayFirstHour = QDateTime(QDate(m_nYear,m_nMonth,m_nDay),QTime(00,00)).addDays(-1);
    QDateTime dateTimeOfLabel = previousDayFirstHour.addSecs(20*60*60);
    if(USE_TYPE::USEAS_BEGINE == usedType){
        for(int i=0;i < 35;++i){
            dateTimeOfLabel = dateTimeOfLabel.addSecs(60*60);
            labelHour[i]->setDateTime(dateTimeOfLabel);
            labelHour[i]->setText(dateTimeOfLabel.toString("HH"));
            if(dateTimeOfLabel > pairedDateTime){
                labelHour[i]->setInErrorRange(true);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(false);
            }else if(dateTimeOfLabel > selectedDateTime){
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(true);
                labelHour[i]->setSelected(false);
            }else if(dateTimeOfLabel == selectedDateTime){
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(true);
            }else{
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(false);
            }
        }
    }else if(USE_TYPE::USEAS_END == usedType){
        for(int i=0;i < 35;++i){
            dateTimeOfLabel = dateTimeOfLabel.addSecs(60*60);
            labelHour[i]->setDateTime(dateTimeOfLabel);
            labelHour[i]->setText(dateTimeOfLabel.toString("HH"));
            if(dateTimeOfLabel < pairedDateTime){
                labelHour[i]->setInErrorRange(true);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(false);
            }else if(dateTimeOfLabel < selectedDateTime){
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(true);
                labelHour[i]->setSelected(false);
            }else if(dateTimeOfLabel == selectedDateTime){
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(true);
            }else{
                labelHour[i]->setInErrorRange(false);
                labelHour[i]->setInRange(false);
                labelHour[i]->setSelected(false);
            }
        }
    }else{
        for(int i=0;i < 35;++i){
            labelHour[i]->setInRange(false);
            labelHour[i]->setInErrorRange(false);
            dateTimeOfLabel = dateTimeOfLabel.addSecs(60*60);
            labelHour[i]->setText(dateTimeOfLabel.toString("HH"));
            if(dateTimeOfLabel == selectedDateTime){
                labelHour[i]->setSelected(true);
            }else{
                labelHour[i]->setSelected(false);
            }
        }
    }

}

void CalendarWidget::sltSelfDateTimeChanged(const QDateTime &value, const QDateTime &){
    m_nYear = value.toString("yyyy").toInt();
    m_nMonth = value.toString("MM").toInt();
    m_nDay = value.toString("dd").toInt();
    currentWidgetShowed->hide();
    verLayoutCalendar->removeWidget(currentWidgetShowed);
    widgetHour->show();
    verLayoutCalendar->insertWidget(1,widgetHour);
    currentWidgetShowed = widgetHour;
    updateWidgets();
}
void CalendarWidget::sltPairedDateTimeChanged(const QDateTime &value, const QDateTime &){
    pairedDateTime = value;
    updateWidgets();
}


void CalendarWidget::sltLabelShowYearClicked(ClickableLabel *){
    if(currentWidgetShowed == widgetYear){
        currentWidgetShowed = widgetMonth;
        updateWidgets();
        widgetYear->hide();
        verLayoutCalendar->removeWidget(widgetYear);
        verLayoutCalendar->insertWidget(1,widgetMonth);
        widgetMonth->show();
    }else{
        int yearIndex0 = m_nYear - (m_nYear %10);
        for(int i=0;i<10;i++){
            labelYear[i]->setText(QString::number(yearIndex0++));
        }
        currentWidgetShowed->hide();
        verLayoutCalendar->removeWidget(currentWidgetShowed);
        currentWidgetShowed = widgetYear;
        updateWidgets();
        verLayoutCalendar->insertWidget(1,widgetYear);
        widgetYear->show();
    }
}
void CalendarWidget::sltLabelShowMonthClicked(ClickableLabel *){

    if(currentWidgetShowed == widgetMonth){
        currentWidgetShowed = widgetDate;
        updateWidgets();
        widgetMonth->hide();
        verLayoutCalendar->removeWidget(widgetMonth);
        verLayoutCalendar->insertWidget(1,widgetDate);
        widgetDate->show();

    }else{
        currentWidgetShowed->hide();
        verLayoutCalendar->removeWidget(currentWidgetShowed);
        currentWidgetShowed = widgetMonth;
        updateWidgets();
        verLayoutCalendar->insertWidget(1,widgetMonth);
        widgetMonth->show();
    }
}
void CalendarWidget::sltLabelShowDayClicked(ClickableLabel *){
    if(currentWidgetShowed == widgetDate){
        currentWidgetShowed = widgetHour;
        updateWidgets();
        widgetDate->hide();
        verLayoutCalendar->removeWidget(widgetDate);
        verLayoutCalendar->insertWidget(1,widgetHour);
        widgetHour->show();

    }else{
        currentWidgetShowed->hide();
        verLayoutCalendar->removeWidget(currentWidgetShowed);
        currentWidgetShowed = widgetDate;
        updateWidgets();
        verLayoutCalendar->insertWidget(1,widgetDate);
        widgetDate->show();

    }
}
void CalendarWidget::sltYearLabelClicked(ClickableLabel *yearLabel){
    QString yearLabelStr = yearLabel->text();
    int year = atoi(yearLabelStr.toStdString().c_str());
    m_nYear = year;
    currentWidgetShowed = widgetMonth;
    updateWidgets();
    widgetYear->hide();
    verLayoutCalendar->removeWidget(widgetYear);
    verLayoutCalendar->insertWidget(1,widgetMonth);
    widgetMonth->show();    
}
void CalendarWidget::sltMonthLabelClicked(ClickableLabel * monthLabel){
    QString monthLabelStr = monthLabel->text();
    int month = atoi(monthLabelStr.replace("月","").toStdString().c_str());
    m_nMonth = month;
    currentWidgetShowed = widgetDate;
    updateWidgets();
    widgetMonth->hide();
    verLayoutCalendar->removeWidget(widgetMonth);
    verLayoutCalendar->insertWidget(1,widgetDate);
    widgetDate->show();
}
void CalendarWidget::sltDayLabelClicked(QDate date,int type){
    Q_UNUSED(type)
    m_nYear = atoi(date.toString("yyyy").toStdString().c_str());
    m_nMonth = atoi(date.toString("MM").toStdString().c_str());
    m_nDay = atoi(date.toString("dd").toStdString().c_str());
    currentWidgetShowed = widgetHour;
    updateWidgets();
    widgetDate->hide();
    verLayoutCalendar->removeWidget(widgetDate);
    widgetHour->show();
    verLayoutCalendar->insertWidget(1,widgetHour);
}
void CalendarWidget::sltHourLabelClicked(QDateTime dateTime, HourLabel::E_HOUR type){
    Q_UNUSED(type)

    m_nYear = dateTime.toString("yyyy").toInt();
    m_nMonth = dateTime.toString("MM").toInt();
    m_nDay = dateTime.toString("dd").toInt();
    m_nHour = dateTime.toString("HH").toInt();    
    currentWidgetShowed = widgetHour;
    setDateTime(dateTime);
//    updateWidgets();
}

void CalendarWidget::sltPreviousYearBtnClicked(bool){
    if(currentWidgetShowed == widgetYear){
        int yearIndex0 = labelYear[0]->text().toInt() - 10;
        for(int i=0;i<10;++i){
            labelYear[i]->setText(QString::number(yearIndex0++));
        }
    }else{
        m_nYear -= 1;
    }
    updateWidgets();
}
void CalendarWidget::sltPreviousMonthBtnClicked(bool){
    m_nYear = (1 == m_nMonth ? m_nYear -1 : m_nYear);
    m_nMonth = (1 == m_nMonth ? 12 : m_nMonth - 1);
    updateWidgets();
}
void CalendarWidget::sltPreviousDayBtnClicked(bool){
    QDate temp(m_nYear,m_nMonth,m_nDay);
    temp = temp.addDays(-1);
    m_nYear = temp.toString("yyyy").toInt();
    m_nMonth = temp.toString("MM").toInt();
    m_nDay = temp.toString("dd").toInt();
    updateWidgets();
}
void CalendarWidget::sltNextYearBtnClicked(bool){
    if(currentWidgetShowed == widgetYear){
        int yearIndex0 = labelYear[0]->text().toInt() + 10;
        for(int i=0;i<10;++i){
            labelYear[i]->setText(QString::number(yearIndex0++));
        }
    }else{
        m_nYear += 1;
    }
    updateWidgets();
}
void CalendarWidget::sltNextMonthBtnClicked(bool){
    m_nYear = (12 == m_nMonth ? m_nYear +1 : m_nYear);
    m_nMonth = (12 == m_nMonth ? 1 : m_nMonth + 1);
    updateWidgets();
}
void CalendarWidget::sltNextDayBtnClicked(bool){
    QDate temp(m_nYear,m_nMonth,m_nDay);
    temp = temp.addDays(1);
    m_nYear = temp.toString("yyyy").toInt();
    m_nMonth = temp.toString("MM").toInt();
    m_nDay = temp.toString("dd").toInt();
    updateWidgets();
}

void CalendarWidget::sltMonthLabelRightClicked(bool){
    currentWidgetShowed = widgetYear;
    widgetMonth->hide();
    verLayoutCalendar->removeWidget(widgetMonth);
    widgetYear->show();
    verLayoutCalendar->insertWidget(1,widgetYear);
    updateWidgets();
}
void CalendarWidget::sltDayLabelRightClicked(bool){
    currentWidgetShowed = widgetMonth;
    widgetDate->hide();
    verLayoutCalendar->removeWidget(widgetDate);
    widgetMonth->show();
    verLayoutCalendar->insertWidget(1,widgetMonth);
    updateWidgets();
}
void CalendarWidget::sltHourLabelRightClicked(bool){
    currentWidgetShowed = widgetDate;
    widgetHour->hide();
    verLayoutCalendar->removeWidget(widgetHour);
    widgetDate->show();
    verLayoutCalendar->insertWidget(1,widgetDate);
    updateWidgets();
}


void CalendarWidget::initTitleWidget(){
    //! [1] 标题行
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName("widgetTitle");
    widgetTitle->setMinimumHeight(26);
    widgetTitle->setMaximumHeight(26);
    horLayoutTiTle = new QHBoxLayout(widgetTitle);
    horLayoutTiTle -> setContentsMargins(0, 0, 0, 0);
    horLayoutTiTle -> setSpacing(0);
    previousYearBtn = new QPushButton(widgetTitle);
    previousYearBtn -> setObjectName("previousYearBtn");

    previousMonthBtn = new QPushButton(widgetTitle);
    previousMonthBtn->setObjectName("previousMonthBtn");

    previousDayBtn = new QPushButton(widgetTitle);
    previousDayBtn->setObjectName("previousDayBtn");

    nextYearBtn = new QPushButton(widgetTitle);
    nextYearBtn->setObjectName("nextYearBtn");

    nextMonthBtn = new QPushButton(widgetTitle);
    nextMonthBtn->setObjectName("nextMonthBtn");

    nextDayBtn = new QPushButton(widgetTitle);
    nextDayBtn->setObjectName("nextDayBtn");

    horLayoutTiTle->addWidget(previousYearBtn);
    horLayoutTiTle->addWidget(previousMonthBtn);
    horLayoutTiTle->addWidget(previousDayBtn);
    horLayoutTiTle->addStretch(1);
    this->initTitleCenterWidget();
    horLayoutTiTle->addWidget(widgetTitleCenter);
    horLayoutTiTle->addStretch(1);
    horLayoutTiTle->addWidget(nextDayBtn);
    horLayoutTiTle->addWidget(nextMonthBtn);
    horLayoutTiTle->addWidget(nextYearBtn);
    connect(previousYearBtn, &QPushButton::clicked, this,&CalendarWidget::sltPreviousYearBtnClicked);
    connect(previousMonthBtn, &QPushButton::clicked, this, &CalendarWidget::sltPreviousMonthBtnClicked);
    connect(previousDayBtn, &QPushButton::clicked, this, &CalendarWidget::sltPreviousDayBtnClicked);
    connect(nextYearBtn, &QPushButton::clicked, this, &CalendarWidget::sltNextYearBtnClicked);
    connect(nextMonthBtn, &QPushButton::clicked, this, &CalendarWidget::sltNextMonthBtnClicked);
    connect(nextDayBtn, &QPushButton::clicked, this, &CalendarWidget::sltNextDayBtnClicked);
}
void CalendarWidget::initTitleCenterWidget(){
    widgetTitleCenter = new QWidget(widgetTitle);
    widgetTitleCenter->setObjectName("widgetTitleCenter");
    horLayoutTiTleCenter = new QHBoxLayout(widgetTitleCenter);
    horLayoutTiTleCenter -> setContentsMargins(0, 0, 0, 0);
    horLayoutTiTleCenter -> setSpacing(0);
    labelShowYear = new ClickableLabel(widgetTitleCenter);
    labelShowYear -> setObjectName("labelShowYear");
    labelShowYear -> setText("2018年");
    labelShowMonth = new ClickableLabel(widgetTitleCenter);
    labelShowMonth -> setObjectName("labelShowMonth");
    labelShowMonth->setText("7月");
    labelShowDay = new ClickableLabel(widgetTitleCenter);
    labelShowDay -> setObjectName("labelShowDay");
    labelShowDay->setText("20日");
    connect(labelShowYear, &ClickableLabel::clicked, this,&CalendarWidget::sltLabelShowYearClicked);
    connect(labelShowMonth, &ClickableLabel::clicked, this,&CalendarWidget::sltLabelShowMonthClicked);
    connect(labelShowDay, &ClickableLabel::clicked, this,&CalendarWidget::sltLabelShowDayClicked);

    horLayoutTiTleCenter->addWidget(labelShowDay);
    horLayoutTiTleCenter->addWidget(labelShowMonth);
    horLayoutTiTleCenter->addWidget(labelShowYear);
    horLayoutTiTle->addWidget(widgetTitleCenter);
}
void CalendarWidget::initYearWidget(){
    widgetYear = new QWidget(this);
    widgetYear->setObjectName("widgetYear");
    gridLayoutYear = new QGridLayout(widgetYear);
    gridLayoutYear -> setContentsMargins(10,10,10,10);
    gridLayoutYear -> setHorizontalSpacing(5);
    gridLayoutYear -> setVerticalSpacing(10);
    for (int i = 0; i < 10; i++) {
        labelYear[i] = new ClickableLabel(widgetYear);
        labelYear[i]->setObjectName("labelYear"+QString::number(i+1));
        labelYear[i]->setAlignment(Qt::AlignCenter);
        labelYear[i]->setText(QString::number(2010+i));
        gridLayoutYear ->addWidget(labelYear[i], i / 2, i % 2);
        connect(labelYear[i], &ClickableLabel::clicked, this,&CalendarWidget::sltYearLabelClicked);
    }
}
void CalendarWidget::initMonthWidget(){
    widgetMonth = new QWidget(this);
    widgetMonth->setObjectName("widgetMonth");
    gridLayoutMonth = new QGridLayout(widgetMonth);
    gridLayoutMonth -> setContentsMargins(10,10,10,10);
    gridLayoutMonth -> setHorizontalSpacing(10);
    gridLayoutMonth -> setVerticalSpacing(20);
    for (int i = 0; i < 12; i++) {
        labelMonth[i] = new ClickableLabel(widgetMonth);
        labelMonth[i]->setObjectName("labelMonth"+QString::number(i));
        labelMonth[i]->setAlignment(Qt::AlignCenter);
        labelMonth[i]->setText(s_strMonth[i]);
        gridLayoutMonth ->addWidget(labelMonth[i], i / 3, i % 3);
        connect(labelMonth[i], &ClickableLabel::clicked, this,&CalendarWidget::sltMonthLabelClicked);
        connect(labelMonth[i], &ClickableLabel::rightButtonClicked, this,&CalendarWidget::sltMonthLabelRightClicked);
    }
}
void CalendarWidget::initDateWidget(){
    widgetDate = new QWidget(this);
    widgetDate->setObjectName("widgetDate");
    QVBoxLayout *verLayoutDate = new QVBoxLayout(widgetDate);
    verLayoutDate->setContentsMargins(0, 0, 0, 0);
    verLayoutDate->setSpacing(0);
    widgetWeek = new QWidget(widgetDate);
    widgetWeek->setObjectName("widgetWeek");
    widgetWeek->setMinimumHeight(30);
    widgetWeek->setMaximumHeight(30);
    horLayoutWeek = new QHBoxLayout(widgetWeek);
    horLayoutWeek->setContentsMargins(0, 0, 0, 0);
    horLayoutWeek->setSpacing(0);
    for (int i = 0; i < 7; i++) {
        labelWeek[i] = new QLabel(widgetWeek);
        labelWeek[i]->setText(s_strWeek[i]);
        labelWeek[i]->setObjectName("labelWeek"+QString::number(i));
        labelWeek[i]->setAlignment(Qt::AlignCenter);
        horLayoutWeek->addWidget(labelWeek[i]);
    }
    verLayoutDate->addWidget(widgetWeek);
    // [1] 主体日期
    widgetDateBody = new QWidget(widgetDate);
    widgetDateBody -> setObjectName("widgetDateBody");
    gridLayoutDateBody = new QGridLayout(widgetDateBody);
    gridLayoutDateBody->setContentsMargins(0, 0, 0, 0);
    gridLayoutDateBody->setHorizontalSpacing(0);
    gridLayoutDateBody->setVerticalSpacing(0);
    for (int i = 0; i < 42; i++) {
        labelDay[i] = new DayLabel(widgetDateBody);
        labelDay[i]->setObjectName("labelDay"+QString::number(i));
        labelDay[i]->setAlignment(Qt::AlignCenter);
        labelDay[i]->setText(QString::number(i));
        gridLayoutDateBody ->addWidget(labelDay[i], i / 7, i % 7);
        connect(labelDay[i], &DayLabel::signalClicked, this,&CalendarWidget::sltDayLabelClicked);
        connect(labelDay[i], &DayLabel::signalRightButtonClicked, this,&CalendarWidget::sltDayLabelRightClicked);
    }
    verLayoutDate->addWidget(widgetDateBody);
}
void CalendarWidget::initHourWidget(){
    widgetHour = new QWidget(this);
    widgetHour->setObjectName("widgetHour");
    gridLayoutHour = new QGridLayout(widgetHour);
    gridLayoutHour->setContentsMargins(0,20,0,20);
    gridLayoutHour->setHorizontalSpacing(0);
    gridLayoutHour->setVerticalSpacing(0);
    for (int i = 0; i < 35; i++) {

        labelHour[i] = new HourLabel(widgetHour);
        labelHour[i]->setObjectName("labelHour"+QString::number(i));
        labelHour[i]->setAlignment(Qt::AlignCenter);
        labelHour[i]->setText(QString::number((23+i)%24));
        gridLayoutHour ->addWidget(labelHour[i], i / 7, i % 7);
        connect(labelHour[i], &HourLabel::signalClicked, this,&CalendarWidget::sltHourLabelClicked);
        connect(labelHour[i], &HourLabel::signalRightButtonClicked, this,&CalendarWidget::sltHourLabelRightClicked);
        if(i < 3){
            labelHour[i]->setType(HourLabel::E_HOUR::PREV_DAY_HOUR);
        }else if(i > 26){
            labelHour[i]->setType(HourLabel::E_HOUR::NEXT_DAY_HOUR);
        }else{
            labelHour[i]->setType(HourLabel::E_HOUR::CURR_DAY_HOUR);
        }
    }
}

//void CalendarWidget::initICons(){
//   previousYear_normal_ico = QIcon(":/ico/previousYear_normal");
//   previousYear_hover_ico = QIcon(":/ico/previousYear_hover");
//   previousMonth_normal_ico = QIcon(":/ico/previousMonth_normal");
//   previousMonth_hover_ico = QIcon(":/ico/previousMonth_hover");
//   previousDay_normal_ico = QIcon(":/ico/previousDay_normal");
//   previousDay_hover_ico = QIcon(":/ico/previousDay_hover");
//   nextYear_normal_ico = QIcon(":/ico/nextYear_normal");
//   nextYear_hover_ico = QIcon(":/ico/nextYear_hover");
//   nextMonth_normal_ico = QIcon(":/ico/nextMonth_normal");
//   nextMonth_hover_ico = QIcon(":/ico/nextMonth_hover");
//   nextDay_normal_ico = QIcon(":/ico/nextDay_normal");
//   nextDay_hover_ico = QIcon(":/ico/nextDay_hover");
//}


QDateTime CalendarWidget::getDateTime() const
{
    return selectedDateTime;
}

void CalendarWidget::setDateTime(const QDateTime &value)
{
    QDateTime temp (QDateTime::fromString(value.toString("yyyyMMddHH"),"yyyyMMddHH"));
    if(temp == selectedDateTime){
        return;
    }
    QDateTime olderTime = selectedDateTime;
    selectedDateTime = value;
    emit selectDateTimeChanged(value,olderTime);
}

void CalendarWidget::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
CalendarWidget::USE_TYPE CalendarWidget::getUsedType() const
{
    return usedType;
}
void CalendarWidget::setUsedType(const USE_TYPE &value)
{
    usedType = value;
}
