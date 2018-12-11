#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QPainter>
#include <QPixmap>
namespace Ui {
class AnimationStackedWidget;
}

class AnimationStackedWidget :  public QStackedWidget
{
    Q_OBJECT

public:
    explicit AnimationStackedWidget(QWidget *parent = nullptr);
    ~AnimationStackedWidget();
    void paintEvent(QPaintEvent *);
    void setDuration(int);
public slots:
    void valueChanged_slot(QVariant);
    void animationFinished();
    void next();
    void forward();

private:
    Ui::AnimationStackedWidget *ui;
    void paintLeft_onNext(QPainter &, int);
    void paintRight_onNext(QPainter &, int);
    void paintLeft_onPrevious(QPainter &, int);
    void paintRight_onPrevious(QPainter &, int);

    QPropertyAnimation *animation;
    int duration;
    bool isAnimation;
    bool isGoingPrevoius;
    bool isGoingNext;
    QVariant currentValue;
    int widgetCount;
    int otherIndex;
};

#endif // ANIMATIONSTACKEDWIDGET_H
