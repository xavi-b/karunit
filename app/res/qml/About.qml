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

        model: KUInstance.aboutPlugins

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
                color: swipeView.currentIndex == index + 1 ? "salmon" : "lightgrey"
            }
            onClicked: {
                listView.currentIndex = index
                swipeView.currentIndex = index + 1
            }
        }

        header: Item {
            width: parent.width
            height: 50 + listView.spacing
            Button {
                id: header
                text: "Karunit"
                width: parent.width
                height: 50
                background: Rectangle {
                    anchors.fill: parent
                    color: swipeView.currentIndex == 0 ? "salmon" : "lightgrey"
                }
                onClicked: {
                    swipeView.currentIndex = 0
                }
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

        ScrollView {
            contentWidth: width

            Column {
                width: parent.width
                spacing: 5

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: "Karunit"
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: "<p>xavi-b/make_karunit</p>" + "LGPL 3.0 License"
                }

                Item {
                    height: qtlogo.sourceSize.width
                    width: height + 20
                    Image {
                        anchors.centerIn: parent
                        id: qtlogo
                        source: "qrc:/qt-project.org/qmessagebox/images/qtlogo-64.png"
                    }
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: qsTr(
                              "<p>Qt is a C++ toolkit for cross-platform application development.</p>" + "<p>Qt provides single-source portability across all major desktop operating systems. It is also available for embedded Linux and other embedded and mobile operating systems.</p>" + "<p>Qt is available under multiple licensing options designed to accommodate the needs of our various users.</p>" + "<p>Qt licensed under our commercial license agreement is appropriate for development of proprietary/commercial software where you do not want to share any source code with third parties or otherwise cannot comply with the terms of GNU (L)GPL.</p>" + "<p>Qt licensed under GNU (L)GPL is appropriate for the development of Qt&nbsp;applications provided you can comply with the terms and conditions of the respective licenses.</p>" + "<p>Please see <a href=\"http://%2/\">%2</a> for an overview of Qt licensing.</p>"
                              + "<p>Copyright (C) %1 The Qt Company Ltd and other contributors.</p>"
                              + "<p>Qt and the Qt logo are trademarks of The Qt Company Ltd.</p>"
                              + "<p>Qt is The Qt Company Ltd product developed as an open source project. See <a href=\"http://%3/\">%3</a> for more information.</p>").arg(
                              "2021").arg("qt.io/licensing").arg("qt.io")
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: "QtFreeVirtualKeyboard"
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: "<p>xavi-b/QtFreeVirtualKeyboard</p>"
                          + "<p>amarula/QtFreeVirtualKeyboard</p>"
                          + "<p>githubuser0xFFFF/QtFreeVirtualKeyboard</p>" + "MIT License"
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    leftPadding: 10
                    rightPadding: leftPadding
                    text: "Flag icons made by Freepik from www.flaticon.com"
                }
            }
        }

        Repeater {
            model: KUInstance.aboutPlugins

            Loader {
                property string name: KUInstance.pluginName(modelData)
                active: true // TODO add property if can be unloaded
                source: "qrc:/" + modelData + "/about.qml"
                clip: true
            }
        }
    }
}
