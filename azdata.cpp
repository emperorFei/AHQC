#include "azdata.h"

AZData::AZData():inited(false)
{

}



AZData::AZData(const AHData &ahData,const ZData &zData):inited(false){
    if(ahData.getObserveTime() != zData.getObserveTime()){
        return;
    }
    this->observeTime = ahData.getObserveTime();
    DataFormatUtil::validateAndExport2AZData(data,ahData.data,zData.data);
    MWW = zData.value("MWW");
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
