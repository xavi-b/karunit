#include "plugin.h"

void KU_Log_PluginConnector::pluginSlot(QString const& signal, QVariantMap const& data)
{
    if(signal == "log")
    {
        if(data["level"].isNull()
        || data["dateTime"].isNull()
        || data["text"].isNull())
            return;

        XB::Log log;
        log.level = static_cast<XB::LogLevel>(data["level"].toInt());
        log.text = data["text"].toString();
        log.dateTime = data["dateTime"].toDateTime();
        emit logSignal(log);
    }
}

QString KU_Log_Plugin::name() const
{
    return "Log";
}

QString KU_Log_Plugin::id() const
{
    return "log.me";
}

KU::PLUGIN::PluginVersion KU_Log_Plugin::version() const
{
    return { 1, 0, 0 };
}

QString KU_Log_Plugin::license() const
{
    return "LGPL";
}

QIcon KU_Log_Plugin::icon() const
{
    return QIcon();
}

bool KU_Log_Plugin::initialize()
{
    this->pluginConnector = new KU_Log_PluginConnector;
    this->setPluginConnector(this->pluginConnector);

    this->logsWidget = new QTextEdit;
    this->logsWidget->setReadOnly(true);

    this->cache.setCapacity(100);

    connect(this->pluginConnector, &KU_Log_PluginConnector::logSignal,
            this, [=](XB::Log const& log)
    {
        this->cache.append(log);

        this->logsWidget->clear();
        for(int i = 0; i < this->cache.size(); ++i)
        {
            this->logsWidget->append(this->cache[i].toString() + "\r\n");
        }
        this->logsWidget->ensureCursorVisible();
    });

    return true;
}

bool KU_Log_Plugin::stop()
{
    return true;
}

QWidget* KU_Log_Plugin::createWidget()
{
    return nullptr;
}

QWidget* KU_Log_Plugin::createSettingsWidget()
{
    return this->logsWidget;
}

bool KU_Log_Plugin::loadSettings()
{
    return true;
}

bool KU_Log_Plugin::saveSettings() const
{
    return KU::Settings::instance()->status() == QSettings::NoError;
}
