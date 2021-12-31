import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Karunit 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Karunit")

    ToolBar {
        id: header
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ToolButton {
            text: drawer.opened || stackView.depth > 1 ? "<" : "⋮"
            onClicked: {
                if (drawer.opened) {
                    drawer.close()
                    return
                }

                if (stackView.depth > 1) {
                    stackView.pop()
                    listView.currentIndex = -1
                    return
                }

                drawer.open()
            }
        }

        Label {
            id: label
            anchors.centerIn: parent
            text: swipeView.currentItem.name
        }
    }

    Drawer {
        id: drawer
        y: header.height
        width: window.width / 2
        height: window.height - header.height
        interactive: false

        ListView {
            id: listView
            anchors.fill: parent

            spacing: 2
            model: KUMainWindow.widgetPlugins
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
                    stackView.pop(stackView.initialItem)
                    swipeView.currentIndex = index
                    label.text = swipeView.currentItem.name
                    drawer.close()
                }
            }

            footerPositioning: ListView.OverlayFooter
            footer: ColumnLayout {
                z: listView.z + 10
                width: parent.width
                spacing: 2
                Button {
                    Layout.fillWidth: true
                    text: qsTr("Settings")
                    onClicked: {
                        stackView.push("qrc:/qml/Settings.qml")
                        label.text = text
                        drawer.close()
                    }
                }
                Button {
                    Layout.fillWidth: true
                    text: qsTr("About")
                    onClicked: {
                        stackView.push("qrc:/qml/About.qml")
                        label.text = text
                        drawer.close()
                    }
                }
            }
        }
    }

    StackView {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        id: stackView
        initialItem: SwipeView {
            id: swipeView
            interactive: false
            clip: true
            Repeater {
                model: KUMainWindow.widgetPlugins
                Loader {
                    property string name: KUMainWindow.pluginName(modelData)
                    active: true // TODO add property if can be unloaded
                    source: "qrc:/" + modelData + "/widget.qml"
                    clip: true
                }
            }
        }
    }
}
