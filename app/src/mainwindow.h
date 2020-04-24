#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include "logger.h"
#include "plugininterface.h"
#include "widgets/maintabwidget.h"
#include "widgets/settingstab.h"

namespace KU::UI
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSet<KU::PLUGIN::PluginInterface*> initializedPlugins;
    WIDGETS::MainTabWidget* tabWidget = nullptr;
    WIDGETS::SettingsTab* settingsTabWidget = nullptr;

    void loadPlugins();
    void connectPlugin(KU::PLUGIN::PluginInterface* plugin);
    void unloadPlugins();

protected:
    QWidget* buildTabWidget();

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

};

}

#endif // MAINWINDOW_H
