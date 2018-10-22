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
friend class singleton<GlobalSetting>;
//friend singleton<GlobalSetting>;

public:
    ~GlobalSetting();
    QString toString();
    static GlobalSetting * getInstance();

    QList<ColInfo> *getColInfos() const;

    QString getColInfoFileName() const;

private:
    explicit GlobalSetting(QObject *parent = nullptr);
    GlobalSetting& operator =(const GlobalSetting&) = delete;
    GlobalSetting(const GlobalSetting&) = delete;
    void init();
    QList<ColInfo>* colInfos;
    QString colInfoFileName;
    bool inited;
    static GlobalSetting* instance;
signals:

public slots:
};

template<>
class singleton<GlobalSetting>{
protected:
   singleton();
private:
   singleton(const singleton&) = delete;
   singleton& operator=(const singleton&) = delete;
   //(const singleton&){}
   static GlobalSetting* m_instance ;
   static QMutex mutex;
public:
   static GlobalSetting* GetInstance();
};
#endif // GLOABLSEETING_H
