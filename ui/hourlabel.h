#ifndef HOURLABEL_H
#define HOURLABEL_H
#include <QObject>
#include <QDateTime>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QCursor>
class HourLabel : public QLabel
{
    Q_OBJECT
public:
    typedef enum {
        PREV_DAY_HOUR,     // 上一天的小时
        NEXT_DAY_HOUR,     // 下一天的小时
        CURR_DAY_HOUR,     // 当天的小时
        CURRENT_HOUR,        // 当前小时
    }E_HOUR;
public:
    explicit HourLabel(QWidget *parent = nullptr);
    ~HourLabel();

    void showDay(int nDay);
    void showHour(int hour);

    QString text() const;
    E_HOUR getType() const;
    void setType(const E_HOUR &type);
    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);
    bool getInRange() const;
    void setInRange(bool inRange);
    bool getInErrorRange() const;
    void setInErrorRange(bool inErrorRange);
    bool getBSelect() const;
    void setSelected(bool value);

public slots:
    void setText(const QString &);
protected:
    bool m_inRange = false;
    bool m_inErrorRange = false;
    bool m_bHover = false;
    bool m_bSelect = false;
    E_HOUR m_type = CURR_DAY_HOUR;
    QString m_strText;
    QColor selectedBG = QColor(18,132,231);
    QColor inRangeAndHoverBG = QColor(220,248,255);
    QColor inErrorRangBG = QColor(243,243,243);
    QColor normalBG = QColor("#FFFFFF");
    QColor selectedPenColor = QColor("#FFFFFF");
    QColor normalPenColor = QColor("#000000");
    QColor errorRangePenColor = QColor(204,204,204);
signals:
    void signalRightButtonClicked(bool);
    void signalClicked(QDateTime dateTime,E_HOUR type);
private:
    int m_nDay;
    int m_hour;
    QDateTime dateTime;
    QCursor forbidCursor;
protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent* e);
};

#endif // HOURLABEL_H
