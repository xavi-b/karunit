#include "mainwindow.h"

namespace KU::UI
{

void MainWindow::loadPlugins()
{
    QSet<KU::PLUGIN::PluginInterface*> loadedPluginsInterfaces;
    QSet<KU::PLUGIN::PluginInfo> loadedPluginsInfos;

    auto pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");

    auto const entryList = pluginsDir.entryList(QDir::Files);
    for(auto const& fileName : entryList)
    {
        if(!fileName.endsWith(".so"))
            continue;

        Logger::log(LogLevel::DEBUG, "Trying to load plugin with filename " + fileName);

        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        auto plugin = loader.instance();
        if(plugin != nullptr)
        {
            Logger::log(LogLevel::DEBUG, "QPluginLoader loaded plugin with filename " + fileName);
            auto pluginInterface = qobject_cast<KU::PLUGIN::PluginInterface*>(plugin);
            if(pluginInterface != nullptr)
            {
                loadedPluginsInterfaces.insert(pluginInterface);
                loadedPluginsInfos.insert(pluginInterface->info());
            }
            else
            {
                Logger::log(LogLevel::WARN, "Plugin " + fileName + " cannot be cast to plugin interface");
            }
        }
        else
        {
            Logger::log(LogLevel::WARN, "QPluginLoader failed to load plugin with filename " + fileName);
            Logger::log(LogLevel::WARN, loader.errorString());
        }
    }

    //TODO redo
    for(auto& p : loadedPluginsInterfaces)
    {
        auto widget = p->createWidget();
        if(widget != nullptr)
            this->tabWidget->addTab(widget, p->icon(), p->name());

        auto settingsWidget = p->createSettingsWidget();
        if(settingsWidget != nullptr)
            this->settingsTabWidget->addTab(settingsWidget, p->icon(), p->name());

        if(p->loadSettings() && p->initialize(loadedPluginsInterfaces))
            this->initializedPlugins.insert(p);
    }
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
    this->tabWidget->addTab(this->settingsTabWidget, tr("Settings"));

    return this->tabWidget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(640, 480);

    this->tabWidget = new WIDGETS::MainTabWidget;
    this->settingsTabWidget = new WIDGETS::SettingsTab;

    this->loadPlugins();

    this->setCentralWidget(this->buildTabWidget());
}

MainWindow::~MainWindow()
{
    this->unloadPlugins();
}


}
