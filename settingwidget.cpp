#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QDialog(parent),setting(singleton<GlobalSetting>::GetInstance()),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );
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

//    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
//    ui->closeButton->setIcon(closePix);
    ui->closeButton->setStyleSheet(styleSheet()+QString("\n"
                                           "#closeButtonr{\n"
                                              "image: url(:/ico/close_normal);\n"
                                           "}\n"
                                           "#closeButton:hover{\n"
                                             "image: url(:/ico/close_hover);\n"
                                           "}\n"
                                       ));
//    ui->minButton->setIcon(minPix);
    ui->minButton->setStyleSheet(styleSheet()+QString("\n"
                                           "#minButtonr{\n"
                                              "image: url(:/ico/min_normal);\n"
                                           "}\n"
                                           "#minButton:hover{\n"
                                             "image: url(:/ico/min_hover);\n"
                                           "}\n"
                                       ));
    //ui->closeButton->setStyleSheet("QToolButton{border:none;background:rgb(248,248,248)}");



    ui->settingTreeWidget->setExpandsOnDoubleClick(false);

    if(!ui->localpath_radioButton->isChecked()){
        ui->localpath_radioButton->animateClick(10);
    }
    ui->settingTreeWidget->expandItem(ui->settingTreeWidget->topLevelItem(0));
    ui->settingTreeWidget->setItemSelected(ui->settingTreeWidget->topLevelItem(0)->child(0),true);
    ui->filesys_account_checkBox->setCheckState(Qt::CheckState::Checked);
    ui->main_stackedWidget->setCurrentIndex(0);

    initPages();
    connectSingles();



}




SettingWidget::~SettingWidget()
{
    delete ui;
}

//stationNum = 58342
//stationHeight = 5.4
//presureHeight = 6.4
//ISOSPath = \\\\10.126.148.90\\isos
//isISOSPathLocal = true
//ISOSPathNeedAccount = false
//ISOSPathUsername = observer
//ISOSPathPassword = 58342
//minuteDataPathTemplate =  \\dataset\\江苏\\#{stationNum}\\AWS\\新型自动站\\质控
//AWSNetPathTemplate = \\bin\\Awsnet\\#{month}
//AMFileNameTemplate = AWS_M_Z_#{stationNum}_#{Date}.txt
//ZFileNameTemplate= Z_SURF_I_#{stationNum}_#{DateTime}_O_AWS_FTM#{ccx}.txt

//dbHost = localhost
//dbPort = 3306
//dbAccount = 58342
//dbPassword = 58342


//delayOfOnTime = 70
//delayOfObserveTime = 170;
//shiftTime = 16:30
//observeTimes = 20,08,11,14,15 20,08,14
//observeTimesCheckedIndex = 0
void SettingWidget::initPages(){
    qDebug() << setting->value("stationHeight");

    ui->station_height_edit->setText(setting->value("stationHeight"));
    ui->presure_height_edit->setText(setting->value("presureHeight"));
//    QString observeTimess (setting->value("observeTimes"));
//    observeTimess = observeTimess.replace(QRegExp("-"),",");
//    QStringList observeTimesList = observeTimess.split("<>");
    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->observeTimes_comboBox);
    ui->observeTimes_comboBox->setItemDelegate(itemDelegate);
    ui->observeTimes_comboBox->addItems(setting->value("observeTimes").replace("-",",").split("<>"));
    ui->observeTimes_comboBox->setCurrentIndex(setting->value("observeTimesCheckedIndex").toInt());
    ui->onTime_sendDelay_edit->setText(setting->value("delayOfOnTime"));
    ui->observeTime_sendDelay_edit->setText(setting->value("delayOfObserveTime"));
    ui->shiftTime_edit->setText(setting->value("shiftTime"));
    setting->value("isISOSPathLocal") == "true" ?
          ui->localpath_radioButton->animateClick(10):
          ui->netpath_radioButton->animateClick(10);
    ui->isospath_lineEdit->setText(setting->value("ISOSPath"));
    setting->value("ISOSPathNeedAccount") == "true" ?
          ui->filesys_account_checkBox->setChecked(true):
          ui->filesys_account_checkBox->setChecked(false);
    ui->filesys_username_edit->setText(setting->value("ISOSPathUsername"));
    ui->filesys_password_edit->setText(setting->value("ISOSPathPassword"));
    ui->db_address_edit->setText(setting->value("dbHost"));
    ui->db_port_edit->setText(setting->value("dbPort"));
    ui->db_account_edit->setText(setting->value("dbAccount"));
    ui->db_password_edit->setText(setting->value("dbPassword"));
}

//void SettingWidget::initComboBoxView(){
//    QComboBox *comboBox = ui->isostpath_comboBox;
//    QListWidget *isostpath_comboBox_ListWidget  = new QListWidget(ui->isostpath_comboBox);
//    isostpath_comboBox_ListWidget->setItemDelegate(new NoFocusFrameDelegate(ui->observeTimes_comboBox));
//    ui->isostpath_comboBox->setEditable(true);
//    ui->isostpath_comboBox->setModel(isostpath_comboBox_ListWidget->model());
//    ui->isostpath_comboBox->setView(isostpath_comboBox_ListWidget);
//    ui->isostpath_comboBox->setMaxVisibleItems(10);


//    QListWidget* isostpath_comboBox_view = static_cast<QListWidget* >(ui->isostpath_comboBox->view());
//    for (int i = 0; i < 3; ++i)
//        {
//            AHQListWidgetItem *item = new AHQListWidgetItem(isostpath_comboBox_view,QListWidgetItem::Type);
//            item->setData(Qt::ItemDataRole::DisplayRole,QVariant("Account:"+QString::number(i)));
//            isostpath_comboBox_view->setItemWidget(item,item->getWidget());
//            //item->getWidget()->show();
//            //isostpath_comboBox_view->addItem(item);
//        }
//    ui->isostpath_comboBox->setCurrentIndex(0);

//}


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
    //this->close();
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
    connect(ui->missingColor_btn,
            &QPushButton::clicked,
            this,
            &SettingWidget::sltColorBtnClicled);
    connect(ui->errorColor_btn,
            &QPushButton::clicked,
            this,
            &SettingWidget::sltColorBtnClicled);
    connect(ui->suspectedColor_btn,
            &QPushButton::clicked,
            this,
            &SettingWidget::sltColorBtnClicled);
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
    this->connect(ui->isospath_change_btn,
                  SIGNAL(clicked(bool)),
                  this,
                  SLOT(isospathChangeButtonClicked(bool)));

    this->connect(ui->isospath_lineEdit,
                  SIGNAL(editingFinished()),
                  this,
                  SLOT(isospathLineEditTextChanged()));
    this->connect(ui->isospath_lineEdit,
                  SIGNAL(editingFinished()),
                  this,
                  SLOT(isospathLineEditTextChanged()));

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
    QString lineEditText = ui->isospath_lineEdit->text();
    QString directory("");
    QString path(QDir::currentPath());
    if(!lineEditText.isEmpty()){
        lineEditText = lineEditText.trimmed();
        if(!lineEditText.isEmpty()){
            QFile currectPath(lineEditText);
            QFileInfo currectPathInfo(currectPath);
            if(currectPath.exists() && currectPathInfo.isDir()){
              path = currectPath.fileName();
            }
        }
    }
    directory =
            QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), path));
    qDebug() << directory;
    if (!directory.isEmpty()) {
            ui->isospath_lineEdit->setText(directory);
    }
    isospathLineEditTextChanged();

}

void SettingWidget::isospathLineEditTextChanged(){
    //qDebug() << "ddd";
    QString text(ui->isospath_lineEdit->text());
    QString lineEditText = text;
    QString directory("");
    QString path(QDir::currentPath());
    if(!lineEditText.isEmpty()){
        lineEditText = lineEditText.trimmed();
        if(!lineEditText.isEmpty()){
            QFile currectPath(lineEditText);
            QFileInfo currectPathInfo(currectPath);
            if(currectPath.exists() && currectPathInfo.isDir()){
              path = currectPath.fileName();

              QFont font = ui->isospath_lineEdit->font();
              QFontMetrics lineEditFontMetrics(font);
              int totalPixSize = lineEditFontMetrics.width(text);
              //int placeholderPixSize = lineEditFontMetrics.width("···");
              QString disPlayText = text;
              QString tempString(disPlayText);
              QRegExp reg("\\\\[^\\\\]+$");
              QString tail("\\ISOS");
              if(reg.indexIn(tempString,0) != -1){
                tail = tempString.mid(reg.indexIn(tempString,0));
                tempString = tempString.remove("\\\\[^\\\\]+$");
              }
              int lastIndex = -1;
              int displayPixSize = -1;
              int maxPixSize = ui->isospath_lineEdit->width()-30;
              if(totalPixSize >= maxPixSize){
                  do{
                      lastIndex = tempString.lastIndexOf("\\\\[^\\\\]+$");
                      tempString = tempString.remove(lastIndex,tempString.length()-lastIndex);
                      disPlayText = tempString+"\\···"+tail;
                      displayPixSize = lineEditFontMetrics.width(disPlayText);
                  }while(lineEditFontMetrics.width(disPlayText) >= ui->isospath_lineEdit->width()-30);        ui->isospath_lineEdit->setText("ddddddddd");
              }
              ui->isospath_lineEdit->setText(disPlayText);
              qDebug() << "path: " << path;
              return ;
            }
        }
    }
    ui->isospath_lineEdit->setText("invalidpath");
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
void SettingWidget::sltColorBtnClicled(bool){
    QPushButton* btn = static_cast<QPushButton*>(sender());
    QColor oldColor = btn->palette().background().color();
    QColor color = QColorDialog::getColor(oldColor,this,
                                              tr("请选择新颜色"));

    if(!color.isValid()){
        color = oldColor;
    }
    if(color == oldColor){
        return;
    }
    btn->setStyleSheet("background-color:rgb("+
                       QString::number(color.red())+","+
                       QString::number(color.green())+","+
                       QString::number(color.blue())
                       +");");

    QString dataLavelName(btn->objectName());
    emit QCColorChanged(color,dataLavelName);
    //btn->update();
    qDebug()<<"color: "<<color;
}
