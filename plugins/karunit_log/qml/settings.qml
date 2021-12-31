import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import KarunitPlugins 1.0

ScrollView {
    id: view
    anchors.fill: parent
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

    TextArea {
        anchors.fill: parent
        text: KUPLogPluginConnector.logs
    }
}
