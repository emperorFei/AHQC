#include "globalseeting.h"
#include <QResource>
QDateTime unInitTime(QDateTime::fromString("19700101000000","yyyyMMddHHmmss"));
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
    this->colInfoFileName = ":/conf/ItemCols";
    MyXMLProcessor xmlProcessor;
    this -> colInfos = xmlProcessor.readColsXml(this->colInfoFileName);
    this->dataSetting = new QSettings("configs/dataSetting.ini",QSettings::IniFormat);
    this->uiSetting = new QSettings("configs/uiSetting.ini",QSettings::IniFormat);
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

QVariant GlobalSetting::value(const QString &itemName){
    if(dataSetting->contains(itemName)){
        return dataSetting->value(itemName);
    }else if(uiSetting->contains(itemName)){
        return uiSetting->value(itemName);
    }
    return QVariant();
}
void GlobalSetting::setValue(const QString &key, const QVariant &value,const QString &categoryName){
    if(categoryName == "ui"){
        uiSetting->setValue(key,value);
    }else if(categoryName == "data"){
        dataSetting->setValue(key,value);
    }
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
void GlobalSetting::sync(){
    uiSetting->sync();
    dataSetting->sync();
}
