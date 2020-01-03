#include "maintabwidget.h"

namespace KU::UI::WIDGETS
{

MainTabWidget::MainTabWidget(QWidget* parent)
    : QTabWidget(parent)
{
    this->setObjectName("MainTabWidget");
    this->setStyleSheet("QTabWidget#MainTabWidget::tab-bar { alignment: center; }");
    this->setTabPosition(QTabWidget::South);
    this->setTabBar(new MainTabBar);
}

}
