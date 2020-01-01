#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

namespace KU::UI
{

class SplashScreen : public QSplashScreen
{
public:
    SplashScreen(QWidget* parent, QPixmap const& pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());
    SplashScreen(QPixmap const& pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());
};

}

#endif // SPLASHSCREEN_H
