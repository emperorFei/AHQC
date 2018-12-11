#include "datetimepagenumberwidget.h"
QTime DateTimePageNumberWidget::zeroHour(QTime(00,00));
QTime DateTimePageNumberWidget::lastHour(QTime(23,00));

DateTimePageNumberWidget::DateTimePageNumberWidget(QWidget *parent) :
    QWidget(parent),
    issueDatas(Q_NULLPTR),
    range(Q_NULLPTR),
    dayLabelSelected(Q_NULLPTR),
    hourLabelSelected(Q_NULLPTR)
{
    initWidgets();
    initStyleSheet();
}
void DateTimePageNumberWidget::select(const QDateTime &dateTime){
    QDate date = dateTime.date();
    for(SignedDayLabel * dayLabel : dayLabels){
        if(dayLabel->getDate() == date){
            dayLabel->setSelected(true);
            dayLabelSelected = dayLabel;
        }else{
            dayLabel->setSelected(false);
        }
        updateHourWidget();
    }
    for(SignedHourLabel *label:hourLabels){
        if(label->getDateTime() == dateTime){
            label->setSelected(true);
            hourLabelSelected = label;
        }else{
            label->setSelected(false);
        }
    }
    update();
}
void DateTimePageNumberWidget::updateAfterPageChange(){
    updateDayWidget();
    updateHourWidget();
    update();
}

void DateTimePageNumberWidget::sltDayLabelClicked(const QDate& date){
    if((dayLabelSelected != Q_NULLPTR && date == dayLabelSelected->getDate())
            || hourLabelSelected == Q_NULLPTR){
        return;
    }
    QTime time = hourLabelSelected->getDateTime().time();
    select(QDateTime(date,time));
    emit selectedDateTimeChanged(hourLabelSelected->getDateTime());
}
void DateTimePageNumberWidget::sltHourLabelClicked(const QDateTime& dateTime){
    for(SignedHourLabel *hourLabel: hourLabels){
        if(hourLabel->getDateTime() == dateTime){
            hourLabel->setSelected(true);
            hourLabelSelected = hourLabel;
        }else{
            hourLabel->setSelected(false);
        }
    }
    emit selectedDateTimeChanged(dateTime);
}

void DateTimePageNumberWidget::initWidgets(){
    this->setMaximumSize(264,140);
    this->setMinimumSize(264,140);
    this->setObjectName("pageComponent");
    QHBoxLayout *layout_main = new QHBoxLayout;
    layout_main->setContentsMargins(0,2,2,2);
    layout_main->setSpacing(0);
    this->setLayout(layout_main);
    initDayWidget();
    initHourWidget();
    layout_main->addWidget(dayWidget);
    layout_main->addWidget(hourWidget);
}
void DateTimePageNumberWidget::initDayWidget(){
    dayWidget = new QWidget(this);
    dayWidget ->setMaximumSize(40,136);
    dayWidget ->setMinimumSize(40,136);
    dayWidget -> setObjectName("dayWidget_PN");

    //dayWidget->setStyleSheet(QString("border-right:3 solid rgb(128,128,128);"));
    QVBoxLayout *layout_dayWidget = new QVBoxLayout;
    dayWidget->setLayout(layout_dayWidget);
    layout_dayWidget->setContentsMargins(0,0,2,0);
    layout_dayWidget->setSpacing(0);
    for(int i=0;i<4;i++){
        SignedDayLabel *dayLabel = new SignedDayLabel(dayWidget);
        dayLabel->setObjectName("dayLabel"+QString::number(i)+"_PN");
        dayLabel->setText("d"+QString::number(i));
        layout_dayWidget->addWidget(dayLabel);
        dayLabels.append(dayLabel);
        connect(dayLabel,&SignedDayLabel::signalClicked,this,&DateTimePageNumberWidget::sltDayLabelClicked);
    }
}
void DateTimePageNumberWidget::initHourWidget(){
    hourWidget = new QWidget(this);
    hourWidget -> setObjectName("hourWidget_PN");
    QGridLayout *layout_hourWidget = new QGridLayout;
    hourWidget->setLayout(layout_hourWidget);
    layout_hourWidget->setContentsMargins(0,10,0,10);
    layout_hourWidget->setSpacing(0);
    SignLevel level = SignLevel::SIGNINFO;
    for(int i=0;i<24;i++){
        SignedHourLabel *hourLabel = new SignedHourLabel(hourWidget);
        hourLabel->setObjectName("hourLabel"+QString::number(i)+"_PN");
        hourLabel->setText(QString::number(i));
        layout_hourWidget->addWidget(hourLabel,i/6,i%6);
        hourLabels.append(hourLabel);
        hourLabel->setSignLevel(level);
        connect(hourLabel,&SignedHourLabel::signalClicked,this,&DateTimePageNumberWidget::sltHourLabelClicked);
    }
}
void DateTimePageNumberWidget::initStyleSheet(){
    this->setStyleSheet(
                  QString(
                    "#pageComponent{\n"
                        "border:2 solid blue;\n"
                        "border-left: none;\n"
                    "}\n"
                    "#dayWidget_PN{\n"
                        "border-right:2 solid rgb(1,128,128);\n"
                    "}\n"
                    "#hourWidget_PN{\n"

                    "}\n"
                    ));
}
void DateTimePageNumberWidget::updateWidgets(){
    updateDayWidget();
    updateHourWidget();
}
void DateTimePageNumberWidget::updateDayWidget(){
    if(range == Q_NULLPTR){
        return;
    }
    QDate date = range->first.date();
    QDate lastDate = range->second.date();
    QDate tempDate(1970,01,01);
    for(int i=0;i<4;i++){
        SignLevel signLevel = SignLevel::SIGNINFO;
        MyDoubleLabel::Level highestLevel = MyDoubleLabel::Level::INFO;
        QDate dateOfIssue(1970,1,1);
        MyDoubleLabel::Level level = MyDoubleLabel::Level::INFO ;
        tempDate = date.addDays(i);
        dayLabels[i]->setDate(tempDate);
        dayLabels[i]->setText(tempDate.toString("dd"));
        if(tempDate > lastDate){
            dayLabels[i]->setInErrorRange(true);
        }else{
            dayLabels[i]->setInErrorRange(false);
        }
        QMap<QDateTime,QPair<QString,MyDoubleLabel::Level> >::const_iterator it
                = issueDatas -> cbegin();
        QMap<QDateTime,QPair<QString,MyDoubleLabel::Level> >::const_iterator end
                = issueDatas -> cend();
        while(it != end){
            dateOfIssue = it.key().date();
            level = it.value().second;
            if(dateOfIssue == tempDate && level > highestLevel){
                highestLevel = level;
            }
            ++it;
        }
        switch(highestLevel){
            case MyDoubleLabel::Level::INFO :
                signLevel = SignLevel::SIGNINFO;
                break;
            case MyDoubleLabel::Level::SUSPECTED :
                signLevel = SignLevel::SIGNSUSPECT;
                break;
            case MyDoubleLabel::Level::CLASH :
                signLevel = SignLevel::SIGNCLASH ;
                break;
            case MyDoubleLabel::Level::MISSING:
                signLevel = SignLevel::SIGNMISSING;
                break;
            case MyDoubleLabel::Level::MISSINGZDATA :
                signLevel = SignLevel::SIGNMISSINGZDATA;
                break;
            case MyDoubleLabel::Level::MISSINGAMDATA :
                signLevel = SignLevel::SIGNMISSINGADATA;
                break;
            case MyDoubleLabel::Level::ERROR :
                signLevel = SignLevel::SIGNERROR;
                break;
        }
        dayLabels[i]->setSignLevel(signLevel);
    }
}
void DateTimePageNumberWidget::updateHourWidget(){
    if(range == Q_NULLPTR){
        return;
    }

    for(SignedDayLabel *label:dayLabels){
        if(label->getBSelect() == true){
            QDateTime zeroTime = QDateTime(label->getDate(),zeroHour);
            QDateTime tempTime = QDateTime(label->getDate(),zeroHour);
            QDateTime lastTime = QDateTime(label->getDate(),lastHour);
            MyDoubleLabel::Level level = MyDoubleLabel::Level::INFO;
            SignLevel signLevel = SignLevel::SIGNINFO;
            for(int i=0;i<24;i++){
                signLevel = SignLevel::SIGNINFO;
                tempTime = zeroTime.addSecs(60*60*i);
                hourLabels[i]->setDateTime(tempTime);
                if(tempTime > range->second || tempTime < range->first){
                   hourLabels[i]->setInErrorRange(true);
                }else{
                   hourLabels[i]->setInErrorRange(false);
                }
                if(issueDatas->contains(tempTime)){
                    level = issueDatas->value(tempTime).second;
                    switch(level){
                        case MyDoubleLabel::Level::INFO :
                            signLevel = SignLevel::SIGNINFO;
                            break;
                        case MyDoubleLabel::Level::SUSPECTED :
                            signLevel = SignLevel::SIGNSUSPECT;
                            break;
                        case MyDoubleLabel::Level::CLASH :
                            signLevel = SignLevel::SIGNCLASH ;
                            break;
                        case MyDoubleLabel::Level::MISSING:
                            signLevel = SignLevel::SIGNMISSING;
                            break;
                        case MyDoubleLabel::Level::MISSINGZDATA :
                            signLevel = SignLevel::SIGNMISSINGZDATA;
                            break;
                        case MyDoubleLabel::Level::MISSINGAMDATA :
                            signLevel = SignLevel::SIGNMISSINGADATA;
                            break;
                        case MyDoubleLabel::Level::ERROR :
                            signLevel = SignLevel::SIGNERROR;
                            break;
                    }
                }
                hourLabels[i]->setSignLevel(signLevel);
            }

        }
    }

}

void DateTimePageNumberWidget::paintEvent(QPaintEvent *e){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
    QWidget::paintEvent(e);
}

