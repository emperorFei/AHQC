#ifndef AHQCOMBOBOXITEM_H
#define AHQCOMBOBOXITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidgetItem>
#include <QDebug>
class AHQListWidgetItem : public QObject,public QListWidgetItem
{
    Q_OBJECT
public:
    explicit AHQListWidgetItem(QListWidget *parent = Q_NULLPTR, int type = Type);
    ~AHQListWidgetItem();
    void setLabelContent(const QString &content);
    QWidget *getWidget();

    void setData(int role, const QVariant &value);
    AHQListWidgetItem *clone() const;
    bool operator<(const AHQListWidgetItem &other) const;
private:
    QWidget *m_widget;
    QPushButton *m_cleanButton;
    QLabel *m_label;
    QHBoxLayout *m_layout;
    QListWidget *parent;
    int type;

signals:
    void cleanButtonClicked();

public slots:
};

#endif // AHQCOMBOBOXITEM_H
