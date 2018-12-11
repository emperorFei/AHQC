#include "datetimedialog.h"
QTime DateTimeDialog::dayDemarcationTime = QTime::fromString("200000","HHmmss");
DateTimeDialog::DateTimeDialog(QWidget *parent) : QDialog(parent)
{
    initWidgets();
    updateWidgets();
    initStyleSheet();
}
DateTimeDialog::~DateTimeDialog(){

}

void DateTimeDialog::sltDayLabelClicked(ClickableLabel *label){
    int index = dayLabels.indexOf(label);
    QString timeRangeString(dateLabel_rangeStrings[index]);
    if(this->rangeOfTimeString != timeRangeString){
       this->rangeOfTimeString = timeRangeString;
       emit selectDateTimeRangeChanged(timeRangeString);
    }
    dateTimeRangeSelectDialog->close();
    this->close();
}
void  DateTimeDialog::sltConfirmBtnClicked(bool){
    if(rangeOfTimeString != dateTimeLabel->text()){
        emit selectDateTimeRangeChanged(dateTimeLabel->text());
    }
    dateTimeRangeSelectDialog->close();
    this->close();
}
void DateTimeDialog::sltDateTimeLabelClicked(ClickableLabel *label){
    if(!dateTimeRangeSelectDialog->isHidden()){
        dateTimeRangeSelectDialog->hide();
        return;
    }
    updateDateTimeDialog();
    int xOfLabel = label->geometry().x();
    int yOfLabel = label->geometry().y();
    int widthOfLabel = label->geometry().width();
    int heightOfLabel = label->geometry().height();
    QRect geometry = dateTimeRangeSelectDialog -> geometry();
    QPoint point = label->mapToGlobal(QPoint(xOfLabel,yOfLabel));
    point = QPoint(point.x()
                   +widthOfLabel
                   -geometry.width()
                   -xOfLabel
                   +marginRight,
                   point.y()
                   +heightOfLabel
                   -10
                   -marginTop);
    dateTimeRangeSelectDialog->move(point);

    dateTimeRangeSelectDialog->show();
}

void DateTimeDialog::sltCloseBtnClicked(bool){
    dateTimeRangeSelectDialog->close();
    this->close();
}

void DateTimeDialog::sltSelectedDateTimeChanged(const QDateTime &startTime,const QDateTime &endTime){
    dateTimeLabel->setText(startTime.toString("yyyy-MM-dd HH")+" ～ "+endTime.toString("yyyy-MM-dd HH"));
}

void DateTimeDialog::initWidgets(){
    marginLeft = 10;
    marginTop = 10;
    marginRight = 10;
    marginBottom = 20;
    rangeOfTimeString = "2018-10-12 14 ～ 2018-10-13 16";
    dateLabel_rangeStrings = QList<QString>();
    for(int i=0;i<7;i++){
        dateLabel_rangeStrings.append("---");
    }
    this->setObjectName("selectDateTimeDialog");
    this->setMaximumSize(350,240);
    this->setMinimumSize(350,240);

    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );

    QVBoxLayout *topLayout = new QVBoxLayout;

    this->setLayout(topLayout);

    topLayout -> setContentsMargins(marginLeft,marginTop,marginRight,marginBottom);

    bgWidget = new QWidget(this);
    bgWidget->setObjectName("bgWidgetOfDateSelectDialog");
    layout_bg = new QVBoxLayout;
    bgWidget -> setLayout(layout_bg);
    topLayout->addWidget(bgWidget);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(bgWidget);
    shadow -> setOffset(0, 0);
    shadow -> setColor(QColor("#888888"));
    //shadow -> setColor(QColor("#FF4444"));
    shadow->setBlurRadius(20);
    bgWidget -> setGraphicsEffect(shadow);
    layout_bg -> setContentsMargins(20,20,20,20);
    //layout_bg -> setContentsMargins(10,3,10,20);

    QHBoxLayout *layout_dateTimeSelectLabel = new QHBoxLayout;
    QLabel *dateTimeSelect_label = new QLabel("时间选择",this);
    closeBtn = new QPushButton(this);
    closeBtn -> setObjectName("closeBtn_dateTimeDialog");
    closeBtn -> setMinimumSize(25,25);
    closeBtn -> setMaximumSize(25,25);



    layout_dateTimeSelectLabel->addWidget(dateTimeSelect_label);
    layout_dateTimeSelectLabel->addStretch(1);
    layout_dateTimeSelectLabel->addWidget(closeBtn);

    QWidget *line = new QWidget(this);
    line->setMinimumHeight(1);
    line->setMaximumHeight(1);
    line->setStyleSheet("background-color:rgb(128,128,128)");


    QWidget *selectMianWidget = new QWidget(this);
    QHBoxLayout *layout_selectMainWidget = new QHBoxLayout;
    selectMianWidget->setLayout(layout_selectMainWidget);
    layout_selectMainWidget->setContentsMargins(20,15,10,25);
    layout_selectMainWidget->setSpacing(10);
    dateTimeLabel = new ClickableLabel(this);
    dateTimeLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    dateTimeLabel->setObjectName("selectDateTimeLabel_inDialog");
    dateTimeLabel->setMinimumHeight(25);
    dateTimeLabel->setMaximumHeight(25);
    dateTimeLabel->setText("2018-10-12 14 ～ 2018-10-13 16");
    confirmBtn = new QPushButton("确定",this);
    confirmBtn -> setMinimumSize(40,25);
    confirmBtn -> setMaximumSize(40,25);
    confirmBtn -> setObjectName("confirmDateTime_btn");
    layout_selectMainWidget->addWidget(dateTimeLabel);
    layout_selectMainWidget->addWidget(confirmBtn);

    QLabel *fastSelectLabel = new QLabel("按观测日快速选择",this);


    QWidget *fastSelectMianWidget = new QWidget(this);
    fastSelectMianWidget->setObjectName("fastSelectMianWidget");
    QHBoxLayout *layout_fastSelectMainWidget = new QHBoxLayout;
    fastSelectMianWidget->setLayout(layout_fastSelectMainWidget);
    layout_fastSelectMainWidget->setContentsMargins(0,0,0,0);
    layout_fastSelectMainWidget->setSpacing(0);
    for(int i=0;i<7;i++){
        ClickableLabel *dateLabel = new ClickableLabel(this);
        dateLabel->setAlignment(Qt::AlignCenter);
        dayLabels.append(dateLabel);        
        connect(dateLabel,&ClickableLabel::clicked,this,&DateTimeDialog::sltDayLabelClicked);
        layout_fastSelectMainWidget->addWidget(dateLabel);
    }

    layout_bg -> addLayout(layout_dateTimeSelectLabel);
    layout_bg -> addWidget(line);
    layout_bg -> addWidget(selectMianWidget);
    layout_bg -> addWidget(fastSelectLabel);
    layout_bg -> addWidget(fastSelectMianWidget);

    dateTimeRangeSelectDialog = new DateTimeRangeSelectDialog(this);


    updateWidgets();

    connect(confirmBtn,&QPushButton::clicked,this,&DateTimeDialog::sltConfirmBtnClicked);
    connect(dateTimeLabel,&ClickableLabel::clicked,this,&DateTimeDialog::sltDateTimeLabelClicked);
    connect(closeBtn,&QPushButton::clicked,this,&DateTimeDialog::sltCloseBtnClicked);
    connect(dateTimeRangeSelectDialog,&DateTimeRangeSelectDialog::dateTimeRangeChanged,this,&DateTimeDialog::sltSelectedDateTimeChanged);


}

void DateTimeDialog::initStyleSheet(){
    this->setStyleSheet(this->styleSheet()+
        QString(
//            "#selectDateTimeDialog{\n"
////                "border-style:solid;\n"
////                "border-width:1;\n"
////                "border-color:lightblue;\n"
//            "}\n"
            "#bgWidgetOfDateSelectDialog{\n"
                "background-color:white;\n"
            "}\n"
            "#fastSelectMianWidget > .ClickableLabel{\n"
                "border-style:solid;\n"
                "border-width:1;\n"
                "border-color:lightblue;\n"
            "}\n"
            "#fastSelectMianWidget > .ClickableLabel:hover{\n"
                "color:white;\n"
                "background-color:lightblue;\n"
            "}\n"
            "QPushButton{\n"
                "color:white;\n"
                "background-color:lightblue;\n"
                "border-radius:5px;\n"
            "}\n"
            "QPushButton:hover{\n"
                "background-color:rgb(59,110,158);\n"
            "}\n"
            "#closeBtn_dateTimeDialog{\n"
                "background-color: transparent;\n"
                "image: url(:/ico/close_normal);\n"
            "}"
            "#closeBtn_dateTimeDialog:hover{\n"
                "image: url(:/ico/close_hover);\n"
            "}\n"
            ".QLabel{\n"
                "font-weight: bold;\n"
            "}\n"
            "#selectDateTimeLabel_inDialog{\n"
                "border-style:solid;\n"
                "border-width:1;\n"
                "border-color:lightgrey;\n"
            "}\n"
            "#selectDateTimeLabel_inDialog:hover{\n"
                "border-style:solid;\n"
                "border-width:1;\n"
                "border-color:lightblue;\n"
            "}\n"

            ));
}

void DateTimeDialog::updateDialog(){
    updateWidgets();
}
void DateTimeDialog::updateWidgets(){
    updateDayLabels();
    updateDateTimeLabel();
    updateDateTimeDialog();
}
void DateTimeDialog::updateDateTimeDialog(){
    QString rangeString = dateTimeLabel->text();
    dateTimeRangeSelectDialog->updateCalendars(rangeString,"～");
}

void DateTimeDialog::updateDateTimeLabel(){
    if(!dateTimeRangeSelectDialog->isHidden()){
        dateTimeLabel->setText(dateTimeRangeSelectDialog->getDateTimeRangeString());
    }else{
        dateTimeLabel->setText(rangeOfTimeString);
    }
}

void DateTimeDialog::updateDayLabels(){
    static QTime startTime(21,00);
    static QTime endTime(20,00);
    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentAWSDay = dateTime2AWSDay(currentTime);
    int index = -7;
    QDateTime startHour(QDate(1970,01,01),QTime(00,00));
    QDateTime endHour(QDate(1970,01,01),QTime(00,00));
    QDate date(1970,01,01);
    for(int i=0;i<7;i++){
        date = currentAWSDay.addDays(++index);
        startHour = QDateTime(date.addDays(-1),startTime);
        endHour = QDateTime(date,endTime);
        dayLabels[i]->setText(date.toString("MM月dd"));
        dateLabel_rangeStrings[i] = startHour.toString("yyyy-MM-dd HH")+" ～ "+endHour.toString("yyyy-MM-dd HH");
    }
    ClickableLabel *lastDayLabel = dayLabels.at(6);
    if(currentTime > QDateTime(currentAWSDay.addDays(-1),dayDemarcationTime.addSecs(60*60))){
        dateLabel_rangeStrings[6] = QDateTime(currentAWSDay.addDays(-1),startTime).toString("yyyy-MM-dd HH")+" ～ "+currentTime.toString("yyyy-MM-dd HH");
        lastDayLabel->setEnabled(true);
    }else if(currentTime > QDateTime(currentAWSDay.addDays(-1),dayDemarcationTime)){
        lastDayLabel->setDisabled(true);
    }
}
QDate DateTimeDialog::dateTime2AWSDay(const QDateTime &dateTime){
    QDate awsDay = dateTime.date();
    if(dateTime.time() > dayDemarcationTime){
       awsDay = awsDay.addDays(1);
    }
    return awsDay;
}

QString DateTimeDialog::getRangeOfTimeString() const
{
    return rangeOfTimeString;
}

void DateTimeDialog::setRangeOfTimeString(const QString &value)
{
    if(rangeOfTimeString == value){
        return;
    }else{
       rangeOfTimeString = value;
       updateWidgets();
    }
}




inline QPair<QDateTime,QDateTime> awsHourRangeOfDate(const QDate &date){
    if(date == QDate::currentDate()){
        return QPair<QDateTime,QDateTime>(QDateTime(date.addDays(-1),QTime(21,00)),QDateTime(date,QTime(20,00)));
    }
    return QPair<QDateTime,QDateTime>(QDateTime(date.addDays(-1),QTime(21,00)),QDateTime(date,QTime(20,00)));
}

int DateTimeDialog::getMarginBottom() const
{
    return marginBottom;
}

void DateTimeDialog::setMarginBottom(int value)
{
    marginBottom = value;
}

int DateTimeDialog::getMarginTop() const
{
    return marginTop;
}

void DateTimeDialog::setMarginTop(int value)
{
    marginTop = value;
}

int DateTimeDialog::getMarginRight() const
{
    return marginRight;
}

void DateTimeDialog::setMarginRight(int value)
{
    marginRight = value;
}

int DateTimeDialog::getMarginLeft() const
{
    return marginLeft;
}

void DateTimeDialog::setMarginLeft(int value)
{
    marginLeft = value;
}
