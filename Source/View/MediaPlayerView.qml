import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import "Components"

Item {
    // Properties from Model
    property string playlistName: "Unknown Playlist"
    property string title: "Unknown Title"
    property string artist: "Unknown Artist"
    property string playTime: "00:00"
    property bool isPlaying: true
    property real volume: 0

    // Demo Search Properties
    property var songList: [
        {
            title: "Song One",
            artist: "Artist A"
        },
        {
            title: "Song Two",
            artist: "Artist B"
        },
        {
            title: "Melody Track",
            artist: "Artist C"
        },
        {
            title: "Rhythm Song",
            artist: "Artist A"
        },
        {
            title: "Harmony Beat",
            artist: "Artist D"
        }
    ]
    property var filteredSongs: songList.length > 0 ? songList : []

    // Scale Factor
    readonly property real scaleFactor: Math.min(parent.width / 1024, parent.height / 600)

    // Top Controls Properties
    property real topControlButtonSize: 90
    property real topControlIconSize: 45
    property real topControlSearchHeight: 60
    property real topControlSearchRadius: 30
    property real topControlSearchIconSize: 30
    property real topControlSearchFontSize: 24
    property real topControlSpacing: 30
    property real topControlMargin: 18

    // Song Info Properties
    property real songInfoTitleSize: 44
    property real songInfoArtistSize: 36
    property real songInfoTimeSize: 34
    property real songInfoSpacing: 20

    // Control Buttons Properties
    property real controlButtonSize: 60
    property real controlIconSize: 24
    property real controlPlayIconSize: 30
    property real controlSpacing: 30

    // Volume Control Properties
    property real volumeIconSize: 24
    property real volumeSliderWidth: 100
    property real volumeSliderHeight: 24
    property real volumeSpacing: 8
    property real previousVolume: 1.0

    // Search Results Properties
    property real searchResultMaxHeight: 300
    property real searchResultItemHeight: 40
    property real searchResultFontSize: 16
    property real searchResultMargin: 10

    // QML Logic
    FolderDialog {
        id: folderDialog
        title: "Select Media Files Directory"
        onAccepted: {
            let folderPath = folderDialog.currentFolder.toString().replace("file://", "");
            console.log("Selected Folder: ", folderPath);
        }
        onRejected: {
            console.log("Folder Selection Canceled");
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"

        ColumnLayout {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20 * scaleFactor
            width: parent.width * 0.8
            spacing: 5 * scaleFactor
            z: 2

            // 1. Top Controls
            RowLayout {
                Layout.fillWidth: true
                Layout.topMargin: 35 * scaleFactor
                spacing: topControlSpacing * scaleFactor

                // Folder Button
                HoverButton {
                    Layout.preferredWidth: topControlButtonSize * scaleFactor
                    Layout.preferredHeight: topControlButtonSize * scaleFactor
                    flat: true
                    onClicked: folderDialog.open()
                    Image {
                        source: "qrc:/Assets/folder.png"
                        width: topControlIconSize * scaleFactor
                        height: topControlIconSize * scaleFactor
                        anchors.centerIn: parent
                    }
                }

                // Playlist Button
                HoverButton {
                    Layout.preferredWidth: topControlButtonSize * scaleFactor
                    Layout.preferredHeight: topControlButtonSize * scaleFactor
                    flat: true
                    onClicked: {
                        stackView.push("qrc:/Source/View/PlaylistView.qml");
                        console.log("Navigate to PlaylistView");
                    }
                    Image {
                        source: "qrc:/Assets/playlist.png"
                        width: topControlIconSize * scaleFactor
                        height: topControlIconSize * scaleFactor
                        anchors.centerIn: parent
                    }
                }

                // Search Bar
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: topControlSearchHeight * scaleFactor
                    radius: topControlSearchRadius * scaleFactor
                    color: "#e0e0e0"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            searchInput.forceActiveFocus();
                            if (searchInput.text !== "Search" && filteredSongs.length > 0) {
                                searchResultsView.visible = true;
                            }
                            console.log("Search bar clicked");
                        }
                    }

                    RowLayout {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: topControlMargin * scaleFactor
                        spacing: topControlSpacing * scaleFactor

                        Image {
                            source: "qrc:/Assets/search.png"
                            Layout.preferredWidth: topControlSearchIconSize * scaleFactor
                            Layout.preferredHeight: topControlSearchIconSize * scaleFactor
                            Layout.alignment: Qt.AlignVCenter
                        }

                        TextInput {
                            id: searchInput
                            Layout.fillWidth: true
                            text: "Search"
                            color: "#666666"
                            font.pixelSize: topControlSearchFontSize * scaleFactor
                            verticalAlignment: TextInput.AlignVCenter
                            onActiveFocusChanged: {
                                if (activeFocus && text === "Search") {
                                    text = "";
                                }
                                if (activeFocus && text !== "" && filteredSongs.length > 0) {
                                    searchResultsView.visible = true;
                                    console.log("Search bar focused, showing results for:", text);
                                } else if (!activeFocus) {
                                    if (text === "") {
                                        text = "Search";
                                    }
                                    searchResultsView.visible = false;
                                    console.log("Search bar lost focus");
                                }
                            }
                            onTextChanged: {
                                if (text !== "Search" && text !== "") {
                                    let query = text.toLowerCase();
                                    filteredSongs = songList.filter(song => song.title.toLowerCase().includes(query) || song.artist.toLowerCase().includes(query));
                                    if (activeFocus && filteredSongs.length > 0) {
                                        searchResultsView.visible = true;
                                    } else {
                                        searchResultsView.visible = false;
                                    }
                                    console.log("Search query:", text, "Results:", filteredSongs.length);
                                } else {
                                    filteredSongs = songList;
                                    searchResultsView.visible = false;
                                    console.log("Reset search results, count:", filteredSongs.length);
                                }
                            }
                            onAccepted: {
                                if (filteredSongs.length > 0) {
                                    title = filteredSongs[0].title;
                                    artist = filteredSongs[0].artist;
                                    searchResultsView.visible = false;
                                    searchInput.focus = false;
                                    console.log("Selected first result, title:", title);
                                }
                            }
                        }
                    }
                }
            }

            // 2. Search Result
            ListView {
                id: searchResultsView
                Layout.fillWidth: true
                Layout.preferredHeight: Math.min(filteredSongs.length * searchResultItemHeight * scaleFactor, searchResultMaxHeight * scaleFactor)
                visible: false
                clip: true
                interactive: true
                model: filteredSongs
                z: 2

                delegate: Rectangle {
                    width: searchResultsView.width
                    height: searchResultItemHeight * scaleFactor
                    color: mouseArea.containsMouse ? "#f0f0f0" : "#ffffff"
                    border.color: "#e0e0e0"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: searchResultMargin * scaleFactor
                        Text {
                            text: modelData.title
                            font.pixelSize: searchResultFontSize * scaleFactor
                            color: "#333333"
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                        Text {
                            text: modelData.artist
                            font.pixelSize: searchResultFontSize * scaleFactor
                            color: "#666666"
                        }
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            parent.color = "#f0f0f0";
                        }
                        onExited: {
                            parent.color = "#ffffff";
                        }
                        onClicked: {
                            title = modelData.title;
                            artist = modelData.artist;
                            searchResultsView.visible = false;
                            searchInput.focus = false;
                            console.log("Selected search result, title:", modelData.title, "artist:", modelData.artist);
                        }
                    }
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                    }
                }

                onVisibleChanged: {
                    opacity = visible ? 1.0 : 0.0;
                }

                onModelChanged: {
                    console.log("Search results updated, count:", count);
                }
            }
        }

        // 3. Song Info
        ColumnLayout {
            anchors.centerIn: parent
            spacing: songInfoSpacing * scaleFactor
            width: parent.width * 0.8
            z: 1

            Text {
                id: playlistText
                Layout.alignment: Qt.AlignHCenter
                text: playlistName
                font.pixelSize: songInfoArtistSize * scaleFactor
                color: "#666666"
                font.bold: true
            }

            Text {
                id: titleText
                Layout.alignment: Qt.AlignHCenter
                text: title
                font.pixelSize: songInfoTitleSize * scaleFactor
                color: "#000000"
                font.bold: true
            }

            Text {
                id: artistText
                Layout.alignment: Qt.AlignHCenter
                text: artist
                font.pixelSize: songInfoArtistSize * scaleFactor
                color: "#333333"
            }

            Text {
                id: timeText
                Layout.alignment: Qt.AlignHCenter
                text: playTime
                font.pixelSize: songInfoTimeSize * scaleFactor
                color: "#666666"
            }

            SliderComponent {
                id: progressSlider
                Layout.fillWidth: true
                Layout.preferredHeight: 30 * scaleFactor
                minValue: 0.0
                maxValue: 1.0
                step: 0.01
                backgroundColor: "#cccccc"
                fillColor: "#000000"
                handleColor: "#ffffff"
                handlePressedColor: "#000000"
                borderColor: "#000000"
            }
        }

        // 4. Control Buttons
        RowLayout {
            id: controlButtons
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: volumeControl.top
            anchors.bottomMargin: 40 * scaleFactor
            spacing: controlSpacing * scaleFactor

            HoverButton {
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                onClicked: {
                    console.log("Shuffle Button Clicked");
                }
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Assets/shuffle.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                }
            }

            HoverButton {
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                onClicked: {
                    console.log("Previous Button Clicked");
                }
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Assets/prev.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                }
            }

            HoverButton {
                id: playButton
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                property string imageSource: isPlaying ? "qrc:/Assets/pause.png" : "qrc:/Assets/play.png"
                onClicked: {
                    isPlaying = !isPlaying;
                    console.log(isPlaying ? "Play Button Clicked" : "Pause Button Clicked");
                }
                Image {
                    anchors.centerIn: parent
                    source: playButton.imageSource
                    width: controlPlayIconSize * scaleFactor
                    height: controlPlayIconSize * scaleFactor
                }
            }

            HoverButton {
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                onClicked: {
                    console.log("Next Button Clicked");
                }
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Assets/next.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                }
            }

            HoverButton {
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                onClicked: {
                    console.log("Repeat Button Clicked");
                }
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Assets/repeat.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                }
            }
        }

        // 5. Volume Slider
        RowLayout {
            id: volumeControl
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20 * scaleFactor
            spacing: volumeSpacing * scaleFactor

            HoverButton {
                Layout.preferredWidth: volumeIconSize * scaleFactor
                Layout.preferredHeight: volumeIconSize * scaleFactor
                flat: true
                onClicked: {
                    volume = (volume === 0) ? previousVolume : 0;
                    previousVolume = (volume === 0) ? previousVolume : volume;
                    console.log("Volume Button Clicked, volume:", volume);
                }
                Image {
                    anchors.centerIn: parent
                    source: volume === 0 ? "qrc:/Assets/muted.png" : "qrc:/Assets/volume.png"
                    width: volumeIconSize * scaleFactor
                    height: volumeIconSize * scaleFactor
                }
            }

            SliderComponent {
                id: volumeSlider
                Layout.preferredWidth: volumeSliderWidth * scaleFactor
                Layout.preferredHeight: volumeSliderHeight * scaleFactor
                minValue: 0.0
                maxValue: 1.0
                step: 0.1
                value: volume
                onValueChanged: {
                    volume = value;
                }
                backgroundColor: "#cccccc"
                fillColor: "#000000"
                handleColor: "#ffffff"
                handlePressedColor: "#000000"
                borderColor: "#000000"
            }
        }

        MouseArea {
            anchors.fill: parent
            z: 0
            propagateComposedEvents: true
            onPressed: {
                if (!searchResultsView.contains(Qt.point(mouse.x - searchResultsView.x, mouse.y - searchResultsView.y)) && !searchInput.contains(Qt.point(mouse.x - searchInput.x, mouse.y - searchInput.y))) {
                    searchInput.focus = false;
                    searchResultsView.visible = false;
                    console.log("Focus removed from search bar, text:", searchInput.text);
                }
                mouse.accepted = false;
            }
        }
    }
}
