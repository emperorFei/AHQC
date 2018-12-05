#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QTimer>
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
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updatePagesByTimeranng(const TimeRange &selectTimeRange);
    void reOrientateTurnPageBtn();
public slots:
    void whenPreviousBtnClicled();
    void whenNextBtnClicled();
protected :
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
    void initComponents();
};

#endif // MAINWINDOW_H
