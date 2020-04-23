#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDateTime>

namespace KU
{

enum LogLevel : char
{
    TRACE, DEBUG, INFO, WARN, ERROR, __COUNT
};

static const char* LogLevelNames[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR" };

static_assert(sizeof(LogLevelNames)/sizeof(char*) == LogLevel::__COUNT, "Sizes do not match");

struct Log
{
    QDateTime dateTime;
    LogLevel level;
    QString text;

    Log(LogLevel level, QString const& text)
        : level(level), text(text), dateTime(QDateTime::currentDateTimeUtc())
    {

    }

    Log(QString const& text)
        : level(LogLevel::DEBUG), text(text), dateTime(QDateTime::currentDateTimeUtc())
    {

    }

    QString toString() const
    {
        return QString("%1 [%2] %3").arg(this->dateTime.toString(Qt::ISODateWithMs)).arg(LogLevelNames[this->level]).arg(this->text);
    }
};

}

#endif // LOG_H
