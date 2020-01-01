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

    for(auto& p : loadedPluginsInterfaces)
    {
        // TODO dependency tree + check
        qDebug() << p->name();
        this->tabWidget->addTab(p->createWidget(), p->icon(), p->name());
    }
}

void MainWindow::unloadPlugins()
{
    //TODO
}

QWidget* MainWindow::buildCentralWidget()
{
    this->tabWidget = new QTabWidget;
    this->tabWidget->setObjectName("CentralTabWidget");
    this->tabWidget->setStyleSheet("QTabWidget#CentralTabWidget::tab-bar { alignment: center; }");
    this->tabWidget->setTabPosition(QTabWidget::South);
    this->tabWidget->tabBar()->setExpanding(false);
    this->tabWidget->tabBar()->setStyleSheet("QTabBar::scroller { width: 0px; } QTabBar::tab { height: 80px; width: 200px; }");

    this->tabWidget->addTab(new QWidget, "test1");
    this->tabWidget->addTab(new QWidget, "test2");
    this->tabWidget->addTab(new QWidget, "test3");
    this->tabWidget->addTab(new QWidget, "PARAMS");

    return this->tabWidget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setCentralWidget(this->buildCentralWidget());
    this->loadPlugins();
}


}
