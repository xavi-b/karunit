#include "maintabbar.h"

namespace KU::UI::WIDGETS
{

QSize MainTabBar::tabSizeHint(int) const
{
    return QSize(TAB_WIDTH, ICON_SIZE + TEXT_HEIGHT);
}

void MainTabBar::paintEvent(QPaintEvent*)
{
    QStylePainter p(this);
    for(int index = 0; index < this->count(); index++)
    {
        QStyleOptionTab tab;
        this->initStyleOption(&tab, index);

        QIcon icon = tab.icon;
        QString text = tab.text;
        tab.icon = QIcon();
        tab.text = QString();

        p.drawControl(QStyle::CE_TabBarTab, tab);

        QPainter painter(this);
        QRect rect = this->tabRect(index);
        rect.adjust(0, 0, 0, -8);
        painter.drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, text);
        icon.paint(&painter,
                   rect.left() + (rect.width()-tab.iconSize.width())/2,
                   rect.top(),
                   tab.iconSize.width(),
                   tab.iconSize.height(),
                   Qt::AlignCenter);
    }
}

MainTabBar::MainTabBar(QWidget* parent)
    : QTabBar(parent)
{
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    this->setExpanding(false);
    this->setStyleSheet("QTabBar::scroller { width: 0px; }");
}

}
