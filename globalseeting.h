#ifndef GLOABLSEETING_H
#define GLOABLSEETING_H

#include <QObject>
#include <QApplication>
#include "singleton.h"
#include "simpleobject.h"
#include "xmlProcessor/myxmlprocessor.h"

template<class T> class singleton;


class GlobalSetting : public QObject
{
    Q_OBJECT
friend singleton<GlobalSetting>;

public:
    ~GlobalSetting();
    QString toString();
    static GlobalSetting * getInstance();
private:
    explicit GlobalSetting(QObject *parent = nullptr);
    static void init();
    QList<ColInfo>* colInfos;
    QString colInfoFileName;
    bool inited;
    static GlobalSetting* instance;
signals:

public slots:
};

#endif // GLOABLSEETING_H
