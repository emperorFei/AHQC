#include "settingdialog.h"
#include "ui_settingwidget.h"
QRegExp SettingDialog::colorStringReg("\\d+,\\d+,\\d+");
SettingDialog::SettingDialog(QWidget *parent) :
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
    this->setWindowIcon(QIcon(":/ico/setting"));
//    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
//    ui->closeButton->setIcon(closePix);
    ui->closeButton->setStyleSheet(styleSheet()+QString("\n"
                                           "#closeButton{\n"
                                              "image: url(:/ico/close_normal);\n"
                                           "}\n"
                                           "#closeButton:hover{\n"
                                             "image: url(:/ico/close_hover);\n"
                                           "}\n"
                                       ));
//    ui->minButton->setIcon(minPix);
    ui->minButton->setStyleSheet(styleSheet()+QString("\n"
                                           "#minButton{\n"
                                              "image: url(:/ico/min_normal);\n"
                                           "}\n"
                                           "#minButton:hover{\n"
                                             "image: url(:/ico/min_hover);\n"
                                           "}\n"
                                       ));
    //ui->closeButton->setStyleSheet("QToolButton{border:none;background:rgb(248,248,248)}");



    ui->settingTreeWidget->setExpandsOnDoubleClick(false);


    ui->settingTreeWidget->expandItem(ui->settingTreeWidget->topLevelItem(0));
    ui->settingTreeWidget->setItemSelected(ui->settingTreeWidget->topLevelItem(0)->child(0),true);
    ui->filesys_account_checkBox->setCheckState(Qt::CheckState::Checked);
    ui->main_stackedWidget->setCurrentIndex(0);

    initPages();
    message_cd = new QMessageBox(QMessageBox::NoIcon,"退出设置","设置已变更,是否保存",QMessageBox::StandardButton::NoButton,this);
    message_cd -> addButton(QString::fromUtf8("保存"), QMessageBox::AcceptRole);
    message_cd -> addButton(QString::fromUtf8("直接退出"), QMessageBox::RejectRole);

    connectSingles();

    ui->uiSetting_apply_button->setDisabled(true);
    ui->stationSetting_apply_button->setDisabled(true);
    ui->filePathSetting_apply_button->setDisabled(true);
    ui->dbSetting_apply_button->setDisabled(true);
    ui->catchSetting_apply_button->setDisabled(true);
}




SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::initPages(){



    ui->stationNum_edit->setText(setting->value("stationNum").toString());

    ui->station_height_edit->setText(setting->value("stationHeight").toString());
    ui->presure_height_edit->setText(setting->value("presureHeight").toString());

    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->observeTimes_comboBox);
    ui->observeTimes_comboBox->setItemDelegate(itemDelegate);
    ui->observeTimes_comboBox->addItems(setting->value("observeTimes").toString().replace("-",",").split("<>"));
    ui->observeTimes_comboBox->setCurrentIndex(setting->value("observeTimesCheckedIndex").toInt());

    ui->onTime_sendDelay_edit->setText(setting->value("delayOfOnTime").toString());
    ui->observeTime_sendDelay_edit->setText(setting->value("delayOfObserveTime").toString());


    int shiftTime = setting->value("shiftTime").toInt();
    ui->shiftTime_timeEdit->setTime(QTime(shiftTime/100,shiftTime%100));
    ui->shallowTemperature_cb->setChecked(setting->value("shallowTemperature_cb_check").toBool());
    ui->e_cb->setChecked(setting->value("e_cb_check").toBool());
    ui->cloud_cb->setChecked(setting->value("cloud_cb_check").toBool());
    ui->wd_cb->setChecked(setting->value("wd_cb_check").toBool());
    ui->extremum12_cb->setChecked(setting->value("extremum12_cb_check").toBool());

    ui->isospath_lineEdit->setText(setting->value("ISOSPath").toString());
    ui->filesys_account_checkBox->setChecked(setting->value("ISOSPathNeedAccount").toBool());
    ui->filesys_username_edit->setText(setting->value("ISOSPathUsername").toString());
    ui->filesys_password_edit->setText(setting->value("ISOSPathPassword").toString());
    ui->db_address_edit->setText(setting->value("dbHost").toString());
    ui->db_port_edit->setText(setting->value("dbPort").toString());
    ui->db_databaseName_edit->setText(setting->value("dbName").toString());
    ui->db_account_edit->setText(setting->value("dbAccount").toString());
    ui->db_password_edit->setText(setting->value("dbPassword").toString());

    QRegExpValidator *rv4Height = new QRegExpValidator(QRegExp("^-?(90|[1-8]?\\d(\\.\\d{1,2})?)$"),this);
    QIntValidator *iv4StationNum = new QIntValidator(1,99999,this);
    QIntValidator *iv4SendDelay = new QIntValidator(0,300,this);
    QIntValidator *iv4DBPort = new QIntValidator(0,65535,this);

    ui->stationNum_edit->setValidator(iv4StationNum);
    ui->station_height_edit->setValidator(rv4Height);
    ui->presure_height_edit->setValidator(rv4Height);
    ui->onTime_sendDelay_edit->setValidator(iv4SendDelay);
    ui->observeTime_sendDelay_edit->setValidator(iv4SendDelay);
    ui->db_port_edit->setValidator(iv4DBPort);

    if(setting->value("isISOSPathLocal").toBool() == true){
        ui->localpath_radioButton->click();
    }else{
        ui->netpath_radioButton->click();
    }
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


void SettingDialog::sltTreeWidget_itemExpanded(QTreeWidgetItem *item)
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

void SettingDialog::sltTreeWidget_itemPressed(QTreeWidgetItem * item,int column)
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

void SettingDialog::sltNavigation_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous){
    Q_UNUSED(previous);
    if(current != Q_NULLPTR){
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
    }
}

void SettingDialog::sltCloseButtonClicked(bool checked)
{
    Q_UNUSED(checked);

    this->close();

}
void SettingDialog::sltMinButtonClicked(bool checked)
{
    Q_UNUSED(checked);

    this->showMinimized();

}


void SettingDialog::navigationTreeIndent(){
    QTreeWidgetItemIterator it( ui->settingTreeWidget);
    int nCount = ui->settingTreeWidget->topLevelItemCount();
    ui->settingTreeWidget->setIndentation(1);

}




void SettingDialog::connectSingles(){
    this->connect(ui->settingTreeWidget,
                  SIGNAL(itemPressed(QTreeWidgetItem *,int)),
                  this,
                  SLOT(sltTreeWidget_itemPressed(QTreeWidgetItem *,int)));
    this->connect(ui->settingTreeWidget,
                  SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
                  this,
                  SLOT(sltNavigation_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));


    this->connect(ui->minButton,&QPushButton::clicked,this,&SettingDialog::sltMinButtonClicked);
    this->connect(ui->closeButton,&QPushButton::clicked,this,&SettingDialog::sltCloseButtonClicked);
    connect(ui->uiSetting_confirm_button,&QPushButton::clicked,this,&SettingDialog::sltConfrimButtonClicked);
    connect(ui->dbSetting_confirm_button,&QPushButton::clicked,this,&SettingDialog::sltConfrimButtonClicked);
    connect(ui->filePathSetting_confirm_button,&QPushButton::clicked,this,&SettingDialog::sltConfrimButtonClicked);
    connect(ui->stationSetting_confirm_button,&QPushButton::clicked,this,&SettingDialog::sltConfrimButtonClicked);
    connect(ui->catchSetting_confirm_button,&QPushButton::clicked,this,&SettingDialog::sltConfrimButtonClicked);

    connect(ui->uiSetting_cancel_button,&QPushButton::clicked,this,&SettingDialog::sltCancelButtonClicked);
    connect(ui->dbSetting_cancel_button,&QPushButton::clicked,this,&SettingDialog::sltCancelButtonClicked);
    connect(ui->filePathSetting_cancel_button,&QPushButton::clicked,this,&SettingDialog::sltCancelButtonClicked);
    connect(ui->stationSetting_cancel_button,&QPushButton::clicked,this,&SettingDialog::sltCancelButtonClicked);
    connect(ui->catchSetting_cancel_button,&QPushButton::clicked,this,&SettingDialog::sltCancelButtonClicked);

    connect(ui->uiSetting_apply_button,&QPushButton::clicked,this,&SettingDialog::sltApplyButtonClicked);
    connect(ui->dbSetting_apply_button,&QPushButton::clicked,this,&SettingDialog::sltApplyButtonClicked);
    connect(ui->filePathSetting_apply_button,&QPushButton::clicked,this,&SettingDialog::sltApplyButtonClicked);
    connect(ui->stationSetting_apply_button,&QPushButton::clicked,this,&SettingDialog::sltApplyButtonClicked);
    connect(ui->catchSetting_apply_button,&QPushButton::clicked,this,&SettingDialog::sltApplyButtonClicked);

    connectUISettingPageSingles();
    connectFilePathSettingPageSingles();
    connectDBSettingPageSingles();
    connectStationSettingPageSingles();
    connectCacheSettingPageSingles();
}

void SettingDialog::connectUISettingPageSingles(){
    connect(ui->missingColor_btn,
            &QPushButton::clicked,
            this,
            &SettingDialog::sltColorBtnClicled);
    connect(ui->errorColor_btn,
            &QPushButton::clicked,
            this,
            &SettingDialog::sltColorBtnClicled);
    connect(ui->suspectedColor_btn,
            &QPushButton::clicked,
            this,
            &SettingDialog::sltColorBtnClicled);
    connect(ui->shallowTemperature_cb,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->e_cb,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->cloud_cb,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->wd_cb,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->extremum12_cb,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);

}
void SettingDialog::connectFilePathSettingPageSingles(){
    this->connect(ui->filepath_switch_buttonGroup,
                  SIGNAL(buttonToggled(QAbstractButton *, bool)),
                  this,
                  SLOT(sltPathSwitchButtonToggled(QAbstractButton *, bool)));
    this->connect(ui->filesys_account_checkBox,
                  SIGNAL(stateChanged(int)),
                  this,
                  SLOT(sltFilesysAccountCheckBoxStateChanged(int)));
    this->connect(ui->isospath_change_btn,
                  SIGNAL(clicked(bool)),
                  this,
                  SLOT(sltIsospathChangeButtonClicked(bool)));

    this->connect(ui->isospath_lineEdit,
                  SIGNAL(editingFinished()),
                  this,
                  SLOT(sltIsospathLineEditTextChanged()));
    this->connect(ui->isospath_lineEdit,
                  SIGNAL(editingFinished()),
                  this,
                  SLOT(sltIsospathLineEditTextChanged()));
    connect(ui->localpath_radioButton,
            &QRadioButton::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->netpath_radioButton,
            &QRadioButton::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->isospath_lineEdit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->filesys_account_checkBox,
            &QCheckBox::clicked,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->filesys_password_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->filesys_username_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
}
void SettingDialog::connectDBSettingPageSingles(){
    connect(ui->db_address_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->db_port_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->db_databaseName_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->db_account_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->db_password_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
}
void SettingDialog::connectStationSettingPageSingles(){
    connect(ui->station_height_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->presure_height_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->onTime_sendDelay_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->observeTime_sendDelay_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->stationNum_edit,
            &QLineEdit::textChanged,
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->observeTimes_comboBox,
            static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,
            &SettingDialog::sltAnySettingChanged);
    connect(ui->shiftTime_timeEdit,
            &QTimeEdit::timeChanged,
            this,
            &SettingDialog::sltAnySettingChanged);

}
void SettingDialog::connectCacheSettingPageSingles(){

}

void SettingDialog::sltPathSwitchButtonToggled(QAbstractButton *button, bool checked){
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



void SettingDialog::sltFilesysAccountCheckBoxStateChanged(int state){
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

void SettingDialog::sltIsospathChangeButtonClicked(bool checked){
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
    if (!directory.isEmpty()) {
            ui->isospath_lineEdit->setText(directory);
    }
    sltIsospathLineEditTextChanged();

}

void SettingDialog::sltIsospathLineEditTextChanged(){
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
              return ;
            }
        }
    }
    ui->isospath_lineEdit->setText("invalidpath");
}

void SettingDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = event->pos();
    }
}

void SettingDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void SettingDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed && (event->buttons() && Qt::LeftButton))
    {
        this->move(event->globalPos() - mousePoint);
        event->accept();
    }
}
void SettingDialog::sltColorBtnClicled(bool){
    QPushButton* btn = static_cast<QPushButton*>(sender());
    QColor oldColor = btn->palette().background().color();
    QString tip("");
    if(btn->objectName() == "missingColor_btn"){
        tip = "缺测";
    }else if(btn->objectName() == "suspectedColor_btn"){
        tip = "疑误";
    }else{
        tip = "错误";
    }
    QString titelString = "请选择"+tip+"信息质控颜色";
    QColor color = QColorDialog::getColor(oldColor,this,
                                              tr(titelString.toStdString().c_str()));
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
    btn->update();
    QColor missingColor = ui->missingColor_btn->palette().background().color();
    QColor suspectColor = ui->suspectedColor_btn->palette().background().color();
    QColor errorColor = ui->errorColor_btn->palette().background().color();
    QString missingColorRgbString("rgb("+
                                      QString::number(missingColor.red())+","+
                                      QString::number(missingColor.green())+","+
                                      QString::number(missingColor.blue())
                                      +")");
    QString suspectColorRgbString("rgb("+
                                      QString::number(suspectColor.red())+","+
                                      QString::number(suspectColor.green())+","+
                                      QString::number(suspectColor.blue())
                                      +")");
    QString errorColorRgbString("rgb("+
                                      QString::number(errorColor.red())+","+
                                      QString::number(errorColor.green())+","+
                                      QString::number(errorColor.blue())
                                      +")");
    emit QCColorChanged(missingColorRgbString,suspectColorRgbString,errorColorRgbString);
    sltAnySettingChanged();
}


void SettingDialog::sltAnySettingChanged(){
    ui->uiSetting_apply_button->setEnabled(true);
    ui->stationSetting_apply_button->setEnabled(true);
    ui->filePathSetting_apply_button->setEnabled(true);
    ui->dbSetting_apply_button->setEnabled(true);
    ui->catchSetting_apply_button->setEnabled(true);
}


void SettingDialog::sltConfrimButtonClicked(bool){

    validateUISetting(true);
    validateDBSetting(true);
    validateFilesysSetting(true);
    validateStationSetting(true);
    validateCatchSetting(true);
    setting->sync();

    ui->uiSetting_apply_button->setDisabled(true);
    ui->stationSetting_apply_button->setDisabled(true);
    ui->filePathSetting_apply_button->setDisabled(true);
    ui->dbSetting_apply_button->setDisabled(true);
    ui->catchSetting_apply_button->setDisabled(true);

    this->close();
}
void SettingDialog::sltCancelButtonClicked(bool){

    validateUISetting(false);
    validateDBSetting(false);
    validateFilesysSetting(false);
    validateStationSetting(false);
    validateCatchSetting(false);

    ui->uiSetting_apply_button->setDisabled(true);
    ui->stationSetting_apply_button->setDisabled(true);
    ui->filePathSetting_apply_button->setDisabled(true);
    ui->dbSetting_apply_button->setDisabled(true);
    ui->catchSetting_apply_button->setDisabled(true);

    this->close();
}
void SettingDialog::sltApplyButtonClicked(bool){
    validateUISetting(true);
    validateDBSetting(true);
    validateFilesysSetting(true);
    validateStationSetting(true);
    validateCatchSetting(true);

    ui->uiSetting_apply_button->setDisabled(true);
    ui->stationSetting_apply_button->setDisabled(true);
    ui->filePathSetting_apply_button->setDisabled(true);
    ui->dbSetting_apply_button->setDisabled(true);
    ui->catchSetting_apply_button->setDisabled(true);
}



void SettingDialog::validateUISetting(bool forConfirm){
    QString styleOfMissingColor_btn = ui->missingColor_btn->styleSheet();
    QString styleOfSuspectColor_btn = ui->suspectedColor_btn->styleSheet();
    QString styleOfErrorColor_btn = ui->errorColor_btn->styleSheet();
    int index = colorStringReg.indexIn(styleOfMissingColor_btn);
    int len = colorStringReg.matchedLength();
    QString mColor = styleOfMissingColor_btn.mid(index,len);
    index = colorStringReg.indexIn(styleOfSuspectColor_btn);
    len = colorStringReg.matchedLength();
    QString sColor = styleOfSuspectColor_btn.mid(index,len);
    index = colorStringReg.indexIn(styleOfErrorColor_btn);
    len = colorStringReg.matchedLength();
    QString eColor = styleOfErrorColor_btn.mid(index,len);
    mColor.replace(",","-");
    sColor.replace(",","-");
    eColor.replace(",","-");
    if(forConfirm){
        if(mColor != setting->value("missingColor").toString().trimmed() ||
                sColor != setting->value("suspectColor").toString().trimmed() ||
                eColor != setting->value("errorColor").toString().trimmed()){
            setting->setValue("missingColor",mColor,"ui");
            setting->setValue("suspectColor",sColor,"ui");
            setting->setValue("errorColor",eColor,"ui");
            emit QCColrConfirmChanged();
        }
        bool shallowTemperature_cb_check_setting = setting->value("shallowTemperature_cb_check").toBool();
        bool shallowTemperature_cb_check_ui = ui->shallowTemperature_cb->isChecked();
        bool e_cb_check_setting = setting->value("e_cb_check").toBool();
        bool e_cb_check_ui = ui->e_cb->isChecked();
        bool cloud_cb_check_setting = setting->value("cloud_cb_check").toBool();
        bool cloud_cb_check_ui = ui->cloud_cb->isChecked();
        bool wd_cb_check_setting = setting->value("wd_cb_check").toBool();
        bool wd_cb_check_ui = ui->wd_cb->isChecked();
        bool extremum12_cb_check_setting = setting->value("extremum12_cb_check").toBool();
        bool extremum12_cb_check_ui = ui->extremum12_cb->isChecked();
        if(shallowTemperature_cb_check_setting != shallowTemperature_cb_check_ui ||
            e_cb_check_setting != e_cb_check_ui ||
            cloud_cb_check_setting != cloud_cb_check_ui ||
            wd_cb_check_setting != wd_cb_check_ui ||
            extremum12_cb_check_setting != extremum12_cb_check_ui
                ){
            setting->setValue("shallowTemperature_cb_check",shallowTemperature_cb_check_ui,"ui");
            setting->setValue("e_cb_check",e_cb_check_ui,"ui");
            setting->setValue("cloud_cb_check",cloud_cb_check_ui,"ui");
            setting->setValue("wd_cb_check",wd_cb_check_ui,"ui");
            setting->setValue("extremum12_cb_check",extremum12_cb_check_ui,"ui");
            emit QCItemsChanged();
        }
    }else{
        QString mColor_setting = setting->value("missingColor").toString().trimmed();
        QString sColor_setting = setting->value("suspectColor").toString().trimmed();
        QString eColor_setting = setting->value("errorColor").toString().trimmed();
        if(mColor != mColor_setting ||
                sColor != sColor_setting ||
                eColor != eColor_setting){
            mColor_setting.replace("-",",");
            sColor_setting.replace("-",",");
            eColor_setting.replace("-",",");
            ui->missingColor_btn->setStyleSheet(QString("background-color: ")+"rgb("+mColor_setting+");");
            ui->suspectedColor_btn->setStyleSheet(QString("background-color: ")+"rgb("+sColor_setting+");");
            ui->errorColor_btn->setStyleSheet(QString("background-color: ")+"rgb("+eColor_setting+");");
            ui->missingColor_btn->update();
            ui->suspectedColor_btn->update();
            ui->errorColor_btn->update();
            emit QCColrConfirmChanged();
        }
        ui->shallowTemperature_cb->setChecked(setting->value("shallowTemperature_cb_check").toBool());
        ui->e_cb->setChecked(setting->value("e_cb_check").toBool());
        ui->cloud_cb->setChecked(setting->value("cloud_cb_check").toBool());
        ui->wd_cb->setChecked(setting->value("wd_cb_check").toBool());
        ui->extremum12_cb->setChecked(setting->value("extremum12_cb_check").toBool());
    }
}
void SettingDialog::validateDBSetting(bool forConfirm){
    QString dbAddress_ui = ui->db_address_edit->text();
    int dbPort_ui = ui->db_port_edit->text().toInt();
    QString dbName_ui = ui->db_databaseName_edit->text();
    QString dbAccount_ui = ui->db_account_edit->text();
    QString dbPassword_ui = ui->db_password_edit->text();

    if(forConfirm){
        setting->setValue("dbHost",dbAddress_ui,"data");
        setting->setValue("dbPort",dbPort_ui,"data");
        setting->setValue("dbName",dbName_ui,"data");
        setting->setValue("dbAccount",dbAccount_ui,"data");
        setting->setValue("dbPassword",dbPassword_ui,"data");
    }else{
        ui->db_address_edit->setText(setting->value("dbHost").toString());
        ui->db_port_edit->setText(setting->value("dbPort").toString());
        ui->db_databaseName_edit->setText(setting->value("dbName").toString());
        ui->db_account_edit->setText(setting->value("dbAccount").toString());
        ui->db_password_edit->setText(setting->value("dbPassword").toString());
    }
}
void SettingDialog::validateFilesysSetting(bool forConfirm){
    bool isISOSPathLocal_ui = ui->localpath_radioButton->isChecked();
    QString ISOSPath_ui = ui->isospath_lineEdit->text();
    bool ISOSPathNeedAccount_ui = ui->filesys_account_checkBox->isChecked();
    QString ISOSPathUsername_ui = ui->filesys_username_edit->text();
    QString ISOSPathPassword_ui = ui->filesys_password_edit->text();

    if(forConfirm){
        setting->setValue("isISOSPathLocal",isISOSPathLocal_ui,"data");
        setting->setValue("ISOSPath",ISOSPath_ui,"data");
        setting->setValue("ISOSPathNeedAccount",ISOSPathNeedAccount_ui,"data");
        setting->setValue("ISOSPathUsername",ISOSPathUsername_ui,"data");
        setting->setValue("ISOSPathPassword",ISOSPathPassword_ui,"data");
    }else{
        ui->isospath_lineEdit->setText(setting->value("ISOSPath").toString());
        if(setting->value("isISOSPathLocal").toBool()){
            ui->localpath_radioButton->setChecked(true);
            ui->netpath_radioButton->setChecked(false);
        }else{
            ui->localpath_radioButton->setChecked(false);
            ui->netpath_radioButton->setChecked(true);
        }
        ui->isospath_lineEdit->setText(setting->value("ISOSPath").toString());
        ui->filesys_account_checkBox->setChecked(setting->value("ISOSPathNeedAccount").toBool());
        ui->filesys_username_edit->setText(setting->value("ISOSPathUsername").toString());
        ui->filesys_password_edit->setText(setting->value("ISOSPathPassword").toString());
    }

}
void SettingDialog::validateStationSetting(bool forConfirm){
    double stationHeight_ui = ui->station_height_edit->text().toDouble();
    double presureHeight_ui = ui->presure_height_edit->text().toDouble();
    QString stationNum_ui = ui->stationNum_edit->text();
    int observeTimesCheckedIndex_ui = ui->observeTimes_comboBox->currentIndex();
    int shiftTime_ui = ui->shiftTime_timeEdit->time().toString("HHmm").toInt();
    int delayOfOnTime_ui = ui->onTime_sendDelay_edit->text().toInt();
    int delayOfObserveTime_ui = ui->observeTime_sendDelay_edit->text().toInt();

    if(forConfirm){
        setting->setValue("stationHeight",stationHeight_ui,"data");
        setting->setValue("presureHeight",presureHeight_ui,"data");
        setting->setValue("stationNum",stationNum_ui,"data");
        setting->setValue("observeTimesCheckedIndex",observeTimesCheckedIndex_ui,"data");
        setting->setValue("shiftTime",shiftTime_ui,"data");
        setting->setValue("delayOfOnTime",delayOfOnTime_ui,"data");
        setting->setValue("delayOfObserveTime",delayOfObserveTime_ui,"data");
    }else{
        ui->station_height_edit->setText(setting->value("stationHeight").toString());
        ui->presure_height_edit->setText(setting->value("presureHeight").toString());
        ui->stationNum_edit->setText(setting->value("stationNum").toString());
        ui->observeTimes_comboBox->setCurrentIndex(setting->value("observeTimesCheckedIndex").toInt());
        int shiftTime = setting->value("shiftTime").toInt();
        ui->shiftTime_timeEdit->setTime(QTime(shiftTime/100,shiftTime %100));
        ui->onTime_sendDelay_edit->setText(setting->value("delayOfOnTime").toString());
        ui->observeTime_sendDelay_edit->setText(setting->value("delayOfObserveTime").toString());
    }
}
void SettingDialog::validateCatchSetting(bool forConfirm){
    Q_UNUSED(forConfirm)
}
void SettingDialog::closeEvent(QCloseEvent *event){
    if(ui->dbSetting_apply_button->isEnabled()){
        if(message_cd->exec() == QMessageBox::AcceptRole){
            sltConfrimButtonClicked(true);
            event->accept();
        }else{
            sltCancelButtonClicked(true);
            event->accept();
        }
    }else{
        event->accept();
    }
}
