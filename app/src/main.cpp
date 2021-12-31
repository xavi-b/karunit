#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainwindow.h"
#include "defines.h"
#include "settings.h"

#include <QLoggingCategory>

static void messageHandler(QtMsgType type, QMessageLogContext const& context, QString const& msg)
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
    XB::Logger::log(
        level,
        QString("[QT CONSOLE] %1%2").arg(context.category ? QString("(%1) ").arg(context.category) : "").arg(msg));
}

int main(int argc, char* argv[])
{
#ifdef QT_DEBUG
    QLoggingCategory::setFilterRules("default.debug=true\n"
                                     "qt.positioning.*=true");
#endif

    qputenv("QT_IM_MODULE", QByteArray("freevirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    qInstallMessageHandler(messageHandler);

    QGuiApplication app(argc, argv);

    app.setOrganizationName(ORG_NAME);
    app.setOrganizationDomain(APP_NAME);

    KU::UI::MainWindow w;
    qmlRegisterSingletonInstance("Karunit", 1, 0, "KUMainWindow", &w);
    qmlRegisterSingletonInstance("Karunit", 1, 0, "KUSettings", KU::Settings::instance());

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    engine.load(url);

    return app.exec();
}
