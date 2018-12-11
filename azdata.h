#ifndef AZDATA_H
#define AZDATA_H

#include <QPair>
#include <QMap>
#include <QDateTime>
#include "ahdata.h"
#include "zdata.h"
#include "util/simpleutil.h"
#include "util/dataformatutil.h"
class DataFormatUtil;
class FullWidegt;
class AZData
{
friend class DataFormatUtil;
friend class FullWidegt;
public:
    AZData(const AHData &ahData,const ZData &zData);
    QDateTime getObserveTime() const;
    void setObserveTime(const QDateTime &value);

private:
    AZData();
    QDateTime observeTime;
    QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > data;
    QString MWW;
    bool inited = false;
};

#endif // AZDATA_H
