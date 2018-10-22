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
    this->colInfos = xmlProcessor.readColsXml(this->colInfoFileName);



    this->inited =true;
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
