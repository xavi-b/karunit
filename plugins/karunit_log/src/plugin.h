#ifndef LOGPLUGIN_H
#define LOGPLUGIN_H

#include <QtPlugin>
#include <QIcon>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include "plugininterface.h"
#include "settings.h"

class KU_Log_PluginConnector : public KU::PLUGIN::PluginConnector
{
    Q_OBJECT

    Q_PROPERTY(QString logs READ logs NOTIFY logsChanged)

public:
    KU_Log_PluginConnector(QObject* parent = nullptr);
    virtual void pluginSlot(QString const& signal, QVariantMap const& data) override;

    QString logs() const;

signals:
    void logsChanged();

private:
    QTimer      timer;
    QStringList cache;
};

class KU_Log_Plugin : public QObject, public KU::PLUGIN::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "xavi-b.karunit.PluginInterface")
    Q_INTERFACES(KU::PLUGIN::PluginInterface)

public:
    virtual QString                   name() const override;
    virtual QString                   id() const override;
    virtual KU::PLUGIN::PluginVersion version() const override;
    virtual QString                   license() const override;
    virtual QString                   icon() const override;
    virtual bool                      initialize() override;
    virtual bool                      stop() override;

    virtual bool                    loadSettings() override;
    virtual bool                    saveSettings() override;
    virtual KU_Log_PluginConnector* getPluginConnector() override;
};

#endif // LOGPLUGIN_H
