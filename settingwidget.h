#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QAbstractButton>
#include <QFile>
#include <QFileDialog>
#include <QListWidget>
#include "nofocusframedelegate.h"
#include "ahqcomboboxitem.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint mousePoint;            //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;            //鼠标是否按下
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();
public slots:
    void treeWidget_itemExpanded(QTreeWidgetItem *item);
    void treeWidget_itemPressed(QTreeWidgetItem * item,int column);
    void closeButtonClicked(bool checked);
    void minButtonClicked(bool checked);
    void navigation_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void pathSwitchButtonToggled(QAbstractButton *button, bool checked);
    void filesysAccountCheckBoxStateChanged(int state);
    void isospathChangeButtonClicked(bool checked = false);
private:


    void initComboBoxView();
    void connectSingles();


    void connectUISettingPageSingles();
    void connectFilePathSettingPageSingles();
    void connectDBSettingPageSingles();
    void connectStationSettingPageSingles();
    void connectCacheSettingPageSingles();

    Ui::SettingWidget *ui;
    void navigationTreeIndent();
};

#endif // SETTINGWIDGET_H
