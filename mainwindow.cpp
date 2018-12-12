#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fullWidgetLeft(Q_NULLPTR),
    fullWidgetMiddle(Q_NULLPTR),
    fullWidgetRight(Q_NULLPTR),
    inRangePages(QList<FullWidegt*>()),
    currentRange(Q_NULLPTR),
    azDatas(Q_NULLPTR),
    issueDatas(Q_NULLPTR)
{
//    TestReadXmlData tReadXml;
//    SimpleTest simpleTest;
////    QtFeatureTest qtFeatureTest;
////    QTest::qExec(&qtFeatureTest);
////    QTest::qExec(&tReadXml);
//    QTest::qExec(&simpleTest);
    ui->setupUi(this);
    issueDatas = new QMap<QDateTime,QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > >();
    this->setWindowIcon(QIcon(":/ico/qc"));
    initComponents();
    QDateTime beginTime(QDate(2018,12,5),QTime(00,00));
    QDateTime endTime(QDate(2018,12,5),QTime(10,00));
    QTimer::singleShot(5000,[=](){updatePagesByTimeranng(TimeRange(beginTime,endTime,timeRange_bound::BEGINEND));});
    QFont font("宋体");
    font.setPointSize(10);
    ui -> mainWidget->setFont(font);


//    QDateTime observeTime = QDateTime::fromString("20181002210000","yyyyMMddHHmmss");
//    AWSMinuteDAOMySqlImp awsMinuteDao(database);
//    AWSMinuteData amData = awsMinuteDao.findByOT(observeTime);
//    QMap<QString,int> stastictsData = awsMinuteDao.getExtremums(observeTime);
//    stastictsData.unite(awsMinuteDao.getVAndRain(observeTime));
//    AHData ahData(amData,stastictsData);
//    ZDataDAOMysqlImp zDao(database);
//    ZData zData(zDao.checkSaveAndFindByOT(observeTime));
//    AZData azData(ahData,zData);
//    FullWidegt * fullWidget = new FullWidegt(azData);
//    ui -> mainWidget->insertWidget(0,fullWidget);

    ui -> mainWidget->setCurrentIndex(0);



    //HorizontalTree *hTree = new HorizontalTree(this);

    reOrientateTurnPageBtn();

    QTimer::singleShot(0,[=](){
        this->setGeometry(bestRect);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentRange;
    delete issueDatas;
    DBCenter::cleanCreatedConns();
}

void MainWindow::reachDataByTimerange(const TimeRange &selectTimeRange){
    QSqlDatabase * database = DBCenter::getDBByAccountType(DBCenter::AccountType::QIU);
    if(!database->open()){
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
}

void MainWindow::updatePagesByTimeranng(const TimeRange &selectTimeRange){
//    if(currentRange != Q_NULLPTR){
//        delete currentRange;
//        currentRange = Q_NULLPTR;
//    }
//    issueDatas -> clear();
//    inRangePages.clear();
//    currentRange = new QPair<QDateTime,QDateTime>(selectTimeRange.older,selectTimeRange.later);
//    pageWidget -> range = currentRange;
//    QSqlDatabase * database = DBCenter::getDBByAccountType(DBCenter::AccountType::QIU);
//    database->open();
//    QFont font = ui -> mainWidget->font();
//    AWSMinuteDAOMySqlImp awsMinuteDao(database);
//    ZDataDAOMysqlImp zDao(database);
//    QList<QString> amFileNames4Save = AHQC::FileNameUtil::prepareAMFile4Select(selectTimeRange);
//    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(selectTimeRange);
//    for(const QString &filename: amFileNames4Save){
//        awsMinuteDao.saveAMFile(filename);
//    }

//    qDebug() << "now adding";

//    int insertIndex = -1;
//    for(const QDateTime &observeTime : focusedHours){
//        AWSMinuteData amData = awsMinuteDao.findByOT(observeTime);
//        QMap<QString,int> stastictsData = awsMinuteDao.getExtremums(observeTime);
//        stastictsData.unite(awsMinuteDao.getVAndRain(observeTime));
//        AHData ahData(amData,stastictsData);
//        ZData zData(zDao.checkSaveAndFindByOT(observeTime));
//        AZData azData(ahData,zData);
//        FullWidegt * fullWidget = new FullWidegt(azData,ui -> mainWidget);
//        fullWidget->setMouseTracking(true);
//        fullWidget->setDoubleLabelFont(font);
//        int insertedIndex =  ui -> mainWidget->insertWidget(++insertIndex,fullWidget);
////        pageCount = ui -> mainWidget->count();
//        qDebug() << "insertedIndex: " << insertedIndex;
////        qDebug() << "count: " << pageCount;
//        if(fullWidget->getMostSeriousIssue().second != 0){
//            //issueDatas->insert(fullWidget->getObserveTime(),fullWidget->getMostSeriousIssue());
//        }
//        inRangePages.append(fullWidget);
//    }
//    database->close();
//    int lastInsertIndex = insertIndex;
//    int lastIndex = ui -> mainWidget->count() -1;
//    while(lastIndex > lastInsertIndex){
//        QWidget *widget = ui -> mainWidget->widget(lastIndex);
//        ui -> mainWidget->removeWidget(widget);
//        widget->deleteLater();
//        lastIndex = ui -> mainWidget->count() -1;
//    }
//    qDebug() << ui -> mainWidget->count();
//    emit selectOver(true);

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
    settingWidget = new SettingWidget(this);

    FullWidegt *fullWidgetLeft = new FullWidegt(ui->mainWidget);
    FullWidegt *fullWidgetMiddle = new FullWidegt(ui->mainWidget);
    FullWidegt *fullWidgetRight = new FullWidegt(ui->mainWidget);

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

    settingWidget->hide();
    pageWidget = new DateTimePageNumberWidget(this);
    pageWidget -> issueDatas = this -> issueDatas;
    pageWidget -> range = this -> currentRange;
    ui->verticalLayout->insertWidget(2,pageWidget);
    initStyleSheet();

    connect(ui->previous_btn,&QPushButton::clicked,this,&MainWindow::sltPreviousBtnClicled);
    connect(ui->next_btn,&QPushButton::clicked,this,&MainWindow::sltNextBtnClicled);
    connect(ui->minButton,&QPushButton::clicked,this,&MainWindow::sltMinBtnClicked);
    connect(ui->maxButton,&QPushButton::clicked,this,&MainWindow::sltMaxBtnClicked);
    connect(ui->closeButton,&QPushButton::clicked,this,&MainWindow::sltCloseBtnClicked);
    connect(ui->showMoreButton,&QPushButton::clicked,this,&MainWindow::sltShowMoreBtnClicked);
    connect(ui->selectedDateTimeRangeLabel,&ClickableLabel::clicked,this,&MainWindow::sltSelectedDateTimeRangeLabelClicked);
    connect(settingWidget,&SettingWidget::QCColorChanged,this,&MainWindow::sltQCColorChanged);
    connect(dateTimeSelectDialog,&DateTimeDialog::selectDateTimeRangeChanged,this,&MainWindow::sltSelectDateTimeRangeChanged);
    connect(ui->refreshBtn,&QPushButton::clicked,this,&MainWindow::sltRefreshBtnClicked);
    connect(this,&MainWindow::selectRangeAutoChanged,this,&MainWindow::sltSelectRangeAutoChanged);
    connect(this,&MainWindow::selectOver,this,&MainWindow::sltSelectOver);
    connect(pageWidget,&DateTimePageNumberWidget::selectedDateTimeChanged,this,&MainWindow::sltPageNumChanged);
    pageWidget->setDisabled(true);
}
void MainWindow::initStyleSheet(){
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
//    qDebug() << "mouseMoveEvent :";
    if(!isLeftPressDown) {
//        qDebug() << "mouseMoveEvent : !isLeftPressDown";
        this->region(gloPoint);
    } else {
//        qDebug() << "mouseMoveEvent : pressDown";
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
//    QMap<QDateTime,AZData>::Iterator it =  (*azDatas).begin();
//    QMap<QDateTime,AZData>::Iterator end =  (*azDatas).end();
//    while(it != end){
//        AZData &theAZData = it.value();
//        QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >::Iterator itOfAZData =  it.value().data.begin();
//        QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >::Iterator endOfAZData =  it.value().data.end();
//        while(itOfAZData != endOfAZData){
//            if((itOfAZData.value().second != AHQC::DataLevel::INFO) &&
//                    theAZData.mostSeriousIssue.second.second < itOfAZData.value().second){
//                theAZData.mostSeriousIssue = *itOfAZData;
//            }
//        }
//        if(theAZData.mostSeriousIssue.first == "unchecked"){
//            theAZData.mostSeriousIssue.first = "noSuspectedData";
//        }else{
//           issueDatas->insert(theAZData.observeTime,theAZData.mostSeriousIssue);
//        }
//    }
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
    int currectIndex = ui -> mainWidget->currentIndex();
    if(currectIndex > 0){
        ui -> mainWidget->forward();
        pageWidget->select(static_cast<FullWidegt *>(ui -> mainWidget->currentWidget())->getObserveTime().addSecs(-60*60));
        pageWidget->setDisabled(true);
        QTimer::singleShot(1000,[=](){pageWidget->setEnabled(true);});
    }
}
void MainWindow::sltNextBtnClicled(){
    int currectIndex = ui -> mainWidget->currentIndex();
    FullWidegt * currentWidget = static_cast<FullWidegt *>(ui -> mainWidget->currentWidget());
    QDateTime currentDateTime = currentWidget->getObserveTime();
    if(currentDateTime == currentRange->second){
        return;
    }else if(currentDateTime == currentRange->second.addSecs(60*60)){
        fullWidgetRight->initFromAZData(azDatas->value(currentDateTime.addSecs(60*60)));
        fullWidgetMiddle->initFromAZData(azDatas->value(currentDateTime));
        if(currentDateTime.addSecs(-60*60) >= currentRange->first){
            fullWidgetLeft->initFromAZData(azDatas->value(currentDateTime.addSecs(-60*60)));
        }
        ui -> mainWidget -> next();
    }

    if(currectIndex < ui -> mainWidget->count() - 1){
        ui -> mainWidget->next();
        pageWidget->select(currentWidget->getObserveTime().addSecs(60*60));
        pageWidget->setDisabled(true);
        QTimer::singleShot(1000,[=](){pageWidget->setEnabled(true);});
    }

}
void MainWindow::sltQCColorChanged(QColor color,QString dataLevelName){
    static QRegExp doubleLabelStyleSheetReg_MISSING("\\.MyDoubleLabel\\[level = '3'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_ERROR("\\.MyDoubleLabel\\[level = '6'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_CLASH("\\.MyDoubleLabel\\[level = '2'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_MISSINGZDATA("\\.MyDoubleLabel\\[level = '4'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_MISSINGADATA("\\.MyDoubleLabel\\[level = '5'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_SUSPECTED("\\.MyDoubleLabel\\[level = '1'\\]\\{[^}]*\\}");
    static QRegExp doubleLabelStyleSheetReg_INFO("\\.MyDoubleLabel\\[level = '0'\\]\\{[^}]*\\}");

    QString newStyleSheet_INFO(".MyDoubleLabel[level = '0']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_SUSPECTED(".MyDoubleLabel[level = '1']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_CLASH(".MyDoubleLabel[level = '2']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_MISSING(".MyDoubleLabel[level = '3']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_MISSINGZDATA(".MyDoubleLabel[level = '4']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_MISSINGADATA(".MyDoubleLabel[level = '5']{\n\tborder-color:#{color};\n}");
    QString newStyleSheet_ERROR(".MyDoubleLabel[level = '6']{\n\tborder-color:#{color};\n}");

    QString styleSheetOfPackingOfMainWidget = ui->packingOfMainWidget->styleSheet();

    QString colorString("rgb("+
                        QString::number(color.red())+","+
                        QString::number(color.green())+","+
                        QString::number(color.blue())+")");
    if(dataLevelName == "missingColor_btn"){
        newStyleSheet_MISSING.replace("#{color}",colorString);
        newStyleSheet_MISSINGZDATA.replace("#{color}",colorString);
        newStyleSheet_MISSINGADATA.replace("#{color}",colorString);
        ui->packingOfMainWidget->setStyleSheet(
                    QString(styleSheetOfPackingOfMainWidget)
                        .replace(doubleLabelStyleSheetReg_MISSING,
                                 newStyleSheet_MISSING)
                        .replace(doubleLabelStyleSheetReg_MISSINGADATA,
                                 newStyleSheet_MISSINGADATA)
                        .replace(doubleLabelStyleSheetReg_MISSINGZDATA,
                                 newStyleSheet_MISSINGZDATA)
                        );
    }else if(dataLevelName == "errorColor_btn"){
        newStyleSheet_ERROR.replace("#{color}",colorString);
        ui->packingOfMainWidget->setStyleSheet(
                    QString(styleSheetOfPackingOfMainWidget)
                        .replace(doubleLabelStyleSheetReg_ERROR,
                                 newStyleSheet_ERROR));
    }else if(dataLevelName == "suspectedColor_btn"){
        newStyleSheet_SUSPECTED.replace("#{color}",colorString);
        newStyleSheet_CLASH.replace("#{color}",colorString);
        ui->packingOfMainWidget->setStyleSheet(
                    QString(styleSheetOfPackingOfMainWidget)
                        .replace(doubleLabelStyleSheetReg_CLASH,
                                 newStyleSheet_CLASH)
                        .replace(doubleLabelStyleSheetReg_SUSPECTED,
                                 newStyleSheet_SUSPECTED));
    }
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

        settingWidget->show();
    }else{
        settingWidget->hide();
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
        emit selectRangeAutoChanged(QPair<QDateTime,QDateTime>(beginDateTiem,endDateTiem));
    }
    updatePagesByTimeranng(TimeRange(beginDateTiem,endDateTiem,BEGINEND));
}
void MainWindow::sltSelectOver(bool){
    pageWidget->updateAfterPageChange();
    ui->refreshBtn->setEnabled(true);
    ui->selectedDateTimeRangeLabel->setEnabled(true);
    ui -> mainWidget->setCurrentIndex(ui -> mainWidget->count()-1);
    pageWidget->select(static_cast<FullWidegt *>(ui -> mainWidget->currentWidget())->getObserveTime());
    pageWidget->setEnabled(true);
}
void MainWindow::sltSelectRangeAutoChanged(const QPair<QDateTime,QDateTime> &DTPair){
    ui->selectedDateTimeRangeLabel->setText(DTPair.first.toString("yyyy-MM-dd HH")
                                            +" ～ "+
                                            DTPair.second.toString("yyyy-MM-dd HH"));
}
void MainWindow::sltPageNumChanged(const QDateTime &dateTime){
    if(dateTime == currentRange->second){
        QDateTime observeTime = currentRange->second;
        fullWidgetRight->initFromAZData(azDatas->value(observeTime));
        observeTime  = observeTime.addSecs(-60*60);
        if(observeTime >= currentRange->second){
            fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
        }
        observeTime  = observeTime.addSecs(-60*60);
        if(observeTime >= currentRange->second){
            fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
        }
        ui->mainWidget->setCurrentIndex(2);
    }else if(dateTime == currentRange->first){
        QDateTime observeTime = currentRange -> first;
        fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
        observeTime  = observeTime.addSecs(60*60);
        if(observeTime >= currentRange->second){
            fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
        }
        observeTime  = observeTime.addSecs(60*60);
        if(observeTime >= currentRange->second){
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
        ui->mainWidget->setCurrentIndex(1);
    }
}
void MainWindow::sltReachDataFinish(const TimeRange &timeRange){
    issueDatas -> clear();
    checkAZDatas();
    QDateTime observeTime = timeRange.later;
    fullWidgetRight->initFromAZData(azDatas->value(observeTime));
    observeTime  = observeTime.addSecs(-60*60);
    if(observeTime >= timeRange.older){
        fullWidgetMiddle->initFromAZData(azDatas->value(observeTime));
    }
    observeTime  = observeTime.addSecs(-60*60);
    if(observeTime >= timeRange.older){
        fullWidgetLeft->initFromAZData(azDatas->value(observeTime));
    }
    ui->mainWidget->setCurrentIndex(2);
    if(currentRange != Q_NULLPTR){
        delete currentRange;
        currentRange = Q_NULLPTR;
    }
    currentRange = new QPair<QDateTime,QDateTime> (timeRange.older,timeRange.later);
    pageWidget -> range = currentRange;
    pageWidget -> updateAfterPageChange();

}

ReachDataThread::ReachDataThread(TimeRange timerange,MainWindow *mWindow,QObject *parent):
    QThread(parent),
    mainWindow(mWindow),
    timeRange(timerange)
{

}

void ReachDataThread::run(){
    mainWindow->reachDataByTimerange(timeRange);
    emit reachDataFinish(timeRange);
}
