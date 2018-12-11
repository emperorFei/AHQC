#ifndef MYDOUBLELABEL_H
#define MYDOUBLELABEL_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QWidget>
#include <QLabel>
#include <QPair>
#include <QPainter>
#include <QDebug>
#ifndef   stringPair
typedef QPair<QString,QString> stringPair;
#endif
namespace Ui {
class MyDoubleLabel;
}

class  QDESIGNER_WIDGET_EXPORT MyDoubleLabel : public QWidget
{
    Q_OBJECT
    Q_ENUMS(TextAlignment)
    Q_PROPERTY(QString rightText READ getRightText WRITE setRightText)
    Q_PROPERTY(QString leftText READ getLeftText WRITE setLeftText)
    Q_PROPERTY(TextAlignment alignment READ getAlignment WRITE setAlignment)

public:
    explicit MyDoubleLabel(QWidget *parent = nullptr);
    ~MyDoubleLabel();
    enum TextAlignment{AlignLeft,AlignHCerter,AlignRight,AlignJustify};

    QString getRightText() const;
    void setRightText(const QString &value);
    QString getLeftText() const;
    void setLeftText(const QString &value);
    TextAlignment getAlignment() const;
    void setAlignment(const TextAlignment &value);
    void mark(){}
protected:
    void paintEvent(QPaintEvent*);

public slots:
    void setText(const QString &);
    void setText(const stringPair&);
private:

    TextAlignment alignment;
    Ui::MyDoubleLabel *ui;
    QLabel *left;
    QLabel *right;
    QString leftText;
    QString rightText;
};

#endif // MYDOUBLELABEL_H
