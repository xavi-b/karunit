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

        model: KUMainWindow.aboutPlugins

        delegate: Button {
            id: button
            icon.name: KUMainWindow.pluginIcon(modelData)
            icon.source: KUMainWindow.pluginIcon(
                             modelData) !== "" ? "qrc" + KUMainWindow.pluginIcon(
                                                     modelData) : ""
            icon.color: "transparent"
            text: KUMainWindow.pluginName(modelData)
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
            model: KUMainWindow.aboutPlugins
            Loader {
                property string name: KUMainWindow.pluginName(modelData)
                active: true // TODO add property if can be unloaded
                source: "qrc:/" + modelData + "/about.qml"
                clip: true
            }
        }
    }
}
