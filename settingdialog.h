#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
#include <QRegExp>
#include <QGraphicsDropShadowEffect>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QAbstractButton>
#include <QFile>
#include <QFileDialog>
#include <QListWidget>
#include "nofocusframedelegate.h"
#include "ahqlistwidgetitem.h"
#include "globalseeting.h"
#include <QRegExp>
#include <QStyledItemDelegate>
#include <QColorDialog>
#include <QMessageBox>
namespace Ui {
class SettingWidget;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:

    QPoint mousePoint;            //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;            //鼠标是否按下
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
public slots:
    void sltTreeWidget_itemExpanded(QTreeWidgetItem *item);
    void sltTreeWidget_itemPressed(QTreeWidgetItem * item,int column);
    void sltCloseButtonClicked(bool checked);
    void sltMinButtonClicked(bool checked);
    void sltNavigation_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void sltPathSwitchButtonToggled(QAbstractButton *button, bool checked);
    void sltFilesysAccountCheckBoxStateChanged(int state);
    void sltIsospathChangeButtonClicked(bool checked = false);
    void sltIsospathLineEditTextChanged();
    void sltColorBtnClicled(bool);

    void sltAnySettingChanged();

    void sltConfrimButtonClicked(bool);
    void sltCancelButtonClicked(bool);
    void sltApplyButtonClicked(bool);
signals:
    void QCColorChanged(QString missColor,QString suspectColor,QString errorColor);
    void QCColrConfirmChanged();
    void QCItemsChanged();
protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
private:

    void initPages();
    void connectSingles();
    void validateUISetting(bool forConfirm);
    void validateDBSetting(bool forConfirm);
    void validateFilesysSetting(bool forConfirm);
    void validateStationSetting(bool forConfirm);
    void validateCatchSetting(bool forConfirm);


    void connectUISettingPageSingles();
    void connectFilePathSettingPageSingles();
    void connectDBSettingPageSingles();
    void connectStationSettingPageSingles();
    void connectCacheSettingPageSingles();
    GlobalSetting *setting;
    Ui::SettingWidget *ui;
    QMessageBox *message_cd;
    void navigationTreeIndent();
    static QRegExp colorStringReg;
};

#endif // SETTINGWIDGET_H
