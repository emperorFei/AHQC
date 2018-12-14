#ifndef GLOABLSEETING_H
#define GLOABLSEETING_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "singleton.h"
#include "simpleobject.h"
#include "xmlProcessor/myxmlprocessor.h"
#include <QSettings>


template<class T> class singleton;


class GlobalSetting : public QObject
{
    Q_OBJECT
friend class singleton<GlobalSetting>;
//friend singleton<GlobalSetting>;

public:
    ~GlobalSetting();
    QString toString();
    void sync();
    static GlobalSetting * getInstance();

    QList<ColInfo> *getColInfos() const;
    QString getColInfoFileName() const;
    QVariant value(const QString &itemName);
    void setValue(const QString &key, const QVariant &value,const QString &categoryName);
private:
    QList<ColInfo>* colInfos;
    QString colInfoFileName;
    bool inited;

    QSettings *dataSetting;
    QSettings *uiSetting;



    explicit GlobalSetting(QObject *parent = nullptr);
    GlobalSetting& operator =(const GlobalSetting&) = delete;
    GlobalSetting(const GlobalSetting&) = delete;
    void init();


    static GlobalSetting* instance;

signals:

public slots:
    void confirmSettingChanged();
    void confirmDataSettingChanged();
    void confirmUISettingChanged();
};
//template class singleton<GlobalSetting>;
template<>
class singleton<GlobalSetting>{
protected:
   singleton();
private:
   singleton(const singleton&) = delete;
   singleton& operator=(const singleton&) = delete;
   static GlobalSetting* m_instance ;
   static QMutex mutex;
public:
   static GlobalSetting* GetInstance();
};

#endif // GLOABLSEETING_H
