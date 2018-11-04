#ifndef DATAFORMATUTIL_H
#define DATAFORMATUTIL_H

#include <QMap>

class DataFormatUtil
{
public:
//    static QMap<QString,int> zFileData2ZIntData(const QMap<QString,QString> &zFileData);
//    static QMap<QString,QString> zFileData2ZStringData(const QMap<QString,QString> &zFileData);
//    static void amendZTimeItem(QMap<QString,int> &zIntData);

//    static QString zIntData2String(int zIntData);

    static QMap<QString,QString> zFileContent2zData(const QString &zFileContent);
private:
    DataFormatUtil() = delete;


    //static int couldHeightFromZFileData(const QMap<QString,QString> &zFileData);

    static QString removeZFileSectionID(const QString &zFileContent);
    static QMap<QString,QString> zFileDataString2zFileData(const QString &zFileDataString);

    static const QString zIntItem[];
    static const QString zStringItem[];
    static const QString zTimeItem[];
    static const QString zDBItem[];
    static const QString zFileItem[];
    static const QString zFileSectionID[];
};

#endif // DATAFORMATUTIL_H
