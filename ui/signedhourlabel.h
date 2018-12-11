#ifndef SIGNEDHOURLABEL_H
#define SIGNEDHOURLABEL_H

#include <QObject>
#include <QWidget>
#include "hourlabel.h"
#include "enums.h"
class SignedHourLabel : public HourLabel
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
    explicit SignedHourLabel(QWidget *parent = nullptr);
    SignLevel getSignLevel() const;
    void setSignLevel(const SignLevel &value);

    bool getSignHidden() const;
    void setSignHidden(bool value);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* e);
private:
    SignLevel signLevel;
    bool signHidden;
};

#endif // SIGNEDHOURLABEL_H
