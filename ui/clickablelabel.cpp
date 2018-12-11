#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent),m_str("")
{
    setText(m_str);
}
ClickableLabel::~ClickableLabel(){}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *evt)
{

    if(evt->button() ==Qt::RightButton){
        emit rightButtonClicked(true);
    }else{
        emit clicked(this);
    }

}

bool ClickableLabel::getSelected() const
{
    return selected;
}

void ClickableLabel::setSelected(bool value)
{
    selected = value;
}
QString ClickableLabel::text() const{
    return m_str;
}
void ClickableLabel::setText(const QString &text){
    m_str = text;
    QLabel::setText(text);
}
//void ClickableLabel::paintEvent(QPaintEvent*)
//{
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}
