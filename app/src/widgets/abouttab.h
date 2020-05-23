#ifndef ABOUTTAB_H
#define ABOUTTAB_H

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

class AboutTab : public QWidget
{
    Q_OBJECT

private:
    QListWidget* listWidget = nullptr;
    QStackedWidget* stackedWidget = nullptr;

    void addAppTab();

public:
    AboutTab(QWidget* parent = nullptr);

    void addTab(QWidget* widget, QIcon icon, QString const& name);
};

}

#endif // ABOUTTAB_H
