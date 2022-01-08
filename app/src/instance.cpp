#include "instance.h"
#include <QDirIterator>
#include <QIcon>
#include "settings.h"

namespace KU::UI
{

void Instance::loadPlugins()
{
    QVector<KU::PLUGIN::PluginInterface*> loadedPluginsInterfaces;
    QVector<KU::PLUGIN::PluginInfo>       loadedPluginsInfos;

    auto pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");

    auto const entryList = pluginsDir.entryList(QDir::Files, QDir::SortFlag::Name);
    for (auto const& fileName : entryList)
    {
        if (!fileName.endsWith(".so"))
            continue;

        XB::Logger::log(XB::LogLevel::DEBUG, "Trying to load plugin with filename " + fileName);

        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        auto          plugin = loader.instance();
        if (plugin != nullptr)
        {
            XB::Logger::log(XB::LogLevel::DEBUG, "QPluginLoader loaded plugin with filename " + fileName);
            auto pluginInterface = qobject_cast<KU::PLUGIN::PluginInterface*>(plugin);
            if (pluginInterface != nullptr)
            {
                loadedPluginsInterfaces.push_back(pluginInterface);
                loadedPluginsInfos.push_back(pluginInterface->info());
            }
            else
            {
                XB::Logger::log(XB::LogLevel::WARN, "Plugin " + fileName + " cannot be cast to plugin interface");
            }
        }
        else
        {
            XB::Logger::log(XB::LogLevel::WARN, "QPluginLoader failed to load plugin with filename " + fileName);
            XB::Logger::log(XB::LogLevel::WARN, loader.errorString());
        }
    }

    for (auto& p : loadedPluginsInterfaces)
    {
        if (!p->loadSettings())
            continue;

        p->getPluginConnector(); // create custom plugin connector if one
        connectPlugin(p);

        if (!p->initialize())
            continue;

        this->initializedPlugins[p->id()] = p;

        auto widgetFile = ":/" + p->id() + "/widget.qml";
        if (QFile(widgetFile).exists())
            widgetPlugins.append(p->id());

        auto settingsFile = ":/" + p->id() + "/settings.qml";
        if (QFile(settingsFile).exists())
            settingsPlugins.append(p->id());

        auto aboutFile = ":/" + p->id() + "/about.qml";
        if (QFile(aboutFile).exists())
            aboutPlugins.append(p->id());

        p->switchLocale(this->currentLocale);

        this->availableSlots.append(p->getPluginConnector()->availableSlots());
    }

    emit availablePluginsChanged();

    //    QDirIterator it(":", QDirIterator::Subdirectories);
    //    XB::Logger::log(XB::LogLevel::DEBUG, "Loaded resources:");
    //    while (it.hasNext())
    //        XB::Logger::log(XB::LogLevel::DEBUG, it.next());
}

void Instance::connectPlugin(PLUGIN::PluginInterface* plugin)
{
    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::log, this, [=](XB::Log const& log) {
        XB::Logger::log(log.level, "[PLUGIN " + plugin->name() + "] " + log.text);
    });

    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::pluginSignal, this, [=](QString const& signal) {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginSignal " + signal);

        for (auto& p : this->initializedPlugins)
            if (p != plugin)
                p->getPluginConnector()->pluginSlot(signal, QVariantMap());
    });

    connect(plugin->getPluginConnector(),
            &KU::PLUGIN::PluginConnector::pluginDataSignal,
            this,
            [=](QString const& signal, QVariantMap const& data) {
                XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginDataSignal " + signal);

                for (auto& p : this->initializedPlugins)
                    if (p != plugin)
                        p->getPluginConnector()->pluginSlot(signal, data);
            });

    connect(plugin->getPluginConnector(),
            &KU::PLUGIN::PluginConnector::pluginChoiceSignal,
            this,
            [=](QString const& signal, QVariantMap const& data) {
                XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginChoiceSignal " + signal);

                PluginsMap signalRegisteredPlugins;

                for (auto& p : this->initializedPlugins)
                    if (p != plugin && p->getPluginConnector()->hasRegisteredPluginChoiceSignal(signal))
                        signalRegisteredPlugins[p->id()] = p;

                if (signalRegisteredPlugins.size() > 0)
                {
                    if (signalRegisteredPlugins.size() == 1)
                    {
                        XB::Logger::log(XB::LogLevel::DEBUG,
                                        (*signalRegisteredPlugins.begin())->name() + " pluginSlot" + signal);
                        (*signalRegisteredPlugins.begin())->getPluginConnector()->pluginSlot(signal, data);
                    }
                    else
                    {
                        this->showPrompt(signalRegisteredPlugins, signal, data);
                    }
                }
                else
                {
                    XB::Logger::log(XB::LogLevel::DEBUG, "No registered plugin for " + signal);
                }
            });

    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::showPluginSignal, this, [=](QString const& pluginId) {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " showPluginSignal " + pluginId);
        if (this->widgetPlugins.contains(pluginId))
            emit showPlugin(this->widgetPlugins.indexOf(pluginId));
    });
}

void Instance::unloadPlugins()
{
    for (auto& p : this->initializedPlugins)
    {
        p->saveSettings();
        p->stop();
    }
}

Instance::Instance(QObject* parent)
    : QObject(parent)
{
    QDir logDir(QCoreApplication::applicationDirPath());
    if (logDir.exists("log") || logDir.mkdir("log"))
    {
        XB::Logger::log(XB::LogLevel::INFO, "Log directory: " + logDir.filePath("log"));

        this->fileLogger = new XB::FileLogger(logDir.filePath("log"), this);
        connect(this->fileLogger, &XB::FileLogger::fileError, this, [=](QFile::FileError error) {
            XB::Logger::log(XB::LogLevel::ERROR, "FileLogger QFileError: " + QString::number(error));
        });
        this->fileLogger->start();
    }
    else
    {
        XB::Logger::log(XB::LogLevel::ERROR, "Could not create log directory: " + logDir.filePath("log"));
    }

    this->switchLocale(KU::Settings::instance()->get("karunit/currentLocale", this->defaultLocale).toString());

    connect(XB::Logger::instance(), &XB::Logger::logWritten, this, [=](XB::Log const& log) {
        QVariantMap data;
        data["level"]    = static_cast<int>(log.level);
        data["dateTime"] = log.dateTime;
        data["text"]     = log.text;

        for (auto& p : this->initializedPlugins)
            p->getPluginConnector()->pluginSlot("log", data);
    });

    this->loadPlugins();
}

Instance::~Instance()
{
}

void Instance::unload()
{
    XB::Logger::log(XB::LogLevel::INFO, "UNLOADING");
    this->unloadPlugins();
    if (this->fileLogger)
        this->fileLogger->quit();
}

QString Instance::pluginName(const QString& id) const
{
    if (this->initializedPlugins.contains(id))
        return this->initializedPlugins[id]->name();

    return "UNKNOWN";
}

QString Instance::pluginIcon(const QString& id) const
{
    if (this->initializedPlugins.contains(id))
        return this->initializedPlugins[id]->icon();

    return "UNKNOWN";
}

void Instance::showPrompt(PluginsMap plugins, QString const& signal, QVariantMap const& data)
{
    emit prompt(plugins.keys(), signal, data);
}

void Instance::selectPromptedPlugin(QString const& pluginId, QString const& signalName, QVariantMap const& signalData)
{
    if (this->initializedPlugins.contains(pluginId))
    {
        auto plugin = this->initializedPlugins[pluginId];
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " pluginSlot" + signalName);
        plugin->getPluginConnector()->pluginSlot(signalName, signalData);
    }
}

QString Instance::translationsDir() const
{
    return ":/translations";
}

bool Instance::switchLocale(QString const& locale)
{
    if (this->getAvailableLocales().contains(locale))
    {
        qApp->removeTranslator(&this->translator);
        qApp->removeTranslator(&this->qt_translator);

        QString path;
        path = this->translationsDir() + "/" + locale + ".qm";
        if (translator.load(path))
            qApp->installTranslator(&translator);

        QString shortLocale = locale.split('_').first();
        path                = ":/qt_translations/qtbase_" + shortLocale + ".qm";
        if (qt_translator.load(path))
            qApp->installTranslator(&qt_translator);

        for (auto& p : this->initializedPlugins)
            p->switchLocale(locale);

        this->setCurrentLocale(locale);

        return true;
    }

    return false;
}

QStringList Instance::getAvailableLocales() const
{
    QDir        dir(this->translationsDir());
    QStringList tsFiles = dir.entryList(QStringList("*.qm"), QDir::Filter::Files);

    QStringList locales;
    locales << this->defaultLocale;
    for (int i = 0; i < tsFiles.size(); ++i)
    {
        QString locale = tsFiles[i];
        locale.truncate(locale.lastIndexOf('.'));
        locales << locale;
    }
    return locales;
}

void Instance::setDefaultLocale(const QString& s)
{
    this->defaultLocale = s;
    if (this->currentLocale.isEmpty())
        this->setCurrentLocale(this->defaultLocale);
}

QString Instance::getCurrentLocale()
{
    if (this->currentLocale.isEmpty())
        this->setCurrentLocale(this->defaultLocale);

    return this->currentLocale;
}

void Instance::setCurrentLocale(const QString& s)
{
    XB::Logger::log(XB::LogLevel::INFO, "setCurrentLocale: " + s);

    this->currentLocale = s;
    QLocale::setDefault(this->currentLocale);
    KU::Settings::instance()->save("karunit/currentLocale", this->currentLocale);

    emit currentLocaleChanged();
}

QStringList Instance::getAvailablePlugins() const
{
    return this->initializedPlugins.keys();
}

} // namespace KU::UI
