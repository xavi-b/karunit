import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Karunit 1.0

Popup {
    id: popup
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: parent.width - 100
    height: 200
    modal: true

    property var plugins: []
    property string signalName
    property var signalData

    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: listview
            orientation: Qt.Horizontal

            model: plugins

            delegate: Button {
                width: height
                height: listview.height
                icon.name: KUInstance.pluginIcon(modelData)
                icon.source: KUInstance.pluginIcon(
                                 modelData) !== "" ? "qrc" + KUInstance.pluginIcon(
                                                         modelData) : ""
                text: KUInstance.pluginName(modelData)
                onClicked: {
                    KUInstance.selectPromptedPlugin(modelData, signalName,
                                                    signalData)
                    popup.close()
                }
            }
        }

        Button {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Close")
            onClicked: popup.close()
        }
    }
}
