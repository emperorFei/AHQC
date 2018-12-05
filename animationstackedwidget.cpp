#include "animationstackedwidget.h"
#include "ui_animationstackedwidget.h"

AnimationStackedWidget::AnimationStackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::AnimationStackedWidget)
{
    ui->setupUi(this);
    isAnimation = false;
    duration = 1000;
    animation = new QPropertyAnimation(this, QByteArray());
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged_slot(QVariant)));
    connect(animation, SIGNAL(finished()), this, SLOT(animationFinished()));
}

AnimationStackedWidget::~AnimationStackedWidget()
{
    delete ui;
}

void AnimationStackedWidget::forward(){
    if(isAnimation){
        return;
    }
    isAnimation = true;
    isGoingPrevoius = true;
    int c = currentIndex();
    if(c == 0){
        isAnimation = false;
        isGoingPrevoius = false;
        return;
    }
    otherIndex = c - 1;
    widget(c)->hide();
    QRect g = geometry();
//    int x = g.x();
    int width = g.width();
    animation->setStartValue(width);
    animation->setEndValue(0);
    animation->setDuration(duration);
    animation->start();
}
void AnimationStackedWidget::next(){
    if(isAnimation){
        return;
    }
    isAnimation = true;
    isGoingNext = true;
    widgetCount = count();
    int c = currentIndex();
    otherIndex = (c + 1) % widgetCount;
    if(otherIndex == 0){
        isAnimation = false;
        isGoingNext = false;
        return;
    }
    widget(c)->hide();
    QRect g = geometry();
//    int x = g.x();
    int width = g.width();
    animation->setStartValue(width);
    animation->setEndValue(0);
    animation->setDuration(duration);
    animation->start();
}

void AnimationStackedWidget::valueChanged_slot(QVariant value)
{
    currentValue = value;
    update();
}

void AnimationStackedWidget::paintEvent(QPaintEvent *e){

    Q_UNUSED(e)
    if(isAnimation){
        if(isGoingNext){
            QPainter painter(this);
            paintLeft_onNext(painter,currentIndex());
            paintRight_onNext(painter,otherIndex);
        }else if(isGoingPrevoius){
            QPainter painter(this);
            paintLeft_onPrevious(painter,otherIndex);
            paintRight_onPrevious(painter,currentIndex());
        }
    }
    QWidget::paintEvent(e);
}

void AnimationStackedWidget::paintLeft_onNext(QPainter &painter,int currentIndex){
    QWidget *widget = this->widget(currentIndex);
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    QRect rectBoxOfWidget = widget->geometry();
    double value = currentValue.toDouble();
    QRect r1(0.0,0.0,qRound(value),rectBoxOfWidget.height());
    QRect r2(rectBoxOfWidget.width() - qRound(value),0,qRound(value),rectBoxOfWidget.height());
    painter.drawPixmap(r1,pixmap,r2);
}

void AnimationStackedWidget::paintRight_onNext(QPainter &painter,int otherIndex){
   QWidget *otherWidget = this->widget(otherIndex);
   QRect r = geometry();
   otherWidget->resize(r.width(), r.height());
   QPixmap nextPixmap(otherWidget->size());
   otherWidget->render(&nextPixmap);
   double value = currentValue.toDouble();
   QRectF r1(value, 0.0, r.width() - value, r.height());
   QRectF r2(0.0, 0.0, r.width() - value, r.height());
   painter.drawPixmap(r1, nextPixmap, r2);
}
void AnimationStackedWidget::paintLeft_onPrevious(QPainter &painter,int otherIndex){

    QWidget *otherWidget = this->widget(otherIndex);
    QRect r = geometry();
    otherWidget->resize(r.width(), r.height());
    QPixmap nextPixmap(otherWidget->size());
    otherWidget->render(&nextPixmap);
    double value = currentValue.toDouble();
    QRectF r1(0.0, 0.0, r.width()-value, r.height());
    QRectF r2(value, 0.0, r.width() - value, r.height());
    painter.drawPixmap(r1, nextPixmap, r2);
}

void AnimationStackedWidget::paintRight_onPrevious(QPainter &painter,int currentIndex){
    QWidget *widget = this->widget(currentIndex);
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    QRect rectBoxOfWidget = widget->geometry();
    double value = currentValue.toDouble();
    QRect r1(widget->width() - qRound(value),0.0,qRound(value),rectBoxOfWidget.height());
    QRect r2(0,0,qRound(value),rectBoxOfWidget.height());
    painter.drawPixmap(r1,pixmap,r2);
}
void AnimationStackedWidget::animationFinished()
{
    isAnimation = false;
    isGoingNext = false;
    isGoingPrevoius = false;
    widget(currentIndex())->show();
    setCurrentIndex(otherIndex);
}

