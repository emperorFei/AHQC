#ifndef DATAFORMATUTIL_H
#define DATAFORMATUTIL_H

#include <QMap>

class DataFormatUtil
{
public:
    static QMap<QString,int> zFileData2ZIntData(const QMap<QString,QString> &zFileData);
    static QMap<QString,QString> zFileData2ZStringData(const QMap<QString,QString> &zFileData);
    static void amendZTimeItem(QMap<QString,int> &zIntData);

    static QString zIntData2String(int zIntData);
private:
    DataFormatUtil() = delete;


    static int couldHeightFromZFileData(const QMap<QString,QString> &zFileData);

    static const QString zIntItem[];
    static const QString zStringItem[];
    static const QString zTimeItem[];
};

#endif // DATAFORMATUTIL_H
