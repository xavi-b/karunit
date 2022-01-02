#ifndef INSTANCE_H
#define INSTANCE_H

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QTranslator>
#include "logger.h"
#include "filelogger.h"
#include "plugininterface.h"

namespace KU::UI
{

typedef QMap<QString, KU::PLUGIN::PluginInterface*> PluginsMap;

class Instance : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList widgetPlugins MEMBER widgetPlugins NOTIFY widgetPluginsChanged)
    Q_PROPERTY(QStringList settingsPlugins MEMBER settingsPlugins NOTIFY settingsPluginsChanged)
    Q_PROPERTY(QStringList aboutPlugins MEMBER aboutPlugins NOTIFY aboutPluginsChanged)
    Q_PROPERTY(QString currentLocale READ getCurrentLocale NOTIFY currentLocaleChanged)
    Q_PROPERTY(QStringList availableLocales READ getAvailableLocales CONSTANT)

public:
    Instance(QObject* parent = nullptr);
    virtual ~Instance();

    Q_INVOKABLE QString pluginName(QString const& id) const;
    Q_INVOKABLE QString pluginIcon(QString const& id) const;

    void             showPrompt(PluginsMap plugins, QString const& signal, QVariantMap const& data);
    Q_INVOKABLE void selectPromptedPlugin(QString const& pluginId, QString const& signalName, QVariantMap const& signalData);

    QString          translationsDir() const;
    Q_INVOKABLE bool switchLocale(QString const& locale);
    QStringList      getAvailableLocales() const;
    void             setDefaultLocale(QString const& s);
    QString          getCurrentLocale();
    void             setCurrentLocale(const QString& s);

signals:
    void prompt(QStringList plugins, QString const& signal, QVariantMap const& data);
    void widgetPluginsChanged();
    void settingsPluginsChanged();
    void aboutPluginsChanged();
    void currentLocaleChanged();

private:
    PluginsMap  initializedPlugins;
    QStringList widgetPlugins;
    QStringList settingsPlugins;
    QStringList aboutPlugins;

    QTranslator translator;
    QTranslator qt_translator;
    QString     defaultLocale = "en_US";
    QString     currentLocale;

    void loadPlugins();
    void connectPlugin(KU::PLUGIN::PluginInterface* plugin);
    void unloadPlugins();
};

} // namespace KU::UI

#endif // INSTANCE_H
