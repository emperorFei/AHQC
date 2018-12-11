#ifndef DAYLABEL_H
#define DAYLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QDate>
#include <QDebug>
class DayLabel : public QLabel
{
    Q_OBJECT
public:
typedef enum {
    PREV_MONTH_DAY,     // 上月剩余天数
    NEXT_MONTH_DAY,     // 下个月的天数
    CURR_MONTH_DAY,     // 当月天数
    WEEKEND_DAY,        // 周末
    CURRENT_DAY,        // 当天
}E_DAY;

public:
    explicit DayLabel(QWidget *parent = nullptr);

    void showDay(int nDay);
    QString text() const;
    E_DAY getType() const;
    void setType(const E_DAY &type);
    QDate getDate() const;
    void setDate(const QDate &value);

    bool getInRange() const;
    void setInRange(bool inRange);
    bool getInErrorRange() const;
    void setInErrorRange(bool inErrorRange);
    bool getBSelect() const;
    void setSelected(bool value);
    bool getBHover() const;
    void setBHover(bool bHover);

public slots:
    void setText(const QString &);
signals:
    void signalClicked(QDate,int ntype);
    void signalRightButtonClicked(bool);
protected:
    E_DAY m_type = CURR_MONTH_DAY;
    QString m_strText;
    int m_nDay;
    bool m_inErrorRange = false;
    bool m_inRange = false;
    bool m_bHover = false;
    bool m_bSelect = false;
    QColor selectedBG = QColor(18,132,231);
    QColor inRangeAndHoverBG = QColor(220,248,255);
    QColor inErrorRangBG = QColor(243,243,243);
    QColor normalBG = QColor("#FFFFFF");
    QColor selectedPenColor = QColor("#FFFFFF");
    QColor normalPenColor = QColor("#000000");
    QColor errorRangePenColor = QColor(204,204,204);
private:
    QDate date = QDate::fromString("19700101","yyyyMMdd");
    QCursor forbidCursor;
protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent* e);
};

#endif // DAYLABEL_H
