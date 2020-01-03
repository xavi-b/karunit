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

class PluginInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~PluginInterface() = default;

    virtual QString name() const = 0;
    virtual QString id() const = 0;
    virtual PluginVersion version() const = 0;
    virtual QSet<PluginInfo> dependencies() const = 0;
    virtual QString license() const = 0;
    virtual QIcon icon() const = 0;
    virtual bool initialize(QSet<PluginInterface*> const& plugins) = 0;
    virtual bool stop() = 0;

    virtual QWidget* createWidget() = 0;
    virtual QWidget* createSettingsWidget() = 0;
    virtual bool loadSettings() = 0;
    virtual bool saveSettings() const = 0;

    PluginInfo info() const
    {
        return { this->version(), this->id() };
    }
    bool checkDependencies(QSet<PluginInfo> const& plugins) const
    {
        return plugins.contains(this->dependencies());
    }
    QSet<PluginInfo> missingDependencies(QSet<PluginInfo> const& plugins) const
    {
        QSet<PluginInfo> missingPlugins;
        for(auto const& d : this->dependencies())
        {
            if(!plugins.contains(d))
            {
                missingPlugins.insert(d);
                emit log(Log(LogLevel::WARN, QString("Missing dependency %1 for %2").arg(d.toString()).arg(this->version().toString())));
            }
        }
        return missingPlugins;
    }

signals:
    void hasInitialized(bool success);
    void log(Log const& log) const;
};

}

#define PLUGININTERFACE_IID "xavi-b.karunit.PluginInterface/1.0"
Q_DECLARE_INTERFACE(KU::PLUGIN::PluginInterface, PLUGININTERFACE_IID)

#endif // PLUGININTERFACE_H
