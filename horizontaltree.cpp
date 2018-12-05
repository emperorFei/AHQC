#include "horizontaltree.h"
#include "ui_horizontaltree.h"

HorizontalTree::HorizontalTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HorizontalTree)
{
    ui->setupUi(this);
//    QPushButton *pushButton = new QPushButton(ui->listView);
//    QPushButton *pushButton_2 = new QPushButton(ui->listView);
//    QPushButton *pushButton_3 = new QPushButton(ui->listView);
//    QPushButton *pushButton_4 = new QPushButton(ui->listView);
//    pushButton->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//    pushButton->resize(20,20);
//    pushButton_2->resize(30,30);
//    pushButton_3->resize(50,50);
//    pushButton_4->resize(70,70);
//    pushButton->setMask(QRegion(0,0,20,20,QRegion::Ellipse));
//    pushButton_2->setMask(QRegion(0,0,30,30,QRegion::Ellipse));
//    pushButton_3->setMask(QRegion(0,0,50,50,QRegion::Ellipse));
//    pushButton_4->setMask(QRegion(0,0,70,70,QRegion::Ellipse));
//    ui->listView->layout()->addWidget(pushButton);
//    ui->listView->layout()->addWidget(pushButton_2);
//    ui->listView->layout()->addWidget(pushButton_3);
//    ui->listView->layout()->addWidget(pushButton_4);

}

HorizontalTree::~HorizontalTree()
{
    delete ui;
}
