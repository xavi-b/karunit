#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>
#include <QSettings>
#include "defines.h"

namespace KU
{

class Settings : public QSettings
{
    Q_OBJECT
private:
    Settings(QObject *parent = nullptr);

public:
    static Settings* instance();

    static void setValue(QString const& key, QVariant const& value);
    static QVariant value(QString const& key, QVariant const& defaultValue);

    static void setValue(QString const& pluginId, QString const& key, QVariant const& value);
    static QVariant value(QString const& pluginId, QString const& key, QVariant const& defaultValue);
};

}

#endif // SETTINGS_H
