import QtQuick 2.6
import QtQuick.Controls 2.5

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 400
    height: 400

    Text {
        id: txtMsg
        text: qtControl.status
        visible: false
    }



    Column {
        x: 200
        y: 100
        Switch {
            id: udpliveswitch
            text: qsTr("Remote live")
            onCheckedChanged: if (checked)
                              {
                                  localswitch.checked = false
                                  udpfileswitch.checked = false
                                  qtControl.set_udp_live()
                              }
                              else if (!checked)
                                  qtControl.set_empty()
        }
        Switch {
            id: udpfileswitch
            text: qsTr("Remote file")
            onCheckedChanged: if (checked)
                              {
                                  localswitch.checked = false
                                  udpliveswitch.checked = false
                                  qtControl.set_udp_file()
                              }
                              else if (!checked)
                                  qtControl.set_empty()
        }
        Switch {
            id: localswitch
            text: qsTr("Local file")
            onCheckedChanged: if (checked)
                              {
                                  udpliveswitch.checked = false
                                  udpfileswitch.checked = false
                                  qtControl.set_local_file()
                              }
                              else if (!checked)
                                  qtControl.set_empty()
        }

    }

    Text {
        id: textt
        x: 35
        y: 180
        width: 338
        height: 29
        text: txtMsg.text
    }

    Button {
        id: stop
        x: 256
        y: 311
        text: qsTr("STOP")
        onClicked: qtControl.stop()
    }

    Button {
        id: play
        x: 150
        y: 311
        text: qsTr("PLAY")
        onClicked: qtControl.play()
    }

    Button {
        id: pause
        x: 45
        y: 311
        text: qsTr("PAUSE")
        onClicked: qtControl.pause()
    }

//    TextField {
//        id: ip
//        anchors.verticalCenterOffset: -141
//        anchors.horizontalCenterOffset: -65
//        placeholderText: qsTr("Address 192.168.1.7")
//        anchors.centerIn: parent

//       // onTextChanged:
//    }
}
