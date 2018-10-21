#include "globalseeting.h"
#include <QResource>
GlobalSetting::GlobalSetting(QObject *parent) : QObject(parent),inited(false)
{
    init();
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
    QResource resource(qApp->applicationDirPath()+"/config.qrc");
    instance->colInfoFileName = resource.absoluteFilePath()+"/configs/ItemCols";
    //colInfoFileName = resource.absoluteFilePath()+"/conf/ItemCols.xml";

    MyXMLProcessor xmlProcessor;
    instance->colInfos = xmlProcessor.readColsXml(instance->colInfoFileName);



    instance->inited =true;
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
