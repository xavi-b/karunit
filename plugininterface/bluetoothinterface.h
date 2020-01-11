#ifndef BLUETOOTHINTERFACE_H
#define BLUETOOTHINTERFACE_H

#include <QObject>
#include <QString>
#include "plugininterface.h"

namespace KU::PLUGIN
{

struct MediaTrack
{
    QString album;
    QString artist;
    quint32 duration;
    QString genre;
    quint32 numberOfTracks;
    QString title;
    quint32 trackNumber;
};

enum MediaRepeat
{
    RepeatOff,
    RepeatSingleTrack,
    RepeatAllTracks,
    RepeatGroup
};

enum MediaShuffle
{
    ShuffleOff,
    ShuffleAllTracks,
    ShuffleGroup
};

enum MediaStatus
{
    Playing,
    Stopped,
    Paused,
    ForwardSeek,
    ReverseSeek,
    Error
};

struct DeviceInfo
{
    QString name;
    QString address;
    bool connected = false;
};

class BluetoothConnector : public QObject
{
    Q_OBJECT
public:
    BluetoothConnector(QObject* parent = nullptr) : QObject(parent) { }
    virtual void mediaPrevious() = 0;
    virtual void mediaNext() = 0;
    virtual void mediaPlay() = 0;
    virtual void mediaPause() = 0;
    virtual void connectToDevice(DeviceInfo const& info) = 0;
    virtual void disconnectFromDevice(DeviceInfo const& info) = 0;

signals:
    void knownDevices(QList<DeviceInfo> const& devices);
    void deviceConnected(DeviceInfo const& info);
    void deviceDisconnected(DeviceInfo const& info);
    void trackChanged(MediaTrack const& track);
    void nameChanged(QString const& name);
    void positionChanged(quint32 position);
    void repeatChanged(MediaRepeat repeat);
    void shuffleChanged(MediaShuffle shuffle);
    void statusChanged(MediaStatus status);
};

class BluetoothPluginInterface
{
public:
    virtual BluetoothConnector* getBluetoothConnector() = 0;
};

}

#define BLUETOOTHPLUGININTERFACE_IID "xavi-b.karunit.BluetoothPluginInterface/1.0"
Q_DECLARE_INTERFACE(KU::PLUGIN::BluetoothPluginInterface, BLUETOOTHPLUGININTERFACE_IID)

#endif // BLUETOOTHINTERFACE_H
