#include <QApplication>
#include "mainwindow.h"
#include "splashscreen.h"
#include "defines.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication app(argc, argv);

    app.setOrganizationName(ORG_NAME);
    app.setOrganizationDomain(APP_NAME);

    KU::UI::SplashScreen splashScreen;
    splashScreen.show();
    app.processEvents();

    KU::UI::MainWindow w;

#ifdef QT_DEBUG
    w.showMaximized();
#else
    w.showFullScreen();
#endif

    return app.exec();
}
