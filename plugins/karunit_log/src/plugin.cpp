#include "plugin.h"
#include <QQmlEngine>

KU_Log_PluginConnector::KU_Log_PluginConnector(QObject* parent)
    : PluginConnector(parent)
{
    timer.start(2000);
    connect(&timer, &QTimer::timeout, this, [=]() {
        emit logsChanged();
    });
}

void KU_Log_PluginConnector::pluginSlot(QString const& signal, QVariantMap const& data)
{
    if (signal == "log")
    {
        if (data["level"].isNull() || data["dateTime"].isNull() || data["text"].isNull())
            return;

        XB::Log log;
        log.level    = static_cast<XB::LogLevel>(data["level"].toInt());
        log.text     = data["text"].toString();
        log.dateTime = data["dateTime"].toDateTime();

        this->cache.prepend(log.toString());

        if (this->cache.size() > 100)
            this->cache.pop_back();
    }
}

QString KU_Log_PluginConnector::logs() const
{
    return this->cache.join('\n');
}

QString KU_Log_Plugin::name() const
{
    return "Log";
}

QString KU_Log_Plugin::id() const
{
    return "karunit_log";
}

KU::PLUGIN::PluginVersion KU_Log_Plugin::version() const
{
    return {1, 0, 0};
}

QString KU_Log_Plugin::license() const
{
    return "LGPL";
}

QString KU_Log_Plugin::icon() const
{
    return QString();
}

bool KU_Log_Plugin::initialize()
{
    qmlRegisterSingletonInstance("KarunitPlugins", 1, 0, "KUPLogPluginConnector", this->pluginConnector);

    return true;
}

bool KU_Log_Plugin::stop()
{
    return true;
}

bool KU_Log_Plugin::loadSettings()
{
    return true;
}

bool KU_Log_Plugin::saveSettings()
{
    return KU::Settings::instance()->status() == QSettings::NoError;
}

KU_Log_PluginConnector* KU_Log_Plugin::getPluginConnector()
{
    if (this->pluginConnector == nullptr)
        this->pluginConnector = new KU_Log_PluginConnector;
    return qobject_cast<KU_Log_PluginConnector*>(this->pluginConnector);
}
