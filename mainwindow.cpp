#include "mainwindow.h"
#include "ui_mainwindow.h"
QString MainWindow::mainWidgetStyleTemplate =
        ".MyDoubleLabel{\n"
            "border-style:solid;\n"
            "border-width:2;\n"
            "border-radius:6;\n"
            "border-color:lightgrey;\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '0']{\n"
            "border-color:lightgrey;\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '1']{\n"
            "border-color:#{suspectColor};\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '2']{\n"
            "border-color:#{suspectColor};\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '3']{\n"
            "border-color:#{missingColor};\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '4']{\n"
            "border-color:#{suspectColor};\n"
        "}\n"
        ".MyDoubleLabel[checked = false][level = '5']{"
            "border-color:#{suspectColor};"
        "}"
        ".MyDoubleLabel[checked = false][level = '6']{"
            "border-color:#{errorColor};"
        "}"
        ".MyDoubleLabel[checked = true]{\n"
            "border-color:lightgrey;\n"
        "}\n";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainWidgetChanging(false),
    fullWidgetLeft(Q_NULLPTR),
    fullWidgetMiddle(Q_NULLPTR),
    fullWidgetRight(Q_NULLPTR),
    currentRange(Q_NULLPTR),
    azDatas(Q_NULLPTR),
    issueDatas(Q_NULLPTR),
    reachDataThreadInstance(new ReachDataThread(TimeRange(),this))
{
    ui->setupUi(this);
    currentRange = new QPair<QDateTime,QDateTime> (QDateTime(QDate(1970,01,01),QTime(00,00)),QDateTime(QDate(1970,01,01),QTime(00,00)));
    azDatas = new QMap<QDateTime,AZData>();
    issueDatas = new QMap<QDateTime,QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > >();
    this->setWindowIcon(QIcon(":/ico/qc"));
    initComponents();
    QDateTime beginTime(QDate(2018,12,5),QTime(00,00));
    QDateTime endTime(QDate(2018,12,5),QTime(10,00));
//    QTimer::singleShot(3000,
//                       [=](){
//        startReachDataByTimerange(TimeRange(beginTime,endTime,timeRange_bound::BEGINEND));
//                            }
//    );
//    QFont font("宋体");
//    font.setPointSize(10);
//    ui -> mainWidget->setFont(font);


    ui -> mainWidget->setCurrentIndex(0);


    reOrientateTurnPageBtn();

    QTimer::singleShot(0,[=](){
        this->setGeometry(bestRect);
    });
}

MainWindow::~MainWindow()
{
    delete currentRange;
    delete azDatas;
    delete issueDatas;
    delete ui;
    if(settingWidget != Q_NULLPTR){
       delete settingWidget;
    }
    //reachDataThreadInstance->exit();
    DBCenter::cleanCreatedConns();
}
void MainWindow::startReachDataByTimerange(const TimeRange &selectTimeRange){
    ui->refreshBtn->setDisabled(true);
    ui->selectedDateTimeRangeLabel->setDisabled(true);
    pageWidget->setDisabled(true);
    reachDataThreadInstance->setTimeRange(selectTimeRange);
    reachDataThreadInstance->start();
}
void MainWindow::reachDataByTimerange(const TimeRange &selectTimeRange){
    QSqlDatabase * database = DBCenter::getDBByAccountType(DBCenter::AccountType::SETTING);
    if(!database->open()){
        emit dbOpenFailed(true);
        return;
    }
    AWSMinuteDAOMySqlImp awsMinuteDao(database);
    ZDataDAOMysqlImp zDao(database);
    QList<QString> amFileNames4Save = AHQC::FileNameUtil::prepareAMFile4Select(selectTimeRange);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(selectTimeRange);
    for(const QString &filename: amFileNames4Save){
        awsMinuteDao.saveAMFile(filename);
    }
    for(const QDateTime &observeTime : focusedHours){
        AWSMinuteData amData = awsMinuteDao.findByOT(observeTime);
        QMap<QString,int> stastictsData = awsMinuteDao.getExtremums(observeTime);
        stastictsData.unite(awsMinuteDao.getVAndRain(observeTime));
        AHData ahData(amData,stastictsData);
        ZData zData(zDao.checkSaveAndFindByOT(observeTime));
        AZData azData(ahData,zData);
        azDatas->insert(observeTime,azData);
    }
    database->close();
    emit reachDataFinish(selectTimeRange.older,selectTimeRange.later);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    reOrientateTurnPageBtn();
}

void MainWindow::reOrientateTurnPageBtn(){
    QRect rectOfMainWidget = ui->packingOfMainWidget->geometry();
    QPushButton *nextBtn = ui->next_btn;
    QPushButton *previousBtn = ui->previous_btn;
    nextBtn->setGeometry(rectOfMainWidget.width()-20,
                         rectOfMainWidget.height()/5*2,
                         20,
                         rectOfMainWidget.height()/5);
    previousBtn ->setGeometry(0,
                              rectOfMainWidget.height()/5*2,
                              20,
                              rectOfMainWidget.height()/5);
    ui -> mainWidget->setGeometry(0,0,rectOfMainWidget.width(),rectOfMainWidget.height());
}
void MainWindow::initComponents(){
    maxSizeHint = false;
    marginPix = 24;
    QDesktopWidget* desktopWidget = QApplication::desktop();
    deskRect = desktopWidget->availableGeometry();
    bestRect = QRect(deskRect.width()/2-1440/2,deskRect.height()/2-720/2,1400,720);
    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint );
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(30);
    //给嵌套QWidget设置阴影
    ui->widget_bg->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->lay_bg->setMargin(marginPix);

    isLeftPressDown = false;
    this->dir = NONE;
    this->setMouseTracking(true);
    ui->widget_bg->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->titleWidget->setMouseTracking(true);
    ui->packingOfMainWidget->setMouseTracking(true);
    ui->mainWidget->setMouseTracking(true);
    ui->rightWidget->setMouseTracking(true);
    ui->titleUtilWidget->setMouseTracking(true);
    ui->minButton->setMouseTracking(true);
    ui->maxButton->setMouseTracking(true);
    ui->closeButton->setMouseTracking(true);
    ui->searchEdit->setMouseTracking(true);

    QIcon iconOfNextBtn(":ico/btn_2Right");
    ui->next_btn->setText("");
    ui->next_btn->setIcon(iconOfNextBtn);
    ui->next_btn->setIconSize(QSize(20,20));
    QIcon iconOfPreviousBtn(":ico/btn_2Left");
    ui->previous_btn->setText("");
    ui->previous_btn->setMouseTracking(true);
    ui->previous_btn->setIcon(iconOfPreviousBtn);
    ui->previous_btn->setIconSize(QSize(20,20));


    dateTimeSelectDialog = new DateTimeDialog(this);
    dateTimeSelectDialog -> setObjectName("selectDateTimeDialog");
    dateTimeSelectDialog -> hide();
    settingWidget = new SettingDialog();



    settingWidget->hide();
    pageWidget = new DateTimePageNumberWidget(this);
    pageWidget -> issueDatas = this -> issueDatas;
    pageWidget -> range = this -> currentRange;
    ui->verticalLayout->insertWidget(2,pageWidget);

    refreshMainWidgetStyleSheet();

    fullWidgetLeft = new FullWidegt(ui->mainWidget);
    fullWidgetMiddle = new FullWidegt(ui->mainWidget);
    fullWidgetRight = new FullWidegt(ui->mainWidget);

    ui->mainWidget->insertWidget(0,fullWidgetLeft);
    ui->mainWidget->insertWidget(1,fullWidgetMiddle);
    ui->mainWidget->insertWidget(2,fullWidgetRight);

    int lastIndex = ui -> mainWidget->count() -1;
    while(lastIndex > 2){
        QWidget *widget = ui -> mainWidget->widget(lastIndex);
        ui -> mainWidget->removeWidget(widget);
        widget->deleteLater();
        lastIndex = ui -> mainWidget->count() -1;
    }
    connect(ui->previous_btn,&QPushButton::clicked,this,&MainWindow::sltPreviousBtnClicled);
    connect(ui->next_btn,&QPushButton::clicked,this,&MainWindow::sltNextBtnClicled);
    connect(ui->minButton,&QPushButton::clicked,this,&MainWindow::sltMinBtnClicked);
    connect(ui->maxButton,&QPushButton::clicked,this,&MainWindow::sltMaxBtnClicked);
    connect(ui->closeButton,&QPushButton::clicked,this,&MainWindow::sltCloseBtnClicked);
    connect(ui->showMoreButton,&QPushButton::clicked,this,&MainWindow::sltShowMoreBtnClicked);
    connect(ui->selectedDateTimeRangeLabel,&ClickableLabel::clicked,this,&MainWindow::sltSelectedDateTimeRangeLabelClicked);
    connect(settingWidget,&SettingDialog::QCColorChanged,this,&MainWindow::sltQCColorChanged);
    connect(dateTimeSelectDialog,&DateTimeDialog::selectDateTimeRangeChanged,this,&MainWindow::sltSelectDateTimeRangeChanged);
    connect(ui->refreshBtn,&QPushButton::clicked,this,&MainWindow::sltRefreshBtnClicked);
    connect(this,&MainWindow::selectRangeAutoChanged,this,&MainWindow::sltSelectRangeAutoChanged);
    connect(this,&MainWindow::selectOver,this,&MainWindow::sltSelectOver);
    connect(this,&MainWindow::reachDataFinish,this,&MainWindow::sltReachDataFinish);
    connect(ui->mainWidget,&AnimationStackedWidget::animationFinishedSignal,this,&MainWindow::sltMainWidgetAnimationFinished);
    connect(pageWidget,&DateTimePageNumberWidget::selectedDateTimeChanged,this,&MainWindow::sltPageNumChanged);
    connect(settingWidget,&SettingDialog::QCItemsChanged,this,&MainWindow::sltQCItemsChanged);
    connect(settingWidget,&SettingDialog::QCColrConfirmChanged,this,&MainWindow::refreshMainWidgetStyleSheet);
    connect(this,&MainWindow::dbOpenFailed,this,&MainWindow::sltDBOpenFailedWhenRefreach);

    sltQCItemsChanged();
    refreshMainWidgetStyleSheet();
    pageWidget->setDisabled(true);
}
void MainWindow::refreshMainWidgetStyleSheet(){
    GlobalSetting *setting  = GlobalSetting::getInstance();
    QString missingColorString = setting->value("missingColor").toString().trimmed();
    QString errorColorString = setting->value("errorColor").toString().trimmed();
    QString suspectColorString = setting->value("suspectColor").toString().trimmed();
    QList<QString> listRGB_missingColor = missingColorString.split("-");
    QList<QString> listRGB_errorColor = errorColorString.split("-");
    QList<QString> listRGB_suspectColor = suspectColorString.split("-");
    QString styleString = QString(mainWidgetStyleTemplate)
                                .replace("#{missingColor}",
                                         "rgb("+listRGB_missingColor[0]+","
                                               +listRGB_missingColor[1]+","
                                               +listRGB_missingColor[2]+")")
                                .replace("#{suspectColor}",
                                         "rgb("+listRGB_suspectColor[0]+","
                                               +listRGB_suspectColor[1]+","
                                               +listRGB_suspectColor[2]+")")
                                .replace("#{errorColor}",
                                         "rgb("+listRGB_errorColor[0]+","
                                               +listRGB_errorColor[1]+","
                                               +listRGB_errorColor[2]+")");
    ui->packingOfMainWidget->setStyleSheet(styleString);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev){
    ev->pos();
    if(ui->titleWidget->geometry().contains(ev->pos()) && dir== NONE){
        sltMaxBtnClicked(true);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(ui->titleWidget->geometry().contains(event->pos())){

    }
    switch(event->button()) {
    case Qt::LeftButton:
        if(ui->titleWidget->geometry().contains(event->pos()) || dir!= NONE){
            isLeftPressDown = true;
        }
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    case Qt::RightButton:
        break;
    default:
        QMainWindow::mousePressEvent(event);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    QMainWindow::mouseReleaseEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    if(!isLeftPressDown) {
        this->region(gloPoint);
    } else {
        if(dir != NONE) {
            QRect rMove(tl, rb);

            switch(dir) {
            case LEFT:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    QMainWindow::mouseMoveEvent(event);
}
void MainWindow::checkAZDatas(){
    issueDatas->clear();
    QList<QString> tempQCI = AHQC::QCItemNames;
    QMap<QDateTime,AZData>::Iterator it =  (*azDatas).begin();
    QMap<QDateTime,AZData>::Iterator end =  (*azDatas).end();
    QPair<QString,QString> dataPair("---","---");
    QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,AHQC::DataLevel::INFO);
    QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > defaultSeriousIssue = QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >("unchecked", pair);
    while(it != end){
        AZData &theAZData = it.value();
        theAZData.mostSeriousIssue = defaultSeriousIssue;
        QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >::Iterator itOfAZData =  it.value().data.begin();
        QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >::Iterator endOfAZData =  it.value().data.end();
        while(itOfAZData != endOfAZData){
            if((itOfAZData.value().second != AHQC::DataLevel::INFO) &&
                    theAZData.mostSeriousIssue.second.second < itOfAZData.value().second){
                if(AHQC::QCItemNames.contains(itOfAZData.key())){
                    theAZData.mostSeriousIssue = QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >(itOfAZData.key(),itOfAZData.value());
                }
            }
            ++itOfAZData;
        }
        if(theAZData.mostSeriousIssue.first == "unchecked"){
            theAZData.mostSeriousIssue.first = "noSuspectedData";
        }else{
           issueDatas->insert(theAZData.observeTime,theAZData.mostSeriousIssue);
        }
        ++it;
    }
}
void MainWindow::region(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void MainWindow::sltPreviousBtnClicled(){
    if(mainWidgetChanging){
        return;
    }
    FullWidegt * currentWidget = static_cast<FullWidegt *>(ui -> mainWidget->currentWidget());
    QDateTime currentDateTime = currentWidget->getObserveTime();
    if(currentDateTime == currentRange->first){
        return;
    }else{
        pageWidget->setDisabled(true);
        ui -> mainWidget -> forward();
    }
}
void MainWindow::sltNextBtnClicled(){
    if(mainWidgetChanging){
        return;
    }
    FullWidegt * currentWidget = static_cast<FullWidegt *>(ui -> mainWidget->currentWidget());
    QDateTime currentDateTime = currentWidget->getObserveTime();
    if(currentDateTime == currentRange->second){
        return;
    }else{
        pageWidget->setDisabled(true);
        ui -> mainWidget -> next();
    }
}
void MainWindow::sltQCColorChanged(const QString &missingColorRgbString,const QString &suspectColorRgbString,const QString &errorColorRgbString){
    QString styleString = QString(mainWidgetStyleTemplate)
                                .replace("#{missingColor}",
                                         missingColorRgbString)
                                .replace("#{suspectColor}",
                                         suspectColorRgbString)
                                .replace("#{errorColor}",
                                         errorColorRgbString);
    ui->packingOfMainWidget->setStyleSheet(styleString);
    ui->packingOfMainWidget->update();
}

void MainWindow::sltShowMoreBtnClicked(bool){
//    static int clickCount = 0;
//    if(clickCount % 2 == 0){
//       settingWidget->show();
//    }else{
//       settingWidget->hide();
//    }
//    ++clickCount;


    if(settingWidget->isHidden()){

        settingWidget->open();
    }else if(settingWidget->isMinimized()){
        settingWidget->show();
    }else{
        settingWidget->close();
    }
}
void MainWindow::sltMinBtnClicked(bool){
    this->showMinimized();
}

void MainWindow::sltMaxBtnClicked(bool){
    if(maxSizeHint == true){
        ui->lay_bg->setMargin(marginPix);
        this->setGeometry(bestRect);
        maxSizeHint = false;
    }else{
        ui->lay_bg->setMargin(0);
        this->setGeometry(deskRect);
        maxSizeHint = true;
    }

 //   this->showFullScreen();
}
void MainWindow::sltCloseBtnClicked(bool){
    this->close();
}

void MainWindow::sltSelectedDateTimeRangeLabelClicked(ClickableLabel *label){


    dateTimeSelectDialog->setRangeOfTimeString(label->text());
    dateTimeSelectDialog->updateDialog();
    int xOfLabel = label->geometry().x();
    int yOfLabel = label->geometry().y();
    int widthOfLabel = label->geometry().width();
    int heightOfLabel = label->geometry().height();
    QRect geometry = dateTimeSelectDialog->geometry();
    QPoint point = label->mapToGlobal(QPoint(xOfLabel,yOfLabel));
    point = QPoint(point.x()
                   +widthOfLabel
                   -geometry.width()
                   -xOfLabel
                   +dateTimeSelectDialog->getMarginRight(),
                   point.y()
                   +heightOfLabel
                   -dateTimeSelectDialog->getMarginTop());
    dateTimeSelectDialog->move(point);


    //dateTimeSelectDialog->show();
    dateTimeSelectDialog->open();
}
void MainWindow::sltSelectDateTimeRangeChanged(QString newDateTime){
    if(newDateTime != ui->selectedDateTimeRangeLabel->text()){
        ui->selectedDateTimeRangeLabel->setText(newDateTime);
    }
}
void MainWindow::sltRefreshBtnClicked(bool){
    if(mainWidgetChanging){
        return;
    }
    ui->refreshBtn->setDisabled(true);
    ui->selectedDateTimeRangeLabel->setDisabled(true);
    pageWidget->setDisabled(true);
    QList<QString> dateTimeStrings = ui->selectedDateTimeRangeLabel->text().split("～");
    dateTimeStrings[0] = dateTimeStrings[0].trimmed();
    dateTimeStrings[1] = dateTimeStrings[1].trimmed();
    QDateTime beginDateTiem = QDateTime::fromString(dateTimeStrings[0],"yyyy-MM-dd HH");
    QDateTime endDateTiem = QDateTime::fromString(dateTimeStrings[1],"yyyy-MM-dd HH");
    QDateTime lastSendHour = QDateTime::currentDateTime();
    lastSendHour = QDateTime::fromString(lastSendHour.toString("yyyyMMddHH"),"yyyyMMddHH");
    if(AHQC::FileNameUtil::validateZFileExistsByDT(lastSendHour))
        lastSendHour = lastSendHour.addSecs(-60*60);
    if(endDateTiem > lastSendHour || beginDateTiem > lastSendHour){
        if(endDateTiem > lastSendHour){
            endDateTiem = lastSendHour;
        }
        if(beginDateTiem > lastSendHour){
            beginDateTiem = lastSendHour;
        }
        emit selectRangeAutoChanged(beginDateTiem,endDateTiem);
    }
    if(beginDateTiem.addDays(3) <= endDateTiem){
        beginDateTiem = endDateTiem.addSecs(-60*60*72);
    }
    emit selectRangeAutoChanged(beginDateTiem,endDateTiem);
    reachDataThreadInstance->setTimeRange(TimeRange(beginDateTiem,endDateTiem,BEGINEND));
    reachDataThreadInstance->start();
//    updatePagesByTimeranng(TimeRange(beginDateTiem,endDateTiem,BEGINEND));
}
void MainWindow::sltSelectOver(bool){
    pageWidget->updateAfterPageChange();
    ui->refreshBtn->setEnabled(true);
    ui->selectedDateTimeRangeLabel->setEnabled(true);
    ui -> mainWidget->setCurrentIndex(ui -> mainWidget->count()-1);
    pageWidget->select(static_cast<FullWidegt *>(ui -> mainWidget->currentWidget())->getObserveTime());
    pageWidget->setEnabled(true);
}
void MainWindow::sltSelectRangeAutoChanged(const QDateTime &older, const QDateTime &later){
    ui->selectedDateTimeRangeLabel->setText(older.toString("yyyy-MM-dd HH")
                                            +" ～ "+
                                            later.toString("yyyy-MM-dd HH"));
}
void MainWindow::sltPageNumChanged(const QDateTime &dateTime){
    pageWidget->setDisabled(true);
    if(dateTime == currentRange->second){
        QDateTime observeTime = currentRange->second;
        fullWidgetRight->initFromAZData(azDatas->value(observeTime));
        observeTime  = observeTime.addSecs(-60*60);
        if(observeTime >= currentRange->first){
            fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
        }
        observeTime  = observeTime.addSecs(-60*60);
        if(observeTime >= currentRange->first){
            fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
        }
        ui->mainWidget->setCurrentIndex(2);
    }else if(dateTime == currentRange->first){
        QDateTime observeTime = currentRange -> first;
        fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
        observeTime  = observeTime.addSecs(60*60);
        if(observeTime <= currentRange->second){
            fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
        }
        observeTime  = observeTime.addSecs(60*60);
        if(observeTime <= currentRange->second){
            fullWidgetRight->initFromAZData(azDatas->value(observeTime));
        }
        ui->mainWidget->setCurrentIndex(0);
    }else{
        QDateTime observeTime = dateTime;
        fullWidgetMiddle ->initFromAZData(azDatas->value(observeTime));
        observeTime  = dateTime.addSecs(-60*60);
        fullWidgetLeft ->initFromAZData(azDatas->value(observeTime));
        observeTime  = dateTime.addSecs(60*60);
        fullWidgetRight -> initFromAZData(azDatas->value(observeTime));
        ui->mainWidget->setCurrentWidget(fullWidgetMiddle);
    }
    ui->mainWidget->update();
    pageWidget->setEnabled(true);
}
void MainWindow::sltReachDataFinish(const QDateTime &older, const QDateTime &later){
    mainWidgetChanging = true;
    checkAZDatas();
    QDateTime observeTime = later;
    fullWidgetRight ->initFromAZData(azDatas->value(observeTime));
    observeTime  = observeTime.addSecs(-60*60);
    if(observeTime >= older){
        fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
    }
    observeTime  = observeTime.addSecs(-60*60);
    if(observeTime >= older){
        fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
    }
    ui->mainWidget->setCurrentIndex(2);
    currentRange -> first = older;
    currentRange -> second = later;
    pageWidget -> range = currentRange;
    pageWidget -> updateAfterPageChange();
    pageWidget ->select(later);
    ui->refreshBtn->setEnabled(true);
    ui->selectedDateTimeRangeLabel->setEnabled(true);
    pageWidget->setEnabled(true);
    mainWidgetChanging = false;
}
void MainWindow::sltMainWidgetAnimationFinished(int olderIndex,int currentIndex){
    mainWidgetChanging = true;
    FullWidegt *currentWidget =  static_cast<FullWidegt *>(ui -> mainWidget->currentWidget());
    FullWidegt *otherWidget =  static_cast<FullWidegt *>(ui -> mainWidget->widget(olderIndex));
    if(olderIndex > currentIndex){
        if(currentWidget -> getObserveTime() == currentRange->first
                ||otherWidget->getObserveTime() == currentRange->second){
        }else{
            fullWidgetRight = static_cast<FullWidegt *>(ui -> mainWidget-> widget(currentIndex+2));
            fullWidgetRight -> initFromAZData(azDatas->value(currentWidget->getObserveTime().addSecs(-60*60)));
            ui->mainWidget->removeWidget(fullWidgetRight);
            ui->mainWidget->insertWidget(0,fullWidgetRight);
            fullWidgetLeft = fullWidgetRight;
            fullWidgetMiddle = currentWidget;
            fullWidgetRight = static_cast<FullWidegt *>(ui -> mainWidget-> widget(ui->mainWidget->currentIndex()+1));
        }

    }else{
        if(currentWidget -> getObserveTime() == currentRange->second
                ||otherWidget->getObserveTime() == currentRange->first){
        }else{
            fullWidgetLeft = static_cast<FullWidegt *>(ui -> mainWidget-> widget(currentIndex-2));
            fullWidgetLeft -> initFromAZData(azDatas->value(currentWidget->getObserveTime().addSecs(60*60)));
            ui->mainWidget->removeWidget(fullWidgetLeft);
            ui->mainWidget->insertWidget(2,fullWidgetLeft);
            fullWidgetRight = fullWidgetLeft;
            fullWidgetMiddle = currentWidget;
            fullWidgetLeft = static_cast<FullWidegt *>(ui -> mainWidget-> widget(ui->mainWidget->currentIndex()-1));
        }

    }
    mainWidgetChanging = false;
    pageWidget->select(currentWidget->getObserveTime());
    pageWidget->setEnabled(true);
}
void MainWindow::sltQCItemsChanged(){
    GlobalSetting *setting = GlobalSetting::getInstance();
    bool shallowTemperature_cb_check_setting = setting->value("shallowTemperature_cb_check").toBool();
    bool e_cb_check_setting = setting->value("e_cb_check").toBool();
    bool cloud_cb_check_setting = setting->value("cloud_cb_check").toBool();
    bool wd_cb_check_setting = setting->value("wd_cb_check").toBool();
    bool extremum12_cb_check_setting = setting->value("extremum12_cb_check").toBool();

    QList<QString> itemNames4Hide = QList<QString>();
    QList<QString> itemNames4Show = QList<QString>();
    QList<QString> dlNames4Check = QList<QString>();
    QList<QString> dlNames4UnCheck = QList<QString>();
    QList<QString> awsItemNeednessQC = QList<QString>();
    QList<QString> awsItemNeedQC = QList<QString>();
    if(shallowTemperature_cb_check_setting == true){
        QList<QString> itemNames =  {"ET40_label","ET40_DL",
                                      "ET80_label","ET80_DL",
                                      "ET160_label","ET160_DL",
                                      "ET320_label","ET320_DL"
                                     };
        QList<QString> dlNames = {"ET40_DL","ET80_DL","ET160_DL","ET320_DL"};
        QList<QString> awsItemNames = {"ET40","ET80","ET160","ET320"};

        itemNames4Hide.append(itemNames);
        dlNames4Check.append(dlNames);
        awsItemNeednessQC.append(awsItemNames);


    }else{
        QList<QString> itemNames =  {"ET40_label","ET40_DL",
                                      "ET80_label","ET80_DL",
                                      "ET160_label","ET160_DL",
                                      "ET320_label","ET320_DL"
                                     };
        QList<QString> dlNames = {"ET40_DL","ET80_DL","ET160_DL","ET320_DL"};
        QList<QString> awsItemNames = {"ET40","ET80","ET160","ET320"};

        itemNames4Show.append(itemNames);
        dlNames4UnCheck.append(dlNames);
        awsItemNeedQC.append(awsItemNames);

    }
    if(e_cb_check_setting == true){
        itemNames4Hide.append("E_label");itemNames4Hide.append("E_DL");
        dlNames4Check.append("E_DL");
        awsItemNeednessQC.append("E");

    }else{
        itemNames4Show.append("E_label");itemNames4Show.append("E_DL");
        dlNames4UnCheck.append("E_DL");
        awsItemNeedQC.append("E");
    }
    if(cloud_cb_check_setting == true){
        QList<QString> dlNames = {"CA_DL","LCA_DL","CH_DL","RCA_DL","CFC_DL"};
        QList<QString> awsItemNames = {"CA","LCA","CH","RCA","CFC"};
        itemNames4Hide.append("Cloud_GB");
        dlNames4Check.append(dlNames);
        awsItemNeednessQC.append(awsItemNames);

    }else{
        QList<QString> dlNames = {"CA_DL","LCA_DL","CH_DL","RCA_DL","CFC_DL"};
        QList<QString> awsItemNames = {"CA","LCA","CH","RCA","CFC"};
        itemNames4Show.append("Cloud_GB");
        dlNames4UnCheck.append(dlNames);
        awsItemNeedQC.append(awsItemNames);
    }
    if(wd_cb_check_setting == true){
        QList<QString> itemNames =  {"wdTitle_label","WD_DL",
                                      "WD2_DL","WD10_DL",
                                      "MaxWD_DL","ExWD_DL",
                                      "ExWD6_DL","ExWD12_DL"
                                     };
         QList<QString> dlNames = { "WD_DL",
                                    "WD2_DL","WD10_DL",
                                    "MaxWD_DL","ExWD_DL",
                                    "ExWD6_DL","ExWD12_DL"
                                   };
         QList<QString> awsItemNames = {"WD","WD2","WD10","MaxWD","ExWD","ExWD6","ExWD12"};
         itemNames4Hide.append(itemNames);
         dlNames4Check.append(dlNames);
         awsItemNeednessQC.append(awsItemNames);
    }else{
        QList<QString> itemNames =  {"wdTitle_label","WD_DL",
                                      "WD2_DL","WD10_DL",
                                      "MaxWD_DL","ExWD_DL",
                                      "ExWD6_DL","ExWD12_DL"
                                     };
        QList<QString> dlNames = { "WD_DL",
                                   "WD2_DL","WD10_DL",
                                   "MaxWD_DL","ExWD_DL",
                                   "ExWD6_DL","ExWD12_DL"
                                  };
        QList<QString> awsItemNames = {"WD","WD2","WD10","MaxWD","ExWD","ExWD6","ExWD12"};
        itemNames4Show.append(itemNames);
        dlNames4UnCheck.append(dlNames);
        awsItemNeedQC.append(awsItemNames);

    }
    if(extremum12_cb_check_setting == true){
        QList<QString> itemNames =  {"MaxT24_label","MaxT24_DL",
                                      "MinT24_label","MinT24_DL",
                                      "MinET12_label","MinET12_DL"
                                     };
         QList<QString> dlNames = { "MaxT24_DL","MinT24_DL","MinET12_DL"};
         QList<QString> awsItemNames = {"MaxT24","MinT24","MinET12"};
         itemNames4Hide.append(itemNames);
         dlNames4Check.append(dlNames);
         awsItemNeednessQC.append(awsItemNames);

    }else{
        QList<QString> itemNames =  {"MaxT24_label","MaxT24_DL",
                                      "MinT24_label","MinT24_DL",
                                      "MinET12_label","MinET12_DL"
                                    };
        QList<QString> dlNames = {"MaxT24_DL","MinT24_DL","MinET12_DL"};
        QList<QString> awsItemNames = {"MaxT24","MinT24","MinET12"};
        itemNames4Show.append(itemNames);
        dlNames4UnCheck.append(dlNames);
        awsItemNeedQC.append(awsItemNames);
    }


    fullWidgetLeft->hideItems(itemNames4Hide);
    fullWidgetLeft->showItems(itemNames4Show);
    fullWidgetLeft->setItemsChecked(dlNames4Check);
    fullWidgetLeft->setItemsUnChecked(dlNames4UnCheck);

    fullWidgetMiddle->hideItems(itemNames4Hide);
    fullWidgetMiddle->showItems(itemNames4Show);
    fullWidgetMiddle->setItemsChecked(dlNames4Check);
    fullWidgetMiddle->setItemsUnChecked(dlNames4UnCheck);

    fullWidgetRight->hideItems(itemNames4Hide);
    fullWidgetRight->showItems(itemNames4Show);
    fullWidgetRight->setItemsChecked(dlNames4Check);
    fullWidgetRight->setItemsUnChecked(dlNames4UnCheck);

    ui->packingOfMainWidget->update();


    for(const QString &itemName : awsItemNeedQC){
        if(!AHQC::QCItemNames.contains(itemName)){
            AHQC::QCItemNames.append(itemName);
        }
    }
    for(const QString &itemName : awsItemNeednessQC){
        AHQC::QCItemNames.removeAll(itemName);
    }

    checkAZDatas();
    pageWidget->updateAfterPageChange();
}
void MainWindow::sltDBOpenFailedWhenRefreach(bool){
    ui->refreshBtn->setEnabled(true);
    ui->selectedDateTimeRangeLabel->setEnabled(true);
}
void MainWindow::closeEvent(QCloseEvent *event){
    settingWidget->close();
    delete settingWidget;
    settingWidget = Q_NULLPTR;
    event->accept();
}


ReachDataThread::ReachDataThread(TimeRange timerange,MainWindow *mWindow,QObject *parent):
    QThread(parent),
    mainWindow(mWindow),
    timeRange(timerange)
{}

void ReachDataThread::run(){
    mainWindow->reachDataByTimerange(timeRange);

}

TimeRange ReachDataThread::getTimeRange() const
{
    return timeRange;
}

void ReachDataThread::setTimeRange(const TimeRange &value)
{
    timeRange = value;
}
