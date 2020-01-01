#ifndef LOG_H
#define LOG_H

#include <QString>

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
    LogLevel level;
    QString text;

    Log(LogLevel level, QString const& text)
        : level(level), text(text)
    {

    }

    Log(QString const& text)
        : level(LogLevel::DEBUG), text(text)
    {

    }

    QString toString() const
    {
        return QString("[%1] %2").arg(LogLevelNames[this->level]).arg(this->text);
    }
};

}

#endif // LOG_H
