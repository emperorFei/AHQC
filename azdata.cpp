#include "azdata.h"

AZData::AZData():observeTime(QDate(1970,01,01),QTime(00,00)),inited(false)
{

}



AZData::AZData(const AHData &ahData,const ZData &zData):inited(false){
    if(ahData.getObserveTime() != zData.getObserveTime()){
        return;
    }
    this->observeTime = ahData.getObserveTime();
    DataFormatUtil::validateAndExport2AZData(data,ahData.data,zData.data);
    MWW = zData.value("MWW");
    QPair<QString,QString> dataPair("---","---");
    QPair<QPair<QString,QString>,AHQC::DataLevel> pair(dataPair,AHQC::DataLevel::INFO);
    mostSeriousIssue = QPair<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> >("unchecked", pair);
    inited = true;
}


QDateTime AZData::getObserveTime() const
{
    return observeTime;
}

void AZData::setObserveTime(const QDateTime &value)
{
    observeTime = value;
}
