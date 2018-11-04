#ifndef AHQCOMBOBOXITEM_H
#define AHQCOMBOBOXITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
class AHQComboboxItem : public QWidget
{
    Q_OBJECT
public:
    explicit AHQComboboxItem(QWidget *parent = nullptr);
    ~AHQComboboxItem();
    void setLabelContent(const QString &content);

private:
    QPushButton *m_cleanButton;
    QLabel *m_label;
    QHBoxLayout *m_layout;
signals:
    void cleanButtonClicked();

public slots:
};

#endif // AHQCOMBOBOXITEM_H
