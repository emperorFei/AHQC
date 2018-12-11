#ifndef HORIZONTALTREE_H
#define HORIZONTALTREE_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
namespace Ui {
class HorizontalTree;
}

class HorizontalTree : public QWidget
{
    Q_OBJECT

public:
    explicit HorizontalTree(QWidget *parent = nullptr);
    ~HorizontalTree();

private:
    Ui::HorizontalTree *ui;
};

#endif // HORIZONTALTREE_H
