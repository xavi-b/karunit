#include "emitplugin.h"

QString EmitPlugin::name() const
{
    return "EMIT";
}

QString EmitPlugin::id() const
{
    return "emit.id.com";
}

KU::PLUGIN::PluginVersion EmitPlugin::version() const
{
    return { 1, 0, 0 };
}

QSet<KU::PLUGIN::PluginInfo> EmitPlugin::dependencies() const
{
    return QSet<KU::PLUGIN::PluginInfo>();
}

QString EmitPlugin::license() const
{
    return "LGPL";
}

QIcon EmitPlugin::icon() const
{
    return QIcon(":/res/icon");
}

bool EmitPlugin::initialize(const QSet<KU::PLUGIN::PluginInterface*>& plugins)
{
    qDebug() << this->name() << "initialize";
    QTimer::singleShot(1000, this, [=]()
    {
        qDebug() << "signal emitted";
        emit testSignal("data");
    });
    return true;
}

bool EmitPlugin::stop()
{
    return true;
}

QWidget* EmitPlugin::createWidget()
{
    return new QLabel("emit");
}

QWidget* EmitPlugin::createSettingsWidget()
{
    return new QLabel("emit");
}

bool EmitPlugin::loadSettings()
{
    return true;
}

bool EmitPlugin::saveSettings() const
{
    return true;
}
