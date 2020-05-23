#ifndef LOGPLUGIN_H
#define LOGPLUGIN_H

#include <QtPlugin>
#include <QIcon>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QDateTime>
#include <QContiguousCache>
#include "plugininterface.h"
#include "settings.h"

class KU_Log_PluginConnector : public KU::PLUGIN::PluginConnector
{
    Q_OBJECT
public:
    virtual void pluginSlot(QString const& signal, QVariantMap const& data) override;

signals:
    void logSignal(XB::Log const& log);
};

class KU_Log_Plugin : public QObject, public KU::PLUGIN::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "xavi-b.karunit.PluginInterface")
    Q_INTERFACES(KU::PLUGIN::PluginInterface)

public:
    virtual QString name() const override;
    virtual QString id() const override;
    virtual KU::PLUGIN::PluginVersion version() const override;
    virtual QString license() const override;
    virtual QIcon icon() const override;
    virtual bool initialize() override;
    virtual bool stop() override;

    virtual QWidget* createWidget() override;
    virtual QWidget* createSettingsWidget() override;
    virtual QWidget* createAboutWidget() override;
    virtual bool loadSettings() override;
    virtual bool saveSettings() const override;

private:
    KU_Log_PluginConnector* pluginConnector = nullptr;
    QTextEdit* logsWidget = nullptr;
    QContiguousCache<XB::Log> cache;
};


#endif // LOGPLUGIN_H
