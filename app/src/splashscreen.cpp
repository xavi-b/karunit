#include "splashscreen.h"

namespace KU::UI
{

SplashScreen::SplashScreen(QWidget* parent, QPixmap const& pixmap, Qt::WindowFlags f)
    : QSplashScreen(parent, pixmap, f)
{

}

SplashScreen::SplashScreen(QPixmap const& pixmap, Qt::WindowFlags f)
    : QSplashScreen(pixmap, f)
{

}

}
