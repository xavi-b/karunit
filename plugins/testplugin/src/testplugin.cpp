#include "testplugin.h"

QString TestPlugin::name() const
{
    return "TEST";
}

QString TestPlugin::id() const
{
    return "test.id.com";
}

KU::PLUGIN::PluginVersion TestPlugin::version() const
{
    return { 1, 0, 0 };
}

QSet<KU::PLUGIN::PluginInfo> TestPlugin::dependencies() const
{
    return QSet<KU::PLUGIN::PluginInfo>();
}

QString TestPlugin::license() const
{
    return "LGPL";
}

QIcon TestPlugin::icon() const
{
    return QIcon(":/logo");
}

bool TestPlugin::initialize(const QSet<KU::PLUGIN::PluginInterface*>& plugins)
{
    qDebug() << this->name() << "initialize";
    for(auto& p : plugins)
    {
        qDebug() << p->name();
        auto emitplugin = qobject_cast<EmitPlugin*>(p);
        if(emitplugin != nullptr)
        {
            qDebug() << "slot connected";
            connect(emitplugin, &EmitPlugin::testSignal, this, [=](QString const& data)
            {
                qDebug() << "signal received" << data;
            });
        }
    }
    return true;
}

bool TestPlugin::stop()
{
    return true;
}

QWidget* TestPlugin::createWidget()
{
    return new QLabel("test");
}

QWidget* TestPlugin::createSettingsWidget()
{
    return new QLabel("test");
}

bool TestPlugin::loadSettings()
{
    qDebug() << "loadSettings" << KU::Settings::value(this->id(), "timestamp", 0).toLongLong();
    return true;
}

bool TestPlugin::saveSettings() const
{
    KU::Settings::instance()->setValue(this->id(), "timestamp", QDateTime::currentSecsSinceEpoch());
    qDebug() << "saveSettings" << KU::Settings::instance()->status();
    return KU::Settings::instance()->status() == QSettings::NoError;
}
