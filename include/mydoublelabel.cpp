#include "mydoublelabel.h"
#include "ui_mydoublelabel.h"

MyDoubleLabel::MyDoubleLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDoubleLabel)
{

    ui->setupUi(this);
    left = ui->left_label;
    right = ui->right_label;

    setProperty("leftText","left");
    setProperty("rightText","right");
    setProperty("alignment",TextAlignment::AlignHCerter);

    left->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    right->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

}
MyDoubleLabel::MyDoubleLabel(const QString &itemName,
                       const QPair<QPair<QString,QString>,MyDoubleLabel::Level> &data,
                       QWidget *parent):
    QWidget(parent),dataName(itemName),leval(data.second)
{
    ui->setupUi(this);
    left = ui->left_label;
    right = ui->right_label;

    setProperty("leftText",data.first.first);
    setProperty("rightText",data.first.second);
    setProperty("alignment",TextAlignment::AlignHCerter);

    left->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    right->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}


MyDoubleLabel::~MyDoubleLabel()
{
    delete ui;
}

void MyDoubleLabel::setText(const QString &){}
void MyDoubleLabel::setText(const stringPair& dataPair){
    leftText = dataPair.first;
    left->setText(leftText);
    rightText = dataPair.second;
    right->setText(rightText);
}


void MyDoubleLabel::setRightText(const QString &value)
{
    rightText = value;
    right->setText(value);
}

QString MyDoubleLabel::getLeftText() const
{
    return leftText;
}

void MyDoubleLabel::setLeftText(const QString &value)
{
    leftText = value;
    left->setText(value);
}

MyDoubleLabel::TextAlignment MyDoubleLabel::getAlignment() const
{
    return alignment;
}

void MyDoubleLabel::setAlignment(const TextAlignment &value)
{
    alignment = value;
    switch(alignment){
    case TextAlignment::AlignLeft:
        left->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        right->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        left->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
        right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        break;
    case TextAlignment::AlignRight:
        left->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        right->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        right->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
        break;
    case TextAlignment::AlignHCerter:
        left->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        right->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        break;
    case TextAlignment::AlignJustify:
        left->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        right->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        break;
    }
}

void MyDoubleLabel::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

const QFont & MyDoubleLabel::font() const{
    return left->font();
}

void MyDoubleLabel::setFont(const QFont &font){
    left->setFont(font);
    right->setFont(font);
}



QString MyDoubleLabel::getDataName() const
{
    return dataName;
}

void MyDoubleLabel::setDataName(const QString &value)
{
    dataName = value;
}

MyDoubleLabel::Level MyDoubleLabel::getLevel() const
{
    return leval;
}

void MyDoubleLabel::setLevel(const Level &value)
{
    leval = value;
}


QString MyDoubleLabel::getRightText() const
{
    return rightText;
}
