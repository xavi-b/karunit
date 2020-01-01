#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QObject>
#include "log.h"

namespace KU
{

class Logger : public QObject
{
    Q_OBJECT
private:
    Logger(QObject *parent = nullptr);

public:
    static Logger* instance();

    static void log(Log const& log);
    static void log(LogLevel level, QString const& text);
    static void log(QString const& log);
};

}

#endif // LOGGER_H
