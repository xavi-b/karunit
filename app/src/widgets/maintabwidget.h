#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include "maintabbar.h"

namespace KU::UI::WIDGETS
{

class MainTabWidget : public QTabWidget
{
public:
    MainTabWidget(QWidget* parent = nullptr);
};

}

#endif // MAINTABWIDGET_H
