#include "ahqlistwidgetitem.h"

AHQListWidgetItem::AHQListWidgetItem(QListWidget *parent, int type) : QListWidgetItem(parent,type)
,parent(parent),type(type){
       m_widget = new QWidget(parent,Qt::Window);
       m_widget->setFixedSize(parent->width(),parent->height());
       m_cleanButton = new QPushButton(m_widget);
       QPixmap pic(QStringLiteral(":/ico/close"));
       QIcon icon(pic);
       m_cleanButton->setIcon(icon);
       m_cleanButton->setFixedSize(QSize(m_widget->height()-1,m_widget->height()-1));
       m_cleanButton->setStyleSheet("background-color: rgb(0, 255, 0);");
       m_label = new QLabel(m_widget);
       m_label->setFixedSize(QSize(m_widget->width()-m_cleanButton->width()-1,m_widget->height()));
       m_layout = new QHBoxLayout(m_widget);
       m_layout->addWidget(m_label);
       m_layout->addStretch();
       m_layout->addWidget(m_cleanButton);
       m_widget-> setStyleSheet("background-color: rgb(110, 15,255);");
       m_layout->setSpacing(5);
       m_layout->setContentsMargins(0, 0, 0, 0);
       m_widget->setLayout(m_layout);
       m_widget->setStyleSheet(m_widget->styleSheet()+";padding:0px");
       m_label->setStyleSheet("background-color: rgb(248, 248, 248);");
       m_cleanButton->setStyleSheet("border:none;");
       this->setSizeHint(QSize(m_widget->width(),m_widget->height()));

       qDebug() << "parentSize: " << parent->size() << "m_widgetSize: "<< m_widget->size() << "m_labelSize: "<< m_label->size() << "m_cleanbuttonSize: " <<m_cleanButton->size();
//       m_widget->connect(m_cleanButton,
//               static_cast<void (QAbstractButton:: *)(bool)>(&QAbstractButton::clicked),
//               [=]() {emit cleanButtonClicked();});

}
AHQListWidgetItem::~AHQListWidgetItem(){
}
void AHQListWidgetItem::setLabelContent(const QString &content){
    m_label->setText(content);
}
QWidget *AHQListWidgetItem::getWidget(){
    return m_widget;
}

void AHQListWidgetItem::setData(int role, const QVariant &value){
    QListWidgetItem::setData(role,value);
    if(role == Qt::ItemDataRole::DisplayRole){
        m_label->setText(value.toString());
    }else{
        m_label->setText(QString());
    }
    qDebug() << "label.text: "+m_label->text();
}


AHQListWidgetItem *AHQListWidgetItem::clone() const{
    AHQListWidgetItem *item = new AHQListWidgetItem(this->parent,this->type);
    item->m_label->text() = this->m_label->text();
    return item;
}
bool AHQListWidgetItem::operator<(const AHQListWidgetItem &other) const{
    return m_label->text() < other.m_label->text();
}
