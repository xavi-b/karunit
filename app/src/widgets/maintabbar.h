#ifndef MAINTABBAR_H
#define MAINTABBAR_H

#include <QTabBar>
#include <QStylePainter>
#include <QStyleOptionTab>

namespace KU::UI::WIDGETS
{

class MainTabBar : public QTabBar
{
    Q_OBJECT
private:
    static const int ICON_SIZE = 80;
    static const int TEXT_HEIGHT = 20;
    static const int TAB_WIDTH = 200;

protected:
    QSize tabSizeHint(int index) const override;
    void paintEvent(QPaintEvent*) override;

public:
    MainTabBar(QWidget* parent = nullptr);
};

}

#endif // MAINTABBAR_H
