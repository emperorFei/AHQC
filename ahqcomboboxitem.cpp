#include "ahqcomboboxitem.h"

AHQComboboxItem::AHQComboboxItem(QWidget *parent) : QWidget(parent)
{
       m_cleanButton = new QPushButton(this);
       QPixmap pic(QStringLiteral(":/ico/close"));
       QIcon icon(pic);
       m_cleanButton->setIcon(icon);
       m_cleanButton->setFixedSize(QSize(this->height()-2,this->height()-2));
       m_label = new QLabel(this);

       m_layout = new QHBoxLayout(this);
       m_layout->addWidget(m_label);
       m_layout->addStretch();
       m_layout->addWidget(m_cleanButton);

       m_layout->setSpacing(5);
       m_layout->setContentsMargins(0, 0, 0, 0);
       setLayout(m_layout);
       this->setStyleSheet(this->styleSheet()+";padding:0px");
       m_label->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
       m_cleanButton->setStyleSheet("border:none;");
       connect(m_cleanButton,
               static_cast<void (QAbstractButton:: *)(bool)>(&QAbstractButton::clicked),
               [=]() {emit cleanButtonClicked();});
}
AHQComboboxItem::~AHQComboboxItem(){
    delete m_cleanButton;
    delete m_label;
    delete m_layout;
}
void AHQComboboxItem::setLabelContent(const QString &content){
    m_label->setText(content);
}
