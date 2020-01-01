#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include "logger.h"
#include "plugininterface.h"

namespace KU::UI
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTabWidget* tabWidget = nullptr;

    void loadPlugins();
    void unloadPlugins();
protected:
    QWidget* buildCentralWidget();
public:
    MainWindow(QWidget *parent = nullptr);

};

}

#endif // MAINWINDOW_H
