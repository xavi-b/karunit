import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Karunit 1.0

RowLayout {
    spacing: 0

    ListView {
        Layout.fillHeight: true
        Layout.preferredWidth: 200
        id: listView
        spacing: 2

        model: KUInstance.settingsPlugins

        delegate: Button {
            id: button
            icon.name: KUInstance.pluginIcon(modelData)
            icon.source: KUInstance.pluginIcon(
                             modelData) !== "" ? "qrc" + KUInstance.pluginIcon(
                                                     modelData) : ""
            icon.color: "transparent"
            text: KUInstance.pluginName(modelData)
            width: parent.width
            height: 50
            background: Rectangle {
                anchors.fill: parent
                color: button.ListView.isCurrentItem ? "salmon" : "lightgrey"
            }
            onClicked: {
                listView.currentIndex = index
                swipeView.currentIndex = index
            }
        }
    }

    Rectangle {
        color: "black"
        Layout.fillHeight: true
        Layout.preferredWidth: 1
    }

    SwipeView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        id: swipeView
        interactive: false
        clip: true
        Repeater {
            model: KUInstance.settingsPlugins
            Loader {
                property string name: KUInstance.pluginName(modelData)
                active: true // TODO add property if can be unloaded
                source: "qrc:/" + modelData + "/settings.qml"
                clip: true
            }
        }
    }
}
