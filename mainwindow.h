#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QRegExp>
#include <QDesktopWidget>
#include <QIcon>
//#include <QVBoxLayout>
#include "ui/clickablelabel.h"
#include "test/testreadxmldata.h"
#include "test/simpletest.h"
#include "test/qtfeaturetest.h"
#include "awsminutedaomysqlimp.h"
#include "zdatadaomysqlimp.h"
#include "dbcenter.h"
#include "fullwidegt.h"
#include "azdata.h"
#include "horizontaltree.h"
#include "simpleobject.h"
#include "animationstackedwidget.h"
#include "settingwidget.h"
#include "ui/datetimedialog.h"
#include "ui/datetimepagenumberwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
#define PADDING 24
enum Direction { UP=0, DOWN=1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
    void reachDataByTimerange(const TimeRange &selectTimeRange);
    void updatePagesByTimeranng(const TimeRange &selectTimeRange);
    void reOrientateTurnPageBtn();
signals:
    void selectRangeAutoChanged(QPair<QDateTime,QDateTime>);
    void selectOver(bool);
public slots:
    void sltPreviousBtnClicled();
    void sltNextBtnClicled();
    void sltCloseBtnClicked(bool);
    void sltMinBtnClicked(bool);
    void sltMaxBtnClicked(bool);
    void sltShowMoreBtnClicked(bool);
    void sltQCColorChanged(QColor,QString);
    void sltSelectedDateTimeRangeLabelClicked(ClickableLabel *);
    void sltSelectDateTimeRangeChanged(QString);
    void sltRefreshBtnClicked(bool);
    void sltSelectOver(bool);
    void sltSelectRangeAutoChanged(const QPair<QDateTime,QDateTime> &DTPair);
    void sltPageNumChanged(const QDateTime &);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *ev);
protected :
    void resizeEvent(QResizeEvent *event);


private:    
    void region(const QPoint &cursorGlobalPoint);
    Ui::MainWindow *ui;
    void initComponents();
    void initStyleSheet();
    SettingWidget *settingWidget = Q_NULLPTR;
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

    QList<FullWidegt *> inRangePages;
    QPair<QDateTime,QDateTime> *currentRange;
    QMap<QDateTime,AZData> *azDatas;
    QMap<QDateTime,QPair<QString,MyDoubleLabel::Level> > *issueDatas;
};

class ReachDataThread : public QThread
{
    Q_OBJECT
public:
    explicit ReachDataThread(TimeRange timerange,MainWindow *mWindow = nullptr,QObject *parent = nullptr);

signals:

public slots:
private slots:
    void run();
private:
    MainWindow *mainWindow;
    TimeRange timeRange;
};

#endif // MAINWINDOW_H
