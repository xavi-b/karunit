#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include "logger.h"
#include "filelogger.h"
#include "plugininterface.h"
#include "widgets/maintabwidget.h"
#include "widgets/settingstab.h"
#include "widgets/prompt.h"

namespace KU::UI
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSet<KU::PLUGIN::PluginInterface*> initializedPlugins;
    WIDGETS::MainTabWidget* tabWidget = nullptr;
    WIDGETS::SettingsTab* settingsTabWidget = nullptr;
    WIDGETS::Prompt* prompt = nullptr;
    XB::FileLogger* fileLogger = nullptr;

    void loadPlugins();
    void connectPlugin(KU::PLUGIN::PluginInterface* plugin);
    void unloadPlugins();

protected:
    QWidget* buildTabWidget();

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    void showPrompt(QSet<KU::PLUGIN::PluginInterface*> plugins, QString const& signal, QVariantMap const& data);
    void hidePrompt();
};

}

#endif // MAINWINDOW_H
