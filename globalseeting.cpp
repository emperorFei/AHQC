#include "globalseeting.h"
#include <QResource>
GlobalSetting *GlobalSetting::instance = Q_NULLPTR;
GlobalSetting::GlobalSetting(QObject *parent) : QObject(parent),inited(false)
{
    init();
    instance = this;
}
GlobalSetting::~GlobalSetting()
{
    //qDeleteAll(colInfos->begin(),colInfos->end());
    colInfos->clear();
    delete colInfos;
    delete dataSetting;
    delete uiSetting;
}

GlobalSetting* GlobalSetting::getInstance(){
    //instance = singleton<GlobalSetting>::GetInstance();
    return instance;
}
void GlobalSetting::init(){

    //QResource::registerResource(qApp->applicationDirPath() + "/skin/skin.rcc");
//    QResource resource(qApp->applicationDirPath()+"/config.qrc");
//    instance->colInfoFileName = resource.absoluteFilePath()+"/configs/ItemCols";
    //colInfoFileName = resource.absoluteFilePath()+"/conf/ItemCols.xml";
    this->colInfoFileName = "F:/GitRepository/OFFICE_AHQC/configs/ItemCols.xml";
    MyXMLProcessor xmlProcessor;
    this -> colInfos = xmlProcessor.readColsXml(this->colInfoFileName);
    this -> dbHostName = "10.126.148.92";
    this -> dbPort = 3306;
    this -> databaseName = "tempDB";
    this -> pressureHeight = 6.4;
    this -> intDataNum = 47;

    this->dataSetting = new QSettings("configs/dataSetting.ini");
    this->uiSetting = new QSettings("configs/uiSetting.ini");

    this->inited =true;
}

void GlobalSetting::confirmSettingChanged(){
    confirmUISettingChanged();
    confirmDataSettingChanged();
}

void GlobalSetting::confirmDataSettingChanged(){

}

void GlobalSetting::confirmUISettingChanged(){

}

QString GlobalSetting::value(const QString &itemName){
    if(dataSetting->contains(itemName)){
        return dataSetting->value(itemName).toString();
    }else if(uiSetting->contains(itemName)){
        return uiSetting->value(itemName).toString();
    }
    return QString();
}


int GlobalSetting::getDBPort() const
{
    return dbPort;
}

QString GlobalSetting::getDatabaseName() const
{
    return databaseName;
}

double GlobalSetting::getPressureHeight() const
{
    return pressureHeight;
}

int GlobalSetting::getIntDataNum() const
{
    return intDataNum;
}



QString GlobalSetting::getDBHostName() const
{
    return dbHostName;
}

QString GlobalSetting::getColInfoFileName() const
{
    return colInfoFileName;
}

QList<ColInfo> *GlobalSetting::getColInfos() const
{
    return colInfos;
}
QString GlobalSetting::toString(){
    if(inited){
        QString colInfoString("ColInfos: ");
        for(ColInfo cInfos : *colInfos){
            //colInfoString << qSetFieldWidth(1) << "\n";
            colInfoString += cInfos.toString()+"\n";
        }
        return "colInfoFileName: "+colInfoFileName+"\n"+
                "colInfos: "+colInfoString;
    }else{
        return "Haven't inited";
    }
}

//template <>
GlobalSetting* singleton<GlobalSetting>::m_instance = Q_NULLPTR;

//template <>
QMutex singleton<GlobalSetting>::mutex(QMutex::RecursionMode::Recursive);

GlobalSetting* singleton<GlobalSetting>::GetInstance(){
    if(m_instance == Q_NULLPTR){
        mutex.lock();
        if(m_instance == Q_NULLPTR){
            GlobalSetting* ptemp = new GlobalSetting();
            m_instance = ptemp;
        }
        mutex.unlock();
    }
    return m_instance;
}
