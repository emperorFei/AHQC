#ifndef DATETIMEPAGENUMBERWIDGET_H
#define DATETIMEPAGENUMBERWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStyleOption>
#include "signeddaylabel.h"
#include "signedhourlabel.h"
#include "mydoublelabel.h"
#include <QDebug>

class DateTimePageNumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePageNumberWidget(QWidget *parent = nullptr);
    void updateAfterPageChange();
    void select(const QDateTime &);

    const QMap<QDateTime,QPair<QString,MyDoubleLabel::Level> > * issueDatas;
    const QPair<QDateTime,QDateTime> *range;
signals:
    void selectedDateTimeChanged(QDateTime);
public slots:
    void sltDayLabelClicked(const QDate&);
    void sltHourLabelClicked(const QDateTime&);
protected:
    void paintEvent(QPaintEvent *);
private:
    void initWidgets();
    void initDayWidget();
    void initHourWidget();
    void initStyleSheet();
    inline void updateWidgets();
    void updateDayWidget();
    void updateHourWidget();
private:
    SignedDayLabel *dayLabelSelected;
    SignedHourLabel *hourLabelSelected;
    QList<SignedHourLabel *>hourLabels;
    QList<SignedDayLabel *>dayLabels;
    QWidget *dayWidget;
    QWidget *hourWidget;
    static QTime zeroHour;
    static QTime lastHour;
};

#endif // DATETIMEPAGENUMBERWIDGET_H
