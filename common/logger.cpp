#include "logger.h"

namespace KU
{

Logger::Logger(QObject *parent)
    : QObject(parent)
{

}

Logger* Logger::instance()
{
    static Logger i;
    return &i;
}

void Logger::log(Log const& log)
{
#ifdef QT_DEBUG
    qDebug() << log.toString();
#endif
}

void Logger::log(LogLevel level, QString const& text)
{
    Logger::instance()->log(Log(level, text));
}

void Logger::log(QString const& log)
{
    Logger::instance()->log(Log(log));
}

}
