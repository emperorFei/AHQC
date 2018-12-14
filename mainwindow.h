#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QRegExp>
#include <QDesktopWidget>
#include <QIcon>
#include <QThread>
//#include <QVBoxLayout>
#include "ui/clickablelabel.h"
#include "awsminutedaomysqlimp.h"
#include "zdatadaomysqlimp.h"
#include "dbcenter.h"
#include "fullwidegt.h"
#include "azdata.h"
#include "horizontaltree.h"
#include "simpleobject.h"
#include "animationstackedwidget.h"
#include "settingdialog.h"
#include "ui/datetimedialog.h"
#include "ui/datetimepagenumberwidget.h"

namespace Ui {
class MainWindow;
}
class ReachDataThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT
#define PADDING 24
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
    void startReachDataByTimerange(const TimeRange &selectTimeRange);
    void reachDataByTimerange(const TimeRange &selectTimeRange);
    void reOrientateTurnPageBtn();
signals:
    void selectRangeAutoChanged(QDateTime older,QDateTime later);
    void selectOver(bool);
    void dbOpenFailed(bool);
    void reachDataFinish(QDateTime older,QDateTime later);
public slots:
    void sltPreviousBtnClicled();
    void sltNextBtnClicled();
    void sltCloseBtnClicked(bool);
    void sltMinBtnClicked(bool);
    void sltMaxBtnClicked(bool);
    void sltShowMoreBtnClicked(bool);
    void sltDBOpenFailedWhenRefreach(bool);
    void sltQCColorChanged(const QString&,const QString&,const QString&);
    void sltSelectedDateTimeRangeLabelClicked(ClickableLabel *);
    void sltSelectDateTimeRangeChanged(QString);
    void sltRefreshBtnClicked(bool);
    void sltSelectOver(bool);
    void sltSelectRangeAutoChanged(const QDateTime &older,const QDateTime &later);
    void sltPageNumChanged(const QDateTime &);
    void sltReachDataFinish(const QDateTime &older,const QDateTime &later);
    void sltMainWidgetAnimationFinished(int,int);
    void sltQCItemsChanged();

    void refreshMainWidgetStyleSheet();

protected :
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void checkAZDatas();
    void region(const QPoint &cursorGlobalPoint);
    Ui::MainWindow *ui;
    void initComponents();

    SettingDialog *settingWidget = Q_NULLPTR;
    DateTimePageNumberWidget *pageWidget;
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;   // 窗口移动拖动时需要记住的点
    Direction dir;        // 窗口大小改变时，记录改变方向
    QPoint mousePoint;            //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;            //鼠标是否按下
    bool maxSizeHint = false;
    DateTimeDialog *dateTimeSelectDialog;
    QRect deskRect;
    QRect bestRect;
    int marginPix;
    bool mainWidgetChanging;
    FullWidegt *fullWidgetLeft;
    FullWidegt *fullWidgetMiddle;
    FullWidegt *fullWidgetRight;
    QPair<QDateTime,QDateTime> *currentRange;
    QMap<QDateTime,AZData> *azDatas;
    QMap<QDateTime,QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > > *issueDatas;
    ReachDataThread *reachDataThreadInstance;
    static QString mainWidgetStyleTemplate;
};

class ReachDataThread : public QThread
{
    Q_OBJECT
public:
    explicit ReachDataThread(TimeRange timerange,MainWindow *mWindow = nullptr,QObject *parent = nullptr);

    TimeRange getTimeRange() const;
    void setTimeRange(const TimeRange &value);

signals:

public slots:
private slots:
    void run();
private:
    MainWindow *mainWindow;
    TimeRange timeRange;
};

#endif // MAINWINDOW_H
