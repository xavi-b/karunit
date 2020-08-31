#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCoreApplication>
#include "icondelegate.h"

namespace KU::UI::WIDGETS
{

class SettingsTab : public QWidget
{
    Q_OBJECT

private:
    QListWidget* listWidget = nullptr;
    QStackedWidget* stackedWidget = nullptr;

protected:
    virtual void addAppTab();

public:
    SettingsTab(QWidget* parent = nullptr);

    void addTab(QWidget* widget, QIcon icon, QString const& name);
};

}

#endif // SETTINGSTAB_H
