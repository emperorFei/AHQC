#include "mydoublelabel.h"
#include "mydoublelabelplugin.h"

#include <QtPlugin>

MyDoubleLabelPlugin::MyDoubleLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MyDoubleLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MyDoubleLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MyDoubleLabelPlugin::createWidget(QWidget *parent)
{
    return new MyDoubleLabel(parent);
}

QString MyDoubleLabelPlugin::name() const
{
    return QLatin1String("MyDoubleLabel");
}

QString MyDoubleLabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon MyDoubleLabelPlugin::icon() const
{
    return QIcon(QLatin1String(":/doubleLabel.ico"));
}

QString MyDoubleLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MyDoubleLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MyDoubleLabelPlugin::isContainer() const
{
    return false;
}

QString MyDoubleLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MyDoubleLabel\" name=\"myDoubleLabel\">\n</widget>\n");
}

QString MyDoubleLabelPlugin::includeFile() const
{
    return QLatin1String("mydoublelabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(mydoublelabelplugin, MyDoubleLabelPlugin)
#endif // QT_VERSION < 0x050000
