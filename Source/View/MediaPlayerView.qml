import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import "Components"

Item {
    // Properties from Model with null checks and default values
    property string playlistName: appController && appController.playbackController && appController.playbackController.currentPlaylistName ? appController.playbackController.currentPlaylistName : "Unknown Playlist"
    property string title: appController && appController.playbackController && appController.playbackController.currentMediaTitle ? appController.playbackController.currentMediaTitle : "Unknown Title"
    property string artist: appController && appController.playbackController && appController.playbackController.currentMediaArtist ? appController.playbackController.currentMediaArtist : "Unknown Artist"
    property string playTime: appController && appController.playbackController ? formatDuration(appController.playbackController.position) : "0:00"
    property bool isPlaying: appController && appController.playbackController ? appController.playbackController.playbackState === 1 : false // 1 là PlayingState
    property real volume: appController && appController.playbackController ? appController.playbackController.volume / 100.0 : 0.5
    property bool shuffle: appController && appController.playbackController ? appController.playbackController.shuffle : false
    property int repeatMode: appController && appController.playbackController ? appController.playbackController.repeatMode : 0
    property bool muted: appController && appController.playbackController ? appController.playbackController.muted : false

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
    property real previousVolume: 0.5 // Default to 50%

    // Search Results Properties
    property real searchResultMaxHeight: 300
    property real searchResultItemHeight: 40
    property real searchResultFontSize: 16
    property real searchResultMargin: 10

    // Search Results
    property var filteredSongs: []

    function formatDuration(milliseconds) {
        if (!milliseconds || milliseconds < 0 || isNaN(milliseconds)) {
            return "0:00";
        }
        let seconds = Math.floor(milliseconds / 1000);
        let minutes = Math.floor(seconds / 60);
        let secs = Math.floor(seconds % 60);
        return minutes + ":" + (secs < 10 ? "0" : "") + secs;
    }

    // Debounce timer for search
    Timer {
        id: searchDebounceTimer
        interval: 200 // Wait 200ms before triggering search
        repeat: false
        onTriggered: {
            if (searchInput.text !== "Search" && searchInput.text !== "" && appController && appController.playlistController) {
                filteredSongs = appController.playlistController.searchMediaFiles(searchInput.text);
                searchResultsView.visible = searchInput.activeFocus && filteredSongs.length > 0;
                console.log("Search query:", searchInput.text, "Results:", filteredSongs.length);
            } else {
                filteredSongs = [];
                searchResultsView.visible = false;
                console.log("Reset search results");
            }
        }
    }

    // Only connect signals when appController and playbackController are available
    Connections {
        target: appController && appController.playbackController ? appController.playbackController : null
        function onCurrentMediaChanged() {
            if (appController && appController.playbackController) {
                playlistName = appController.playbackController.currentPlaylistName || "Unknown Playlist";
                title = appController.playbackController.currentMediaTitle || "Unknown Title";
                artist = appController.playbackController.currentMediaArtist || "Unknown Artist";
                progressSlider.maxValue = appController.playbackController.currentMediaDuration;
                console.log("Current media changed:", title, "Artist:", artist, "Playlist:", playlistName);
            }
        }
        function onPlaybackStateChanged() {
            if (appController && appController.playbackController) {
                isPlaying = appController.playbackController.playbackState === 1; // 1 là PlayingState
                console.log("Playback state changed:", isPlaying ? "Playing" : "Paused/Stopped");
            }
        }
        function onPositionChanged() {
            if (appController && appController.playbackController) {
                playTime = formatDuration(appController.playbackController.position);
                progressSlider.value = appController.playbackController.position;
            }
        }
        function onVolumeChanged() {
            if (appController && appController.playbackController) {
                volume = appController.playbackController.volume / 100.0;
            }
        }
        function onShuffleChanged() {
            if (appController && appController.playbackController) {
                shuffle = appController.playbackController.shuffle;
                console.log("Shuffle changed:", shuffle);
            }
        }
        function onRepeatModeChanged() {
            if (appController && appController.playbackController) {
                repeatMode = appController.playbackController.repeatMode;
                console.log("Repeat mode changed:", repeatMode);
            }
        }
        function onMutedChanged() {
            if (appController && appController.playbackController) {
                muted = appController.playbackController.muted;
                console.log("Muted changed:", muted);
            }
        }
    }

    // QML Logic
    FolderDialog {
        id: folderDialog
        title: "Select Media Files Directory"
        onAccepted: {
            if (appController && appController.playlistController) {
                let folderPath = folderDialog.currentFolder.toString().replace("file://", "");
                appController.playlistController.loadFolder(folderPath);
                console.log("FolderDialog::folderDialog - Selected Folder: ", folderPath);
            }
        }
        onRejected: {
            console.log("FolderDialog::folderDialog - Folder Selection Canceled");
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
                                searchDebounceTimer.restart();
                            }
                            onAccepted: {
                                if (filteredSongs.length > 0 && appController && appController.playlistController && appController.playbackController) {
                                    let playlist = appController.playlistController.getPlaylist(filteredSongs[0].playlistName);
                                    if (playlist) {
                                        appController.playbackController.playMedia(playlist, filteredSongs[0].index);
                                        searchResultsView.visible = false;
                                        searchInput.focus = false;
                                        console.log("Selected first result, title:", filteredSongs[0].title);
                                    }
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

                    Text {
                        anchors.fill: parent
                        anchors.margins: searchResultMargin * scaleFactor
                        text: modelData.playlistName + " - " + modelData.title + " - " + modelData.artist
                        font.pixelSize: searchResultFontSize * scaleFactor
                        color: "#333333"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
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
                            if (appController && appController.playlistController && appController.playbackController) {
                                let playlist = appController.playlistController.getPlaylist(modelData.playlistName);
                                if (playlist) {
                                    appController.playbackController.playMedia(playlist, modelData.index);
                                    searchResultsView.visible = false;
                                    searchInput.focus = false;
                                    console.log("Selected search result, title:", modelData.title, "artist:", modelData.artist);
                                }
                            }
                        }
                    }
                }

                Behavior on opacity {
                    NumberAnimation {
                        duration: 200
                    }
                }

                Behavior on height {
                    NumberAnimation {
                        duration: 200
                    }
                }

                onVisibleChanged: {
                    opacity = visible ? 1.0 : 0.5;
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
                text: playTime + " / " + (appController && appController.playbackController ? formatDuration(appController.playbackController.currentMediaDuration) : "0:00")
                font.pixelSize: songInfoTimeSize * scaleFactor
                color: "#666666"
            }

            SliderComponent {
                id: progressSlider
                Layout.fillWidth: true
                Layout.preferredHeight: 30 * scaleFactor
                minValue: 0.0
                maxValue: appController && appController.playbackController ? appController.playbackController.currentMediaDuration : 0
                step: 100
                value: appController && appController.playbackController ? appController.playbackController.position : 0
                backgroundColor: "#cccccc"
                fillColor: "#000000"
                handleColor: "#ffffff"
                handlePressedColor: "#000000"
                borderColor: "#000000"
                onValueChanged: {
                    if (pressed && appController && appController.playbackController) {
                        appController.playbackController.setPosition(value);
                    }
                }
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
                    if (appController && appController.playbackController) {
                        appController.playbackController.setShuffle(!shuffle);
                        console.log("Shuffle Button Clicked, enabled:", !shuffle);
                    }
                }
                Image {
                    anchors.centerIn: parent
                    source: "qrc:/Assets/shuffle.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                    opacity: shuffle ? 1.0 : 0.5 // Show when active, partially visible when inactive
                }
            }

            HoverButton {
                Layout.preferredWidth: controlButtonSize * scaleFactor
                Layout.preferredHeight: controlButtonSize * scaleFactor
                flat: true
                onClicked: {
                    if (appController && appController.playbackController) {
                        appController.playbackController.previous();
                        console.log("Previous Button Clicked");
                    }
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
                    if (appController && appController.playbackController) {
                        if (isPlaying) {
                            appController.playbackController.pause();
                        } else {
                            appController.playbackController.play();
                        }
                        console.log(isPlaying ? "Pause Button Clicked" : "Play Button Clicked");
                    }
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
                    if (appController && appController.playbackController) {
                        appController.playbackController.next();
                        console.log("Next Button Clicked");
                    }
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
                    if (appController && appController.playbackController) {
                        let newMode = (repeatMode + 1) % 3; // Cycle through 0, 1, 2
                        appController.playbackController.setRepeatMode(newMode);
                        console.log("Repeat Button Clicked, mode:", newMode);
                    }
                }
                Image {
                    anchors.centerIn: parent
                    source: repeatMode === 1 ? "qrc:/Assets/repeat-one.png" : "qrc:/Assets/repeat.png"
                    width: controlIconSize * scaleFactor
                    height: controlIconSize * scaleFactor
                    opacity: repeatMode > 0 ? 1.0 : 0.5 // Show when active, partially visible when inactive
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
                    if (appController && appController.playbackController) {
                        if (muted) {
                            appController.playbackController.setMuted(false);
                            appController.playbackController.setVolume(previousVolume * 100);
                        } else {
                            previousVolume = volume > 0 ? volume : previousVolume;
                            appController.playbackController.setVolume(0);
                            appController.playbackController.setMuted(true);
                        }
                        console.log("Volume Button Clicked, muted:", muted, "volume:", volume);
                    }
                }
                Image {
                    anchors.centerIn: parent
                    source: muted || volume === 0 ? "qrc:/Assets/muted.png" : "qrc:/Assets/volume.png"
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
                    if (appController && appController.playbackController && value !== volume) {
                        volume = value;
                        appController.playbackController.setVolume(value * 100);
                        if (value > 0 && muted) {
                            appController.playbackController.setMuted(false);
                        }
                        previousVolume = value > 0 ? value : previousVolume;
                    }
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
            onPressed: function (mouse) {
                if (!searchResultsView.contains(Qt.point(mouse.x - searchResultsView.x, mouse.y - searchResultsView.y)) && !searchInput.contains(Qt.point(mouse.x - searchInput.x, mouse.y - searchInput.y))) {
                    searchInput.focus = false;
                    searchResultsView.visible = false;
                    console.log("Focus removed from search bar, text:", searchInput.text);
                }
                mouse.accepted = false;
            }
        }
    }

    // Log when component is completed to debug initialization
    Component.onCompleted: {
        console.log("MediaPlayerView: Component completed, appController exists:", appController !== null);
        if (!appController || !appController.playbackController) {
            console.log("MediaPlayerView: Warning - appController or playbackController is null");
        }
    }
}
