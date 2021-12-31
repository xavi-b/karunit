#include "mainwindow.h"
#include <QDirIterator>
#include <QIcon>

namespace KU::UI
{

void MainWindow::loadPlugins()
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
    }

    emit widgetPluginsChanged();
    emit settingsPluginsChanged();
    emit aboutPluginsChanged();

    //    QDirIterator it(":", QDirIterator::Subdirectories);
    //    XB::Logger::log(XB::LogLevel::DEBUG, "Loaded resources:");
    //    while (it.hasNext())
    //        XB::Logger::log(XB::LogLevel::DEBUG, it.next());
}

void MainWindow::connectPlugin(PLUGIN::PluginInterface* plugin)
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

                QSet<KU::PLUGIN::PluginInterface*> signalRegisteredPlugins;

                for (auto& p : this->initializedPlugins)
                    if (p != plugin && p->getPluginConnector()->hasRegisteredPluginChoiceSignal(signal))
                        signalRegisteredPlugins.insert(p);

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
            });
}

void MainWindow::unloadPlugins()
{
    for (auto& p : this->initializedPlugins)
    {
        p->saveSettings();
        p->stop();
    }
}

MainWindow::MainWindow(QObject* parent)
    : QObject(parent)
{
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

MainWindow::~MainWindow()
{
    this->unloadPlugins();
}

QString MainWindow::pluginName(const QString& id) const
{
    if (this->initializedPlugins.contains(id))
        return this->initializedPlugins[id]->name();

    return "UNKNOWN";
}

QString MainWindow::pluginIcon(const QString& id) const
{
    if (this->initializedPlugins.contains(id))
        return this->initializedPlugins[id]->icon();

    return "UNKNOWN";
}

void MainWindow::showPrompt(QSet<PLUGIN::PluginInterface*> plugins, QString const& signal, QVariantMap const& data)
{
    // TODO
    //    disconnect(this->prompt, &WIDGETS::Prompt::choiceMade, this, nullptr);
    //    connect(this->prompt, &WIDGETS::Prompt::choiceMade,
    //            this, [=](KU::PLUGIN::PluginInterface* plugin)
    //    {
    //        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " pluginSlot" + signal);
    //        plugin->getPluginConnector()->pluginSlot(signal, data);
    //    });

    //    this->prompt->setChoices(plugins);
    //    this->prompt->slideDown(this->width()*3/4);
}

void MainWindow::hidePrompt()
{
}

} // namespace KU::UI
