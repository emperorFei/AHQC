#include "signeddaylabel.h"

QPen SignedDayLabel::penINFO(QPen(QColor(255,255,255,0),2));;
QPen SignedDayLabel::penSUSPECT(QPen(QColor(147,147,255),2));;
QPen SignedDayLabel::penCLASH(QPen(QColor(147,147,255),2));;
QPen SignedDayLabel::penMISSING(QPen(QColor(221,160,221),2));;
QPen SignedDayLabel::penMISSINGADATA(QPen(QColor(147,147,255),2));;
QPen SignedDayLabel::penMISSINGZDATA(QPen(QColor(221,160,221),2));;
QPen SignedDayLabel::penERROR(QPen(QColor(255,124,128),2));

SignedDayLabel::SignedDayLabel(QWidget *parent):
    DayLabel(parent),
    signLevel(SignLevel::SIGNINFO),
    signHidden(false)
{}


void SignedDayLabel::paintEvent(QPaintEvent* e){
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
    p.drawEllipse(this->rect().x()+4+2,this->rect().y()+4+2,this->width()-12,this->height()-12);

    if(!signHidden){
        switch(signLevel){
        case SignLevel::SIGNINFO:
            p.setPen(penINFO);
            break;
        case SignLevel::SIGNSUSPECT:
            p.setPen(penSUSPECT);
            break;
        case SignLevel::SIGNCLASH:
            p.setPen(penCLASH);
            break;
        case SignLevel::SIGNMISSING:
            p.setPen(penMISSING);
            break;
        case SignLevel::SIGNMISSINGADATA:
            p.setPen(penMISSINGADATA);
            break;
        case SignLevel::SIGNMISSINGZDATA:
            p.setPen(penMISSINGZDATA);
            break;
        case SignLevel::SIGNERROR:
            p.setPen(penERROR);
            break;
        }
    }else{
        p.setPen(penINFO);
    }
    p.drawEllipse(this->rect().x()+4,this->rect().y()+4,this->width()-8,this->height()-8);



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


SignLevel SignedDayLabel::getSignLevel() const
{
    return signLevel;
}
void SignedDayLabel::setSignLevel(const SignLevel &value)
{
    signLevel = value;
}

