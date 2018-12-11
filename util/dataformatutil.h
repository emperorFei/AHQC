#ifndef DATAFORMATUTIL_H
#define DATAFORMATUTIL_H

#include <QMap>
#include <QRegExp>
#include "simpleutil.h"
class ZDataDAOMysqlImp;
class DataFormatUtil
{
friend class ZDataDAOMysqlImp;
public:
//    static QMap<QString,int> zFileData2ZIntData(const QMap<QString,QString> &zFileData);
//    static QMap<QString,QString> zFileData2ZStringData(const QMap<QString,QString> &zFileData);
//    static void amendZTimeItem(QMap<QString,int> &zIntData);

//    static QString zIntData2String(int zIntData);

    static QMap<QString,QString> zFileContent2zData(const QString &zFileContent);
    static void validateAndExport2AZData(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                                  const QMap<QString, int> &ahData,
                                  const QMap<QString, QString> &zData);
private:
    DataFormatUtil() = delete;


    //static int couldHeightFromZFileData(const QMap<QString,QString> &zFileData);

    static QString removeZFileSectionID(const QString &zFileContent);
    static QMap<QString,QString> zFileDataString2zFileData(const QString &zFileDataString);
    static void validateWD();
    static void validateTimeItems();




    static void validateSimpleItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                           QMap<QString,int> &ahData,
                           QMap<QString,QString> &zData);
    static void validateTimeItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                            QMap<QString,int> &ahData,
                            QMap<QString,QString> &zData);
    static void validateWD(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                           QMap<QString,int> &ahData,
                           QMap<QString,QString> &zData);
    static void validateRain(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                            QMap<QString,int> &ahData,
                            QMap<QString,QString> &zData);
    static void validateManualItems(QMap<QString,QPair<QPair<QString,QString>,AHQC::DataLevel> > &data,
                            QMap<QString,int> &ahData,
                            QMap<QString,QString> &zData);

    static void ahItemMinusThousand(QMap<QString,int> &ahData);
    static void zItemMinusByThousand(QMap<QString,QString> &zData);
    static void zTime2LocalTime(QMap<QString,QString> &zData);
    static const QString zIntItem[];
    static const QString zStringItem[];
    static const QString zDBItem[];
    static const QString zFileItem[];

    static const QString AHDataAndZData[];
    static const QString UIComponentName[];
    static const QString itemsOnlyInAHData[];
    static const QString itemsOnlyInZData[];

    static const QString simpleValidteItems_3Byte[];
    static const QString simpleValidteItems_4Byte[];
    static const QString simpleValidteItems_5Byte[];
    static const QString rainItems[];
    static const QString zTimeItem[];
    static const QString zManualItems[];
    static const QString zWindDirectionItems[];
    static const QString zItemsShouldMinusByThousand[];
    static const QString ahItemsShouldMinusThousand[];

    static const QString zFileSectionID[];
    static const QRegExp mwReg;
};

#endif // DATAFORMATUTIL_H
