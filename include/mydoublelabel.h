#ifndef MYDOUBLELABEL_H
#define MYDOUBLELABEL_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QWidget>
#include <QLabel>
#include <QPair>
#include <QPainter>
#include <QDebug>
#include <QMap>

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
    Q_ENUMS(Level)
    Q_PROPERTY(QString rightText READ getRightText WRITE setRightText)
    Q_PROPERTY(QString leftText READ getLeftText WRITE setLeftText)
    Q_PROPERTY(TextAlignment alignment READ getAlignment WRITE setAlignment)
    Q_PROPERTY(Level level READ getLevel WRITE setLevel)

public:
    enum TextAlignment{AlignLeft,AlignHCerter,AlignRight,AlignJustify};
    enum Level{INFO,SUSPECTED,CLASH,MISSING,MISSINGZDATA,MISSINGAMDATA,ERROR};

    explicit MyDoubleLabel(QWidget *parent = nullptr);
    explicit MyDoubleLabel(const QString &itemName,
                           const QPair<QPair<QString,QString>,MyDoubleLabel::Level> &data,
                           QWidget *parent = nullptr);
    ~MyDoubleLabel();

    //void mark(){}

    QString getRightText() const;
    void setRightText(const QString &value);
    QString getLeftText() const;
    void setLeftText(const QString &value);
    TextAlignment getAlignment() const;
    void setAlignment(const TextAlignment &value);
    Level getLevel() const;
    void setLevel(const Level &value);
    QString getDataName() const;
    void setDataName(const QString &value);
    const QFont & font() const;
    void setFont(const QFont &font);
protected:
    void paintEvent(QPaintEvent*);

public slots:
    void setText(const QString &);
    void setText(const stringPair&);
private:
    QString dataName;
    TextAlignment alignment;
    Ui::MyDoubleLabel *ui;
    QLabel *left;
    QLabel *right;
    Level leval;
    QString leftText;
    QString rightText;
};

#endif // MYDOUBLELABEL_H
