#include <QApplication>
#include "mainwindow.h"
#include "splashscreen.h"
#include "defines.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    qInstallMessageHandler([](QtMsgType type, QMessageLogContext const& context, QString const& msg)
    {
        XB::LogLevel level;
        switch (type)
        {
            case QtInfoMsg:
                level = XB::LogLevel::INFO;
                break;
            case QtWarningMsg:
                level = XB::LogLevel::WARN;
                break;
            case QtCriticalMsg:
            case QtFatalMsg:
                level = XB::LogLevel::ERROR;
                break;
            default:
                level = XB::LogLevel::DEBUG;
                break;
        }
        XB::Logger::log(level, QString("[QT CONSOLE] %1%2").arg(context.category ? QString("(%1) ").arg(context.category) : "").arg(msg));
    });

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
