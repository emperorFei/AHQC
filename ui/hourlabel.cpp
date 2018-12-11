#include "hourlabel.h"

HourLabel::HourLabel(QWidget *parent) :
    QLabel(parent),m_nDay(0),m_hour(0),m_bHover(false),m_bSelect(false)
{
    forbidCursor = QCursor(QPixmap(":ico/forbid")
                           .scaled(25,25,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}
HourLabel::~HourLabel(){}

bool HourLabel::getBSelect() const {return m_bSelect;}
void HourLabel::setSelected(bool value)
{
    m_bSelect = value;
    update();
}
void HourLabel::showDay(int nDay)
{
    m_strText = QString::number(nDay);
    m_nDay = nDay;
}
void HourLabel::showHour(int nDay)
{
    m_strText = QString::number(nDay);
    m_nDay = nDay;
}

void HourLabel::enterEvent(QEvent *e)
{
    if(m_inErrorRange){
        setCursor(forbidCursor);
    }else{
        setCursor(Qt::PointingHandCursor);
        m_bHover = true;
        update();
    }
    QLabel::enterEvent(e);
}

void HourLabel::leaveEvent(QEvent *e)
{
    setCursor(Qt::ArrowCursor);
    m_bHover = false;
    update();
    QLabel::leaveEvent(e);
}

void HourLabel::mousePressEvent(QMouseEvent *e)
{
    if(m_inErrorRange){
        if(e->buttons() == Qt::RightButton){
            emit signalRightButtonClicked(true);
        }else{
          return;
        }
    }else{
        if(e->buttons() == Qt::RightButton){
            emit signalRightButtonClicked(true);
        }else{
            emit signalClicked(dateTime,m_type);
        }
    }
    QLabel::mousePressEvent(e);
}
void HourLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    if(!m_inErrorRange){
        if(m_bSelect){
            p.setBrush(QBrush(selectedBG));
            p.setPen(QPen(selectedBG, 1));
        }else if(m_inRange || m_bHover){
            p.setBrush(QBrush(inRangeAndHoverBG));
            p.setPen(QPen(inRangeAndHoverBG,1));
        }else{
            p.setBrush(QBrush(normalBG));
            p.setPen(QPen(normalBG,1));
        }
    }else{
        p.setBrush(QBrush(inErrorRangBG));
        p.setPen(QPen(inErrorRangBG,1));
    }
    p.drawRect(rect());

    if(m_bSelect){
        p.setPen(selectedPenColor);
    }else if(m_inErrorRange ||
             E_HOUR::PREV_DAY_HOUR == m_type ||
             E_HOUR::NEXT_DAY_HOUR == m_type){
        p.setPen(errorRangePenColor);

    }else{
        p.setPen(normalPenColor);
    }
    p.drawText(rect(), Qt::AlignCenter, m_strText);
}



QString HourLabel::text() const{
    return m_strText;
}
void HourLabel::setText(const QString &text){
    m_strText  = text;
    QLabel::setText(text);
}

bool HourLabel::getInErrorRange() const
{
    return m_inErrorRange;
}

void HourLabel::setInErrorRange(bool inErrorRange)
{
    m_inErrorRange = inErrorRange;
}

bool HourLabel::getInRange() const
{
    return m_inRange;
}

void HourLabel::setInRange(bool inRange)
{
    m_inRange = inRange;
}

QDateTime HourLabel::getDateTime() const
{
    return dateTime;
}

void HourLabel::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

HourLabel::E_HOUR HourLabel::getType() const
{
    return m_type;
}

void HourLabel::setType(const E_HOUR &type)
{
    m_type = type;
    update();
}
