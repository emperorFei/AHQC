#ifndef SINGEDDAYLABEL_H
#define SINGEDDAYLABEL_H

#include <QWidget>
#include "enums.h"
#include "daylabel.h"
#include <QPainter>
class SignedDayLabel : public DayLabel
{
    Q_OBJECT
    Q_ENUMS(SignLevel)
    Q_PROPERTY(SignLevel level READ getSignLevel WRITE setSignLevel)
public:
    static QPen penINFO;
    static QPen penSUSPECT;
    static QPen penCLASH;
    static QPen penMISSING;
    static QPen penMISSINGADATA;
    static QPen penMISSINGZDATA;
    static QPen penERROR;
public:
    explicit SignedDayLabel(QWidget *parent = nullptr);

    SignLevel getSignLevel() const;
    void setSignLevel(const SignLevel &value);
protected:
    void paintEvent(QPaintEvent* e);
private:
    SignLevel signLevel;
    bool signHidden;
};

#endif // SINGEDDAYLABEL_H
