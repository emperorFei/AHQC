#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    TestReadXmlData tReadXml;
//    SimpleTest simpleTest;
////    QtFeatureTest qtFeatureTest;
////    QTest::qExec(&qtFeatureTest);
////    QTest::qExec(&tReadXml);
//    QTest::qExec(&simpleTest);
    ui->setupUi(this);
    initComponents();
    QDateTime beginTime(ui->beginTime_CW->getDateTime());
    QDateTime endTime(ui->endTime_CW->getDateTime());
    updatePagesByTimeranng(TimeRange(beginTime,endTime,timeRange_bound::BEGINEND));
    QFont font("宋体");
    font.setPointSize(10);
    ui->mainWidget->setFont(font);


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
//    ui->mainWidget->insertWidget(0,fullWidget);

    ui->mainWidget->setCurrentIndex(0);



    //HorizontalTree *hTree = new HorizontalTree(this);

    reOrientateTurnPageBtn();

    QTimer::singleShot(0,[=](){
        //QRect geometry  = this->geometry();
        qDebug() << "initResize";
        this->resize(1280,740);
        qDebug() << "initResizeEnd";
    });
//    QRect geometry  = this->geometry();
//    QTimer::
//    this->resize(geometry.width(),geometry.height());
//    connect(ui->previousTime_btn,&QPushButton::clicked,this,&MainWindow::whenPreviousBtnClicled);
//    connect(ui->nextTime_btn,&QPushButton::clicked,this,&MainWindow::whenNextBtnClicled);
//    ui->treeWidget->
}

MainWindow::~MainWindow()
{
    delete ui;
    DBCenter::cleanCreatedConns();
}
void MainWindow::whenPreviousBtnClicled(){
    int currectIndex = ui->mainWidget->currentIndex();
    if(currectIndex > 0){
        ui->mainWidget->setCurrentIndex(currectIndex-1);
    }
}
void MainWindow::whenNextBtnClicled(){
    int currectIndex = ui->mainWidget->currentIndex();
    if(currectIndex < ui->mainWidget->count() - 1){
        ui->mainWidget->setCurrentIndex(currectIndex + 1);
    }
}
void MainWindow::updatePagesByTimeranng(const TimeRange &selectTimeRange){
    QSqlDatabase * database = DBCenter::getDBByAccountType(DBCenter::AccountType::QIU);
    database->open();
    QFont font = ui->mainWidget->font();
    AWSMinuteDAOMySqlImp awsMinuteDao(database);
    ZDataDAOMysqlImp zDao(database);
    QList<QString> amFileNames4Save = AHQC::FileNameUtil::prepareAMFile4Select(selectTimeRange);
    QList<QDateTime> focusedHours = AHQC::TimeUtil::getFocusedHours(selectTimeRange);
    for(const QString &filename: amFileNames4Save){
        awsMinuteDao.saveAMFile(filename);
    }
    int totalPage = focusedHours.length();
    int pageCount = ui->mainWidget->count();
    qDebug() << "totalPage: " << totalPage;
    qDebug() << "initpageCount: " << pageCount;
    if(pageCount > totalPage){
        int removedIndex = pageCount - 1;
        while(removedIndex >= totalPage){
            QWidget * widget = ui->mainWidget->widget(removedIndex);
            ui->mainWidget->removeWidget(widget);
            --removedIndex;
            pageCount = ui->mainWidget->count();
            qDebug() << "removedIndex: " << removedIndex <<" count: " << pageCount;
        }
    }
//    int index = -1;
     qDebug() << "now adding";
    for(const QDateTime &observeTime : focusedHours){
        AWSMinuteData amData = awsMinuteDao.findByOT(observeTime);
        QMap<QString,int> stastictsData = awsMinuteDao.getExtremums(observeTime);
        stastictsData.unite(awsMinuteDao.getVAndRain(observeTime));
        AHData ahData(amData,stastictsData);
        ZData zData(zDao.checkSaveAndFindByOT(observeTime));
        AZData azData(ahData,zData);
        FullWidegt * fullWidget = new FullWidegt(azData,ui->mainWidget);
        fullWidget->setDoubleLabelFont(font);
        int insertedIndex =  -1;
//        insertedIndex = ui->mainWidget->insertWidget(++index,fullWidget);
        insertedIndex = ui->mainWidget->addWidget(fullWidget);
        pageCount = ui->mainWidget->count();
        qDebug() << "insertedIndex: " << insertedIndex;
        qDebug() << "count: " << pageCount;
    }
    QWidget *widget0 = ui->mainWidget->widget(0);
    QWidget *widget1 = ui->mainWidget->widget(1);
    ui->mainWidget->removeWidget(widget0);
    ui->mainWidget->removeWidget(widget1);
    database->close();
}
void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    qDebug() << "in resizeEvent";
    reOrientateTurnPageBtn();
    qDebug() << "in resizeEventEnd";
}

void MainWindow::reOrientateTurnPageBtn(){
    qDebug() << "reOrientateTurnPageBtn";
    QRect rectOfMainWidget = ui->packingOfMainWidget->geometry();
    qDebug() << rectOfMainWidget;
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

    ui->mainWidget->setGeometry(rectOfMainWidget);
//    nextBtn->setStyleSheet("")
}
void MainWindow::initComponents(){
    QIcon iconOfNextBtn(":ico/btn_2Right");
    ui->next_btn->setText("");
    ui->next_btn->setIcon(iconOfNextBtn);
    ui->next_btn->setIconSize(QSize(20,20));
    QIcon iconOfPreviousBtn(":ico/btn_2Left");
    ui->previous_btn->setText("");
    ui->previous_btn->setIcon(iconOfPreviousBtn);
    ui->previous_btn->setIconSize(QSize(20,20));

    AnimationStackedWidget *animationStackedWidget = this->findChild<AnimationStackedWidget *>("mainWidget");
    connect(ui->previous_btn,&QPushButton::clicked,animationStackedWidget,&AnimationStackedWidget::forward);
    connect(ui->next_btn,&QPushButton::clicked,animationStackedWidget,&AnimationStackedWidget::next);

    QDateTime beginTime(QDate(2018,12,4),QTime(20,00));
    QDateTime endTime(QDate(2018,12,5),QTime(10,00));
    ui->beginTime_CW->setDateTime(beginTime);
    ui->endTime_CW->setDateTime(endTime);
    ui->beginTime_CW->connectToAnother(ui->endTime_CW);
    connect(ui->beginTime_CW,&CalendarWidget::selectDateTimeChanged,ui->beginTime_DTE,&QDateTimeEdit::setDateTime);
    connect(ui->endTime_CW,&CalendarWidget::selectDateTimeChanged,ui->endTime_DTE,&QDateTimeEdit::setDateTime);



}
