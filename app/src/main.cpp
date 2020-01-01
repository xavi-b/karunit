#include <QApplication>
#include "mainwindow.h"
#include "splashscreen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("xavi-b");
    app.setOrganizationDomain("karunit");

    KU::UI::SplashScreen splashScreen;
    splashScreen.show();
    app.processEvents();

    KU::UI::MainWindow w;
    w.show();

    return app.exec();
}
