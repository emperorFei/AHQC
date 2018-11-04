#ifndef NOFOCUSFRAMEDELEGATE_H
#define NOFOCUSFRAMEDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>


class NoFocusFrameDelegate : public QStyledItemDelegate
{
public:
    NoFocusFrameDelegate(QWidget *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // NOFOCUSFRAMEDELEGATE_H
