import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Karunit 1.0

Item {
    Grid {
        anchors.centerIn: parent
        columns: 3
        spacing: 15

        Repeater {
            model: KUInstance.availableLocales

            // TODO "Icon made by Freepik from www.flaticon.com"
            RoundButton {
                icon.source: "qrc:/icons/" + modelData + ".png"
                icon.color: "transparent"
                onClicked: {
                    KUInstance.switchLocale(modelData)
                }
            }
        }
    }
}
