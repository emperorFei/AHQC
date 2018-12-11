#ifndef DATETIMEDIALOG_H
#define DATETIMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include "clickablelabel.h"
#include "calendarwidget.h"
#include "datetimerangeselectdialog.h"
class DateTimeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DateTimeDialog(QWidget *parent = nullptr);
    ~DateTimeDialog();
    void updateDialog();

    int getMarginLeft() const;
    void setMarginLeft(int value);

    int getMarginRight() const;
    void setMarginRight(int value);

    int getMarginTop() const;
    void setMarginTop(int value);

    int getMarginBottom() const;
    void setMarginBottom(int value);

    QString getRangeOfTimeString() const;
    void setRangeOfTimeString(const QString &value);

signals:
    void selectDateTimeRangeChanged(QString);
public slots:
    void sltDayLabelClicked(ClickableLabel *);
    void sltCloseBtnClicked(bool);
    void sltConfirmBtnClicked(bool);
    void sltDateTimeLabelClicked(ClickableLabel *);
    void sltSelectedDateTimeChanged(const QDateTime &,const QDateTime &);
private:
    void initWidgets();
    void initStyleSheet();
    void updateWidgets();
    void updateDayLabels();
    void updateDateTimeDialog();
    void updateDateTimeLabel();

    QDate dateTime2AWSDay(const QDateTime &dateTime);
    inline QPair<QDateTime,QDateTime> awsHourRangeOfDate(const QDate &);
private:
    QWidget *bgWidget;
    QVBoxLayout *layout_bg;
    QPushButton *closeBtn;
    ClickableLabel *dateTimeLabel;
    QPushButton *confirmBtn;
    QList<ClickableLabel *> dayLabels;
    QList<QString> dateLabel_rangeStrings;
    DateTimeRangeSelectDialog *dateTimeRangeSelectDialog;

    int marginLeft;
    int marginRight;
    int marginTop;
    int marginBottom;
    QString rangeOfTimeString;
    static QTime dayDemarcationTime;
};

#endif // DATETIMEDIALOG_H
