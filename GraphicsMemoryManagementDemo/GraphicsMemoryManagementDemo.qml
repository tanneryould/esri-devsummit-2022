// [WriteFile Name=GraphicsMemoryManagementDemo, Category=Analysis]
// [Legal]
// Copyright 2022 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// [Legal]

import QtQuick 2.12
import QtQuick.Controls 2.12
import Esri.Samples 1.0

Item {
    // add a mapView component
    MapView {
        id: view
        anchors.fill: parent

        Component.onCompleted: {
            // Set and keep the focus on SceneView to enable keyboard navigation
            forceActiveFocus();
        }
    }

    // Declare the C++ instance which creates the scene etc. and supply the view
    GraphicsMemoryManagementDemoSample {
        id: gmmDemo
        mapView: view
    }

    Rectangle {
        color: "white"
        border.color: "black"
        x: 5
        y: 5
        width: col.width + 15
        height: col.height + 15

        Column {
            id: col
            anchors.centerIn: parent
            spacing: 10

            Button {
                id: button
                width: parent.width
                Text {
                    anchors.centerIn: parent
                    text: "Add graphics with parent: 'this'"
                    wrapMode: Text.WordWrap
                }
                onClicked: gmmDemo.badMemoryManagement();
            }

            Button {
                width: parent.width
                Text {
                    anchors.centerIn: parent
                    text: "Add graphics with parent: scoped QObject"
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    width: parent.width
                }
                onClicked: gmmDemo.properMemoryManagement();
            }

            Button {
                width: parent.width
                Text {
                    anchors.centerIn: parent
                    text: "Clear graphics"
                }
                onClicked: gmmDemo.clearGraphics();
            }

            Text {
                text: "Current graphics count: " + gmmDemo.graphicsOverlayCount;
            }

            Text {
                text: "Resident memory usage: " + (gmmDemo.usedMemory).toFixed(3) + " GB";
            }
        }
    }
}