#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include <QtPlugin>
#include <QIcon>
#include <QDebug>
#include <QLabel>
#include "plugininterface.h"
#include "emitplugin.h"

class TestPlugin : public KU::PLUGIN::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "xavi-b.karunit.PluginInterface" FILE "TestPlugin.json")
    Q_INTERFACES(KU::PLUGIN::PluginInterface)

public:
    virtual QString name() const override;
    virtual QString id() const override;
    virtual KU::PLUGIN::PluginVersion version() const override;
    virtual QSet<KU::PLUGIN::PluginInfo> dependencies() const override;
    virtual QString license() const override;
    virtual QIcon icon() const override;
    virtual bool initialize(QSet<PluginInterface*> const& plugins) override;

    virtual QWidget* createWidget() override;
    virtual QWidget* createSettingsWidget() override;
    virtual bool loadSettings() override;
    virtual bool saveSettings() const override;
};

#endif // TESTPLUGIN_H
