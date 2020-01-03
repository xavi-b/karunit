#ifndef EMITPLUGIN_H
#define EMITPLUGIN_H

#include <QtPlugin>
#include <QIcon>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include "plugininterface.h"

class EmitPlugin : public KU::PLUGIN::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "xavi-b.karunit.PluginInterface" FILE "EmitPlugin.json")
    Q_INTERFACES(KU::PLUGIN::PluginInterface)

public:
    virtual QString name() const override;
    virtual QString id() const override;
    virtual KU::PLUGIN::PluginVersion version() const override;
    virtual QSet<KU::PLUGIN::PluginInfo> dependencies() const override;
    virtual QString license() const override;
    virtual QIcon icon() const override;
    virtual bool initialize(QSet<PluginInterface*> const& plugins) override;
    virtual bool stop() override;

    virtual QWidget* createWidget() override;
    virtual QWidget* createSettingsWidget() override;
    virtual bool loadSettings() override;
    virtual bool saveSettings() const override;

signals:
    void testSignal(QString const& data);
};

#endif // EMITPLUGIN_H
