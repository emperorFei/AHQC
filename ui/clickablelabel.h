#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
class ClickableLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY (bool selected READ getSelected WRITE setSelected)
public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    ~ClickableLabel();
    QString text() const;
    bool getSelected() const;
    void setSelected(bool value);

signals:
    void clicked(ClickableLabel* clicked);
    void rightButtonClicked(bool);
public slots:
    void setText(const QString &);
protected:
    void mouseReleaseEvent(QMouseEvent *);
//    void paintEvent(QPaintEvent*);
private:
    QString m_str;
    bool selected;
};

#endif // CLICKABLELABEL_H
