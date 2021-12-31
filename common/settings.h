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
    Settings(QObject* parent = nullptr);

public:
    static Settings* instance();

    Q_INVOKABLE void     save(QString const& key, QVariant const& value);
    Q_INVOKABLE QVariant get(QString const& key, QVariant const& defaultValue);
};

} // namespace KU

#endif // SETTINGS_H
