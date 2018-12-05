#include "daylabel.h"

DayLabel::DayLabel(QWidget *parent):
    QLabel(parent),m_nDay(0),m_inErrorRange(false),m_bHover(false),m_bSelect(false)
{
    forbidCursor = QCursor(QPixmap(":ico/forbid")
                           .scaled(25,25,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}





void DayLabel::showDay(int nDay)
{
    m_strText = QString::number(nDay);
    m_nDay = nDay;
}

void DayLabel::enterEvent(QEvent *e)
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

void DayLabel::leaveEvent(QEvent *e)
{
    setCursor(Qt::ArrowCursor);
    m_bHover = false;
    update();
    QLabel::leaveEvent(e);
}

void DayLabel::mousePressEvent(QMouseEvent *e)
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
            emit signalClicked(date,this->property("type").toInt());
        }
    }
    QLabel::mousePressEvent(e);
}
void DayLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    if(!m_inErrorRange){
        if(m_bSelect){
            p.setBrush(QBrush(selectedBG));
            p.setPen(QPen(selectedBG, 1));
        }else if(m_bHover || m_inRange){
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
             E_DAY::PREV_MONTH_DAY == m_type ||
             E_DAY::NEXT_MONTH_DAY == m_type){
        p.setPen(errorRangePenColor);

    }else{
        p.setPen(normalPenColor);
    }
    p.drawText(rect(), Qt::AlignCenter, m_strText);
}






QString DayLabel::text() const{
    return m_strText;
}
void DayLabel::setText(const QString &text){
    m_strText  = text;
    QLabel::setText(text);
}

bool DayLabel::getInErrorRange() const
{
    return m_inErrorRange;
}

void DayLabel::setInErrorRange(bool inErrorRange)
{
    m_inErrorRange = inErrorRange;
}

bool DayLabel::getInRange() const
{
    return m_inRange;
}

void DayLabel::setInRange(bool inRange)
{
    m_inRange = inRange;
}

bool DayLabel::getBSelect() const {return m_bSelect;}
void DayLabel::setSelected(bool value)
{
    m_bSelect = value;
    update();
}


QDate DayLabel::getDate() const
{
    return date;
}

void DayLabel::setDate(const QDate &value)
{
    date = value;
}

DayLabel::E_DAY DayLabel::getType() const
{
    return m_type;
}

void DayLabel::setType(const E_DAY &type)
{
    // 设置控件属性类型
    this->setProperty("type", type);
    update();
    m_type = type;
}
