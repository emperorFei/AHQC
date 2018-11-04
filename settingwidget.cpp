#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint );
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor("#444444"));
    //设置阴影圆角
    shadow->setBlurRadius(30);
    //给嵌套QWidget设置阴影
    ui->widget_bg->setGraphicsEffect(shadow);
    //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    ui->lay_bg->setMargin(24);

    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->closeButton->setIcon(closePix);
    ui->minButton->setIcon(minPix);
    //ui->closeButton->setStyleSheet("QToolButton{border:none;background:rgb(248,248,248)}");



    ui->settingTreeWidget->setExpandsOnDoubleClick(false);

    if(!ui->localpath_radioButton->isChecked()){
        ui->localpath_radioButton->animateClick(10);
    }
    ui->settingTreeWidget->expandItem(ui->settingTreeWidget->topLevelItem(0));
    ui->settingTreeWidget->setItemSelected(ui->settingTreeWidget->topLevelItem(0)->child(0),true);
    ui->filesys_account_checkBox->setCheckState(Qt::CheckState::Checked);

    initComboBoxView();
    connectSingles();



}




SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initComboBoxView(){
    QListWidget *isostpath_comboBox_ListWidget  = new QListWidget(ui->isostpath_comboBox);
    isostpath_comboBox_ListWidget->setItemDelegate(new NoFocusFrameDelegate(ui->observeTimes_comboBox));
    ui->isostpath_comboBox->setEditable(true);
    ui->isostpath_comboBox->setModel(isostpath_comboBox_ListWidget->model());
    ui->isostpath_comboBox->setView(isostpath_comboBox_ListWidget);

    for (int i = 0; i < 5; ++i)
        {
            QListWidget* isostpath_comboBox_view = static_cast<QListWidget* >(ui->isostpath_comboBox->view());
            AHQComboboxItem *item = new AHQComboboxItem(ui->isostpath_comboBox);
            item->setLabelContent(QString("Account") + QString::number(i, 10));
            QListWidgetItem* widgetItem = new QListWidgetItem(isostpath_comboBox_view);
            isostpath_comboBox_view->setItemWidget(widgetItem,item);

        }
}


void SettingWidget::treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    //qDebug()<<"111";
    int nCount = ui->settingTreeWidget->topLevelItemCount();
    for(int i=0; i<nCount;i++) {
        if (item != ui->settingTreeWidget->topLevelItem(i)) {
            ui->settingTreeWidget->collapseItem(ui->settingTreeWidget->topLevelItem(i));
        }
    }
    item->child(0)->setSelected(true);
}

void SettingWidget::treeWidget_itemPressed(QTreeWidgetItem * item,int column)
{
    Q_UNUSED(column);

    if(qApp->mouseButtons() & Qt::LeftButton ){
        bool isTopLever = false;
        int nCount = ui->settingTreeWidget->topLevelItemCount();
        int i=0;
        for(; i<nCount;i++) {
            if (item == ui->settingTreeWidget->topLevelItem(i)) {
                isTopLever = true;
                break;
            }
        }
        if(isTopLever){
            for(int i=0; i<nCount;i++) {
                if (item != ui->settingTreeWidget->topLevelItem(i)) {
                    ui->settingTreeWidget->collapseItem(ui->settingTreeWidget->topLevelItem(i));
                }
            }
            ui->settingTreeWidget->expandItem(item);
            ui->settingTreeWidget->setCurrentItem(item->child(0));
        }
    }
}

void SettingWidget::navigation_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous){
    //Q_UNUSED(previous);
    if(current != Q_NULLPTR){
        qDebug() << "currentItemChanged: " << (previous == Q_NULLPTR ? "NONE" : previous->text(0).toStdString().c_str()) <<  " to " << current->text(0).toStdString().c_str();
        if(current->text(0) == "界面设置"){
            ui->main_stackedWidget->setCurrentIndex(0);
        }else if(current->text(0) == "台站设置"){
            ui->main_stackedWidget->setCurrentIndex(1);
        }else if(current->text(0) == "路径设置"){
            ui->main_stackedWidget->setCurrentIndex(2);
        }else if(current->text(0) == "数据库设置"){
            ui->main_stackedWidget->setCurrentIndex(3);
        }else if(current->text(0) == "缓存设置"){
            ui->main_stackedWidget->setCurrentIndex(4);
        }
    }else{
        qDebug() << "currentItemChanged: NONE";
    }

}

void SettingWidget::closeButtonClicked(bool checked)
{
    Q_UNUSED(checked);
    //qDebug()<<"closeButtonClicked";
    this->close();
    //qDebug() << cloesed;
}
void SettingWidget::minButtonClicked(bool checked)
{
    Q_UNUSED(checked);
    //qDebug()<<"minButtonClicked";
    this->showMinimized();
}


void SettingWidget::navigationTreeIndent(){
    QTreeWidgetItemIterator it( ui->settingTreeWidget);
    int nCount = ui->settingTreeWidget->topLevelItemCount();
    ui->settingTreeWidget->setIndentation(1);

}




void SettingWidget::connectSingles(){
    this->connect(ui->settingTreeWidget,
                  SIGNAL(itemPressed(QTreeWidgetItem *,int)),
                  this,
                  SLOT(treeWidget_itemPressed(QTreeWidgetItem *,int)));
    this->connect(ui->settingTreeWidget,
                  SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
                  this,
                  SLOT(navigation_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));


    this->connect(ui->minButton,&QToolButton::clicked,this,&SettingWidget::minButtonClicked);
    this->connect(ui->closeButton,&QToolButton::clicked,this,&SettingWidget::closeButtonClicked);

    connectUISettingPageSingles();
    connectFilePathSettingPageSingles();
    connectDBSettingPageSingles();
    connectStationSettingPageSingles();
    connectCacheSettingPageSingles();
}

void SettingWidget::connectUISettingPageSingles(){

}
void SettingWidget::connectFilePathSettingPageSingles(){
    this->connect(ui->filepath_switch_buttonGroup,
                  SIGNAL(buttonToggled(QAbstractButton *, bool)),
                  this,
                  SLOT(pathSwitchButtonToggled(QAbstractButton *, bool)));
    this->connect(ui->filesys_account_checkBox,
                  SIGNAL(stateChanged(int)),
                  this,
                  SLOT(filesysAccountCheckBoxStateChanged(int)));
    this->connect(ui->isospath_change_Button,
                  SIGNAL(clicked(bool)),
                  this,
                  SLOT(isospathChangeButtonClicked(bool)));
}
void SettingWidget::connectDBSettingPageSingles(){

}
void SettingWidget::connectStationSettingPageSingles(){

}
void SettingWidget::connectCacheSettingPageSingles(){

}

void SettingWidget::pathSwitchButtonToggled(QAbstractButton *button, bool checked){
    if(checked == true){
        if(button->objectName() == "localpath_radioButton"){
            ui->filesys_account_checkBox->setEnabled(false);
            ui->filesys_username_label->setEnabled(false);
            ui->filesys_username_edit->setEnabled(false);
            ui->filesys_password_label->setEnabled(false);
            ui->filesys_password_edit->setEnabled(false);
        }else if(button->objectName() == "netpath_radioButton"){
            ui->filesys_account_checkBox->setEnabled(true);
            if(ui->filesys_account_checkBox->checkState() ==Qt::CheckState::Checked){
                ui->filesys_username_label->setEnabled(true);
                ui->filesys_username_edit->setEnabled(true);
                ui->filesys_password_label->setEnabled(true);
                ui->filesys_password_edit->setEnabled(true);
            }

        }
    }
}



void SettingWidget::filesysAccountCheckBoxStateChanged(int state){
    if(state == 0){
        ui->filesys_username_label->setEnabled(false);
        ui->filesys_username_edit->setEnabled(false);
        ui->filesys_password_label->setEnabled(false);
        ui->filesys_password_edit->setEnabled(false);
    }else if(state == 1){
        ui->filesys_username_label->setEnabled(false);
        ui->filesys_username_edit->setEnabled(false);
        ui->filesys_password_label->setEnabled(false);
        ui->filesys_password_edit->setEnabled(false);
    }else if(state == 2){
        ui->filesys_username_label->setEnabled(true);
        ui->filesys_username_edit->setEnabled(true);
        ui->filesys_password_label->setEnabled(true);
        ui->filesys_password_edit->setEnabled(true);
    }
}

void SettingWidget::isospathChangeButtonClicked(bool checked){
    Q_UNUSED(checked);
    QString directory =
            QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));
    qDebug() << directory;
        if (!directory.isEmpty()) {
//            QString disk(directory.mid(0,1));
//            QFile diskPath(disk+":");
//            QFileInfo fi(directory);
//            if(fi.exists()){
//                //QDir dir(directory);
//                if(directory == fi.absoluteFilePath()){
//                    qDebug() << directory <<  " -- SAME";
//                }else{
//                    qDebug() << directory <<  " -- " <<  fi.canonicalFilePath()
//                             <<" @-@" << fi.absoluteDir()<< " @-@ " << fi.absoluteFilePath()
//                             <<"@_@"
//                               <<" @-@" << fi.completeBaseName();

////                             << QDir(directory).root()
////                             <<"@_@"
////                             << QDir(directory).rootPath()
////                             <<"@_@"
////                             << QDir(directory).dirName();
//                   QFileInfoList fl(QDir::drives());
//                   QString buffer("");
//                   for(QFileInfo filei:fl){

//                       if(filei.isSymLink()){
//                          buffer += filei.symLinkTarget();
//                       }else{
//                          buffer += " "+filei.completeBaseName();
//                       }

//                   }
//                   qDebug() << buffer;
//                }

//            }

            if (ui->isostpath_comboBox->findText(directory) == -1){
//                ui->isostpath_comboBox->addItem(directory);
                QListWidget* isostpath_comboBox_view = static_cast<QListWidget* >(ui->isostpath_comboBox->view());
                AHQComboboxItem *item = new AHQComboboxItem(ui->isostpath_comboBox);
                item->setLabelContent(directory);
                QListWidgetItem* widgetItem = new QListWidgetItem(isostpath_comboBox_view);
                isostpath_comboBox_view->setItemWidget(widgetItem,item);
            }

            ui->isostpath_comboBox->setCurrentIndex(ui->isostpath_comboBox->findText(directory));
        }
    qDebug() << directory << "aaa";
}



void SettingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = event->pos();
    }
}

void SettingWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void SettingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed && (event->buttons() && Qt::LeftButton))
    {
        this->move(event->globalPos() - mousePoint);
        event->accept();
    }
}

