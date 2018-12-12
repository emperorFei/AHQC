#ifndef FULLWIDEGT_H
#define FULLWIDEGT_H

#include <QWidget>
#include <QDateTime>
#include "azdata.h"
#include "mydoublelabel.h"

namespace Ui {
class FullWidegt;
}

class FullWidegt : public QWidget
{
    Q_OBJECT

public:
    explicit FullWidegt(QWidget *parent = nullptr);
    explicit FullWidegt(const AZData &azData,QWidget *parent = nullptr);
    ~FullWidegt();

    const QFont &doubleLabelfont() const;
    void setDoubleLabelFont(const QFont &font);
    QPair<QString, MyDoubleLabel::Level> getMostSeriousIssue() const;
    QDateTime getObserveTime() const;
    void initFromAZData(const AZData &azData);
private:
    //    void setQCWarn();
    static const QString doubleLabelNames[];
    QDateTime observeTime;
    Ui::FullWidegt *ui;
    QPair<QString,MyDoubleLabel::Level> mostSeriousIssue;
};

#endif // FULLWIDEGT_H
