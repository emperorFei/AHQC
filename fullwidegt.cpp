#include "fullwidegt.h"
#include "ui_fullwidegt.h"
const QString FullWidegt::doubleLabelNames[] =
{
    "CA_DL","CH_DL","E_DL","ET_DL","ET10_DL","ET15_DL","ET160_DL","ET20_DL","ET320_DL",
    "ET40_DL","ET5_DL","ET80_DL","ExWD_DL","ExWD12_DL","ExWD6_DL","ExWS_DL","ExWS12_DL",
    "ExWS6_DL","ExWST_DL","GT_DL",
    "HRain_DL","HRain12_DL","HRain24_DL",
    "HRain3_DL","HRain6_DL","LCA_DL",
    "MaxET_DL","MaxETT_DL","MaxGT_DL","MaxGTT_DL",
    "MaxP_DL","MaxPT_DL","MaxT_DL","MaxT24_DL","MaxTT_DL",
    "MaxWD_DL","MaxWS_DL","MaxWST_DL","MinET_DL","MinET12_DL",
    "MinETT_DL","MinGT_DL","MinGTT_DL","MinP_DL","MinPT_DL","MinRH_DL",
    "MinRHT_DL","MinT_DL","MinT24_DL","MinTT_DL","MinV_DL",
    "MinVT_DL","P_DL","RH_DL","SP_DL","SnowD_DL","T_DL",
    "TD_DL","V1_DL","V10_DL","VP24_DL","VP3_DL","VT24_DL",
    "WD_DL","WD10_DL","WD2_DL","WP_DL","WS_DL","WS10_DL","WS2_DL",
    "CCX_DL","CF_DL","CFC_DL","EC_DL","FE1D_DL","FE1U_DL","FE2D_DL","FE2U_DL","GA_DL","HA_DL"
};
FullWidegt::FullWidegt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullWidegt)
{
    ui->setupUi(this);
}
FullWidegt::FullWidegt(const AZData &azData,QWidget *parent) :
    QWidget(parent),
    observeTime(azData.getObserveTime()),
    ui(new Ui::FullWidegt)
{
    ui->setupUi(this);
    initFromAZData(azData);
    setQCWarn();
    QFont font("宋体");
    font.setPointSize(15);
    setDoubleLabelFont(font);

}

FullWidegt::~FullWidegt()
{
    delete ui;
}

void FullWidegt::initFromAZData(const AZData &azData)
{
    this->observeTime = azData.observeTime;
    ui->time_lb->setText(observeTime.toString("yyyy/MM/dd HH"));
    QList<QString> keys = azData.data.keys();
    QString doubleLabelName("");
    QString dataItemName("");
    AHQC::DataLevel dataLeval = AHQC::DataLevel::INFO;
    MyDoubleLabel::Leval level = MyDoubleLabel::Leval::INFO;
    for(const QString &key :keys){
        doubleLabelName = key + "_DL";
        MyDoubleLabel * doubleLabel = this->findChild<MyDoubleLabel *>(doubleLabelName);
        doubleLabel -> setDataName(key);
        doubleLabel -> setText(azData.data.value(key).first);
        dataLeval = azData.data.value(key).second;
        switch(dataLeval){
            case AHQC::DataLevel::INFO :
                level = MyDoubleLabel::Leval::INFO;
                break;
            case AHQC::DataLevel::SUSPECTED :
                level = MyDoubleLabel::Leval::SUSPECTED;
                break;
            case AHQC::DataLevel::CLASH :
                level = MyDoubleLabel::Leval::CLASH ;
                qDebug() << observeTime.toString("yyyyMMddHH") << " " << doubleLabel->getDataName() << " CLASH.";
                break;
            case AHQC::DataLevel::MISSING:
                level = MyDoubleLabel::Leval::MISSING;
                qDebug() << observeTime.toString("yyyyMMddHH") << " " << doubleLabel->getDataName() << " MISSING.";

                break;
            case AHQC::DataLevel::MISSINGZDATA :
                level = MyDoubleLabel::Leval::MISSINGZDATA;
                break;
            case AHQC::DataLevel::MISSINGAMDATA :
                level = MyDoubleLabel::Leval::MISSINGAMDATA;
                break;
            case AHQC::DataLevel::ERROR :
                level = MyDoubleLabel::Leval::ERROR;
                break;
        }
        doubleLabel->setLevel(level);
    }
}

const QFont &FullWidegt::doubleLabelfont() const{
    return ui->CA_DL->font();
}
void FullWidegt::setDoubleLabelFont(const QFont &font){
    for(const QString &dlName : doubleLabelNames){
        MyDoubleLabel * doubleLabel = this->findChild<MyDoubleLabel *>(dlName);
        doubleLabel->setFont(font);
    }
}

void FullWidegt::setQCWarn(){
    for(const QString &dlName :doubleLabelNames){
        MyDoubleLabel * doubleLabel = this->findChild<MyDoubleLabel *>(dlName);
        MyDoubleLabel::Leval level = doubleLabel->getLevel();
        switch(level){
        case MyDoubleLabel::Leval::MISSING:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:red;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::CLASH:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:orange;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::MISSINGAMDATA:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:#0F0F0F;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::MISSINGZDATA:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:#FF05FF;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::ERROR:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:darkred;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::SUSPECTED:
            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
                                       "#"+doubleLabel->objectName()+"{"
                                       "border-style:solid;"
                                       "border-width:2;"
                                       "border-color:yellow;"
                                       "border-radius:6;"
                                       "}");
            break;
        case MyDoubleLabel::Leval::INFO:
//            doubleLabel->setStyleSheet(doubleLabel->styleSheet()+
//                                       "#"+doubleLabel->objectName()+"{"
//                                       "border-style:solid;"
//                                       "border-width:2;"
//                                       "border-color:lightgrey;"
//                                       "border-radius:6;"
//                                       "}");
            break;
        }
    }
}
