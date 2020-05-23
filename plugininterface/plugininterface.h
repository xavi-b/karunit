#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>
#include <QSet>
#include <QObject>
#include "log.h"

namespace KU::PLUGIN
{

struct PluginVersion
{
    int major = 0;
    int minor = 0;
    int maintenance = 0;

    QString toString() const
    {
        return QString("%1.%2.%3").arg(major).arg(minor).arg(maintenance);
    }

    operator QString() const
    {
        return this->toString();
    }

    bool operator==(PluginVersion const& other) const
    {
        return major == other.major && minor == other.minor && maintenance == other.maintenance;
    }

    bool operator!=(PluginVersion const& other) const
    {
        return !(*this == other);
    }
};

struct PluginInfo
{
    PluginVersion version;
    QString id;

    QString toString() const
    {
        return QString("%1:%2").arg(id).arg(version.toString());
    }

    operator QString() const
    {
        return this->toString();
    }

    bool operator==(PluginInfo const& other) const
    {
        return version == other.version && id == other.id;
    }

    bool operator!=(PluginInfo const& other) const
    {
        return !(*this == other);
    }
};

class PluginConnector : public QObject
{
    Q_OBJECT
public:
    PluginConnector(QObject* parent = nullptr) : QObject(parent) { }

    void emitLogSignal(XB::Log const& l) const
    {
        emit log(l);
    }

    void emitPluginSignal(QString const& signal)
    {
        emit pluginSignal(signal);
    }

    void emitPluginDataSignal(QString const& signal, QVariantMap const& data)
    {
        emit pluginDataSignal(signal, data);
    }

    void emitPluginChoiceSignal(QString const& signal, QVariantMap const& data)
    {
        emit pluginChoiceSignal(signal, data);
    }

    virtual void pluginSlot(QString const& signal, QVariantMap const& data)
    {

    }

    virtual bool hasRegisteredPluginChoiceSignal(QString const& signal)
    {
        return false;
    }

signals:
    void hasInitialized(bool success);
    void log(XB::Log const& log) const;
    void pluginSignal(QString const& signal);
    void pluginDataSignal(QString const& signal, QVariantMap const& data);
    void pluginChoiceSignal(QString const& signal, QVariantMap const& data);
};

class PluginInterface
{
private:
    PluginConnector* pluginConnector = nullptr;

public:
    virtual ~PluginInterface()
    {
        if(this->pluginConnector != nullptr)
            this->pluginConnector->deleteLater();
    }

    virtual QString name() const = 0;
    virtual QString id() const = 0;
    virtual PluginVersion version() const = 0;
    virtual QString license() const = 0;
    virtual QIcon icon() const = 0;
    virtual bool initialize() = 0;
    virtual bool stop() = 0;

    virtual QWidget* createWidget() = 0;
    virtual QWidget* createSettingsWidget() = 0;
    virtual QWidget* createAboutWidget() = 0;
    virtual bool loadSettings() = 0;
    virtual bool saveSettings() const = 0;

    PluginInfo info() const
    {
        return { this->version(), this->id() };
    }

    PluginConnector* getPluginConnector()
    {
        if(this->pluginConnector == nullptr)
            this->pluginConnector = new PluginConnector;
        return this->pluginConnector;
    }

    void setPluginConnector(PluginConnector* pluginConnector)
    {
        this->pluginConnector = pluginConnector;
    }
};

}

#define PLUGININTERFACE_IID "xavi-b.karunit.PluginInterface/1.0"
Q_DECLARE_INTERFACE(KU::PLUGIN::PluginInterface, PLUGININTERFACE_IID)

#endif // PLUGININTERFACE_H
