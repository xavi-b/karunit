import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.FreeVirtualKeyboard 1.0

import Karunit 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Karunit"

    Connections {
        target: KUInstance
        function onPrompt(plugins, signalName, signalData) {
            var popupComponent = Qt.createComponent("ChoicePopup.qml")
            var popup = popupComponent.createObject(window, {
                                                        "plugins": plugins,
                                                        "signalName": signalName,
                                                        "signalData": signalData
                                                    })
            popup.open()
        }
    }

    InputPanel {
        id: inputPanel

        z: 99
        y: window.height

        anchors.left: parent.left
        anchors.right: parent.right

        btnTextFontFamily: "monospace"

        states: State {
            name: "visible"
            when: Qt.inputMethod.visible
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 150
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

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
            model: KUInstance.widgetPlugins
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
                    text: qsTr("Languages")
                    icon.source: "qrc:/icons/" + KUInstance.currentLocale + ".png"
                    icon.color: "transparent"
                    onClicked: {
                        stackView.push("qrc:/qml/Languages.qml")
                        label.text = Qt.binding(function () {
                            return text
                        })
                        drawer.close()
                    }
                }
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
                model: KUInstance.widgetPlugins
                Loader {
                    property string name: KUInstance.pluginName(modelData)
                    active: true // TODO add property if can be unloaded
                    source: "qrc:/" + modelData + "/widget.qml"
                    clip: true
                }
            }
        }
    }
}
