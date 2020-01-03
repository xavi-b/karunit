#include "settings.h"

namespace KU
{

Settings::Settings(QObject* parent)
    : QSettings(ORG_NAME, APP_NAME, parent)
{
    qDebug() << "Settings" << this->fileName();
}

Settings* Settings::instance()
{
    static Settings i;
    return &i;
}

void Settings::setValue(QString const& key, QVariant const& value)
{
    Settings::instance()->QSettings::setValue(key, value);
    Settings::instance()->sync();
}

QVariant Settings::value(QString const& key, QVariant const& defaultValue)
{
    return Settings::instance()->QSettings::value(key, defaultValue);
}

void Settings::setValue(QString const& pluginId, QString const& key, QVariant const& value)
{
    Settings::setValue(pluginId + "/" + key, value);
}

QVariant Settings::value(QString const& pluginId, QString const& key, QVariant const& defaultValue)
{
    return Settings::value(pluginId + "/" + key, defaultValue);
}

}
