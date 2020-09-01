#include "mainwindow.h"

namespace KU::UI
{

void MainWindow::loadPlugins()
{
    QVector<KU::PLUGIN::PluginInterface*> loadedPluginsInterfaces;
    QVector<KU::PLUGIN::PluginInfo> loadedPluginsInfos;

    auto pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");

    auto const entryList = pluginsDir.entryList(QDir::Files, QDir::SortFlag::Name);
    for(auto const& fileName : entryList)
    {
        if(!fileName.endsWith(".so"))
            continue;

        XB::Logger::log(XB::LogLevel::DEBUG, "Trying to load plugin with filename " + fileName);

        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        auto plugin = loader.instance();
        if(plugin != nullptr)
        {
            XB::Logger::log(XB::LogLevel::DEBUG, "QPluginLoader loaded plugin with filename " + fileName);
            auto pluginInterface = qobject_cast<KU::PLUGIN::PluginInterface*>(plugin);
            if(pluginInterface != nullptr)
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

    for(auto& p : loadedPluginsInterfaces)
    {
        if(!p->loadSettings())
            continue;

        connectPlugin(p);

        if(!p->initialize())
            continue;

        this->initializedPlugins.insert(p);

        auto widget = p->createWidget();
        if(widget != nullptr)
            this->tabWidget->addTab(widget, p->icon(), p->name());

        auto settingsWidget = p->createSettingsWidget();
        if(settingsWidget != nullptr)
            this->settingsTabWidget->addTab(settingsWidget, p->icon(), p->name());

        auto aboutWidget = p->createAboutWidget();
        if(aboutWidget != nullptr)
            this->aboutTabWidget->addTab(aboutWidget, p->icon(), p->name());
    }
}

void MainWindow::connectPlugin(PLUGIN::PluginInterface* plugin)
{
    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::log, this, [=](XB::Log const& log)
    {
        XB::Logger::log(log.level, "[PLUGIN " + plugin->name() +"] " + log.text);
    });

    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::pluginSignal, this,
            [=](QString const& signal)
    {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginSignal " + signal);

        for(auto& p : this->initializedPlugins)
            if(p != plugin)
                p->getPluginConnector()->pluginSlot(signal, QVariantMap());
    });

    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::pluginDataSignal, this,
            [=](QString const& signal, QVariantMap const& data)
    {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginDataSignal " + signal);

        for(auto& p : this->initializedPlugins)
            if(p != plugin)
                p->getPluginConnector()->pluginSlot(signal, data);
    });

    connect(plugin->getPluginConnector(), &KU::PLUGIN::PluginConnector::pluginChoiceSignal, this,
            [=](QString const& signal, QVariantMap const& data)
    {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " emitPluginChoiceSignal " + signal);

        QSet<KU::PLUGIN::PluginInterface*> signalRegisteredPlugins;

        for(auto& p : this->initializedPlugins)
            if(p != plugin && p->getPluginConnector()->hasRegisteredPluginChoiceSignal(signal))
                signalRegisteredPlugins.insert(p);

        if(signalRegisteredPlugins.size() > 0)
        {
            if(signalRegisteredPlugins.size() == 1)
            {
                XB::Logger::log(XB::LogLevel::DEBUG, (*signalRegisteredPlugins.begin())->name() + " pluginSlot" + signal);
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
    for(auto& p : this->initializedPlugins)
    {
        p->saveSettings();
        p->stop();
    }
}

QWidget* MainWindow::buildTabWidget()
{
    this->tabWidget->addTab(this->settingsTabWidget, QIcon::fromTheme("preferences-system"), tr("Settings"));
    this->tabWidget->addTab(this->aboutTabWidget, QIcon::fromTheme("dialog-information"), tr("About"));

    return this->tabWidget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDir logDir(QCoreApplication::applicationDirPath());
    if(logDir.exists("log") || logDir.mkdir("log"))
    {
        XB::Logger::log(XB::LogLevel::INFO, "Log directory: " + logDir.filePath("log"));

        this->fileLogger = new XB::FileLogger(logDir.filePath("log"), this);
        connect(this->fileLogger, &XB::FileLogger::fileError, this, [=](QFile::FileError error)
        {
            XB::Logger::log(XB::LogLevel::ERROR, "FileLogger QFileError: " + QString::number(error));
        });
        this->fileLogger->start();
    }
    else
    {
        XB::Logger::log(XB::LogLevel::ERROR, "Could not create log directory: " + logDir.filePath("log"));
    }

    this->setMinimumSize(480, 320);

    this->tabWidget = new WIDGETS::MainTabWidget;
    this->settingsTabWidget = new WIDGETS::SettingsTab;
    this->aboutTabWidget = new WIDGETS::AboutTab;
    this->prompt = new WIDGETS::Prompt(this->minimumWidth()*3/4, this);

    this->loadPlugins();

    this->setCentralWidget(this->buildTabWidget());

    connect(XB::Logger::instance(), &XB::Logger::logWritten, this, [=](XB::Log const& log)
    {
        QVariantMap data;
        data["level"] = static_cast<int>(log.level);
        data["dateTime"] = log.dateTime;
        data["text"] = log.text;

        for(auto& p : this->initializedPlugins)
            p->getPluginConnector()->pluginSlot("log", data);
    });
}

MainWindow::~MainWindow()
{
    this->unloadPlugins();
    if(this->fileLogger)
        this->fileLogger->quit();
}

void MainWindow::showPrompt(QSet<PLUGIN::PluginInterface*> plugins, QString const& signal, QVariantMap const& data)
{
    disconnect(this->prompt, &WIDGETS::Prompt::choiceMade, this, nullptr);
    connect(this->prompt, &WIDGETS::Prompt::choiceMade,
            this, [=](KU::PLUGIN::PluginInterface* plugin)
    {
        XB::Logger::log(XB::LogLevel::DEBUG, plugin->name() + " pluginSlot" + signal);
        plugin->getPluginConnector()->pluginSlot(signal, data);
    });

    this->prompt->setChoices(plugins);
    this->prompt->slideDown(this->width()*3/4);
}

void MainWindow::hidePrompt()
{

}

}
