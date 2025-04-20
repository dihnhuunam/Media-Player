# Media Player Use Case Specification (English)

## Use Case Specification: Media Player

### 1. User Registration (UC-001)

#### 1.1 Brief Description

This use case describes how a guest user registers for a new account to access the Media Player application in online mode.

#### 1.2 Actors

- **Primary Actor**: Guest User

#### 1.3 Preconditions

- The user is not logged in and has selected online mode.
- The application is running and connected to MySQL and Firebase.

#### 1.4 Basic Flow

1. The Guest User navigates to the registration page via the application’s UI after selecting online mode.
2. The system displays a registration form requesting a username, password, and optional details (e.g., email).
3. The Guest User enters the required information and submits the form.
4. The system validates the input:
   - Username must be unique.
   - Password must meet complexity requirements (e.g., minimum length, special characters).
5. The system stores the encrypted credentials in MySQL and Firebase.
6. The system displays a success message and redirects the user to the login page.

#### 1.5 Alternative Flows

- **A1: Username Already Exists**
  - At step 4, if the username is taken, the system displays an error message: "Username already exists."
  - The user is prompted to enter a different username.
  - Return to step 3.
- **A2: Invalid Password**
  - At step 4, if the password does not meet requirements, the system displays an error message: "Password is too weak."
  - The user is prompted to enter a stronger password.
  - Return to step 3.

#### 1.6 Exceptions

- **E1: Database Connection Failure**
  - If MySQL or Firebase is unavailable, the system displays: "Unable to connect to the server. Please try again later."
  - The user is prompted to retry or switch to offline mode.

#### 1.7 Postconditions

- A new user account is created in MySQL and Firebase.
- The user is redirected to the login page.

#### 1.8 Priority

High

#### 1.9 Frequency of Use

Occasional (once per user).

#### 1.10 Assumptions

- MySQL and Firebase support secure storage of credentials.
- The UI provides a clear registration form.

---

### 2. User Login (UC-002)

#### 2.1 Brief Description

This use case describes how a registered user logs into the Media Player in online mode to access cloud-based features.

#### 2.2 Actors

- **Primary Actor**: Registered User

#### 2.3 Preconditions

- The user has a registered account.
- The application is running and connected to MySQL and Firebase.
- The user has selected online mode.

#### 2.4 Basic Flow

1. The Registered User navigates to the login page after selecting online mode.
2. The system displays a login form requesting a username and password.
3. The user enters their credentials and submits the form.
4. The system validates the credentials against MySQL and Firebase.
5. If valid, the system caches the login information for persistent login.
6. The system grants access to the Media Player’s main interface with cloud connectivity and a smooth transition animation.

#### 2.5 Alternative Flows

- **A1: Incorrect Credentials**
  - At step 4, if the credentials are invalid, the system displays: "Incorrect username or password."
  - The user is prompted to retry or switch to offline mode.
  - Return to step 3.

#### 2.6 Exceptions

- **E1: Database Connection Failure**
  - If MySQL or Firebase is unavailable, the system displays: "Unable to connect to the server. Please try again later."
  - The user is prompted to retry or switch to offline mode.

#### 2.7 Postconditions

- The user is authenticated and has access to the Media Player with cloud-based features.
- Login information is cached for future online sessions.

#### 2.8 Priority

High

#### 2.9 Frequency of Use

Frequent (once per session unless cached).

#### 2.10 Assumptions

- MySQL and Firebase store encrypted credentials.
- Persistent login is supported via secure caching.

---

### 3. Select Online or Offline Mode (UC-009)

#### 3.1 Brief Description

This use case describes how a user selects between online and offline modes at the login screen.

#### 3.2 Actors

- **Primary Actor**: Guest User or Registered User

#### 3.3 Preconditions

- The application is running.
- The user is at the login screen.

#### 3.4 Basic Flow

1. The system presents the login screen with options for "Online Mode" and "Offline Mode."
2. The user selects either:
   - **Online Mode**: Proceeds to the login or registration page for cloud access.
   - **Offline Mode**: Bypasses login and navigates directly to the music playback interface with local file access only.
3. If Online Mode is selected, the system initiates UC-001 (User Registration) or UC-002 (User Login).
4. If Offline Mode is selected, the system navigates to the music playback interface with restricted access to local files only.

#### 3.5 Alternative Flows

- **A1: Switch Mode**
  - At step 2, the user can toggle between modes before confirming.
  - Return to step 2.

#### 3.6 Exceptions

- None

#### 3.7 Postconditions

- In Online Mode: The user proceeds to login/registration for cloud access.
- In Offline Mode: The user accesses the music playback interface limited to local files.

#### 3.8 Priority

High

#### 3.9 Frequency of Use

Frequent (every session).

#### 3.10 Assumptions

- The UI clearly distinguishes between online and offline mode options.
- Offline mode supports local file playback without cloud connectivity.

---

### 4. Play Music from Database (UC-003)

#### 4.1 Brief Description

This use case describes how a logged-in user plays music from a Firebase-stored playlist in online mode.

#### 4.2 Actors

- **Primary Actor**: Logged-in User

#### 4.3 Preconditions

- The user is logged in and in online mode.
- Firebase contains music files or references and is accessible.

#### 4.4 Basic Flow

1. The Logged-in User navigates to the playlist section in the UI.
2. The system retrieves and displays available playlists from Firebase.
3. The user selects a playlist.
4. The system retrieves and displays the songs in the selected playlist.
5. The user selects a song to play.
6. The system uses QMediaPlayer to stream or play the song.
7. The system displays the song’s metadata (title, artist, duration) and updates the progress bar in real-time.

#### 4.5 Alternative Flows

- **A1: Empty Playlist**
  - At step 4, if the playlist is empty, the system displays: "This playlist is empty."
  - The user is prompted to add songs or select another playlist.
  - Return to step 3.

#### 4.6 Exceptions

- **E1: Database Connection Failure**
  - If Firebase is unavailable, the system displays: "Unable to retrieve playlists. Please try again or switch to offline mode."
  - The user is prompted to retry or switch modes.
- **E2: Media Playback Failure**
  - If the song fails to play, the system displays: "Error playing media."
  - The system skips to the next song, if available.

#### 4.7 Postconditions

- The selected song is playing.
- The UI displays the song’s metadata and playback progress.

#### 4.8 Priority

High

#### 4.9 Frequency of Use

Frequent

#### 4.10 Assumptions

- Firebase stores valid music file references.
- QMediaPlayer supports the audio formats in Firebase.

---

### 5. Play Music from Local File/Folder (UC-004)

#### 5.1 Brief Description

This use case describes how a user plays a single music file or a playlist from a local folder in offline or online mode.

#### 5.2 Actors

- **Primary Actor**: Logged-in User (online mode) or Guest User (offline mode)

#### 5.3 Preconditions

- The user is in offline mode or logged in for online mode.
- The local file system is accessible.

#### 5.4 Basic Flow

1. The user selects the option to play a local file or folder via the UI.
2. The system opens a file/folder browser dialog.
3. The user selects a single music file or a folder.
4. If a folder is selected, the system scans for supported audio files (e.g., MP3, WAV) and creates a playlist.
5. The user selects a song from the file or playlist.
6. The system uses QMediaPlayer to play the song.
7. The system displays the song’s metadata (title, artist, duration) using QMediaMetaData and updates the progress bar.

#### 5.5 Alternative Flows

- **A1: No Supported Files**
  - At step 4, if no supported files are found, the system displays: "No supported audio files found."
  - The user is prompted to select another file/folder.
  - Return to step 3.

#### 5.6 Exceptions

- **E1: File Access Failure**
  - If the file/folder is inaccessible, the system displays: "Unable to access file/folder."
  - The user is prompted to retry.
- **E2: Media Playback Failure**
  - If the song fails to play, the system displays: "Error playing media."
  - The system skips to the next song, if available.

#### 5.7 Postconditions

- The selected song is playing.
- The UI displays the song’s metadata and playback progress.

#### 5.8 Priority

High

#### 5.9 Frequency of Use

Frequent

#### 5.10 Assumptions

- The local file system contains accessible audio files.
- QMediaPlayer and QMediaMetaData support the selected file formats.

---

### 6. Control Music Playback (UC-005)

#### 6.1 Brief Description

This use case describes how a user controls music playback using basic controls in online or offline mode.

#### 6.2 Actors

- **Primary Actor**: Logged-in User (online mode) or Guest User (offline mode)

#### 6.3 Preconditions

- The user is in offline mode or logged in for online mode.
- A song is loaded or playing.

#### 6.4 Basic Flow

1. The user interacts with the UI controls (play/pause, next/previous, volume up/down, progress bar seek).
2. The system processes the input:
   - Play/Pause: Toggles the playback state.
   - Next/Previous: Skips to the next or previous song in the playlist.
   - Volume Up/Down: Adjusts the volume level.
   - Progress Bar Seek: Moves playback to the selected position.
3. The system updates the UI with the current playback state, time, and duration.
4. The system ensures smooth animations for control interactions.

#### 6.5 Alternative Flows

- **A1: No Next/Previous Song**
  - At step 2, if no next/previous song exists, the system disables the respective button or takes no action.
- **A2: End of Playlist**
  - At step 2, if the last song ends, the system stops playback or loops the playlist (based on settings).

#### 6.6 Exceptions

- **E1: Media Playback Failure**
  - If playback fails, the system displays: "Error playing media."
  - The system attempts to skip to the next song.

#### 6.7 Postconditions

- The playback state reflects the user’s actions.
- The UI is updated with real-time playback information.

#### 6.8 Priority

High

#### 6.9 Frequency of Use

Very Frequent

#### 6.10 Assumptions

- The UI provides responsive controls.
- QMediaPlayer supports real-time playback updates.

---

### 7. Search Songs or Playlists (UC-006)

#### 7.1 Brief Description

This use case describes how a logged-in user searches for songs or playlists in online mode.

#### 7.2 Actors

- **Primary Actor**: Logged-in User

#### 7.3 Preconditions

- The user is logged in and in online mode.
- Firebase is accessible.

#### 7.4 Basic Flow

1. The Logged-in User navigates to the song or playlist search page.
2. The system displays a search bar with a modern UI.
3. The user enters a search query (e.g., song title, artist, playlist name).
4. The system queries Firebase for matching results.
5. The system displays the results in a list with metadata (e.g., song title, artist, playlist name).
6. The user selects a result to play (for songs) or view (for playlists).

#### 7.5 Alternative Flows

- **A1: No Results Found**
  - At step 5, if no matches are found, the system displays: "No results found for [query]."
  - The user can modify the query and retry.
  - Return to step 3.

#### 7.6 Exceptions

- **E1: Database Connection Failure**
  - If Firebase is unavailable, the system displays: "Unable to search. Please try again or switch to offline mode."
  - The user is prompted to retry or switch modes.

#### 7.7 Postconditions

- Matching songs or playlists are displayed.
- The user can interact with the results (play or view).

#### 7.8 Priority

Medium

#### 7.9 Frequency of Use

Moderate

#### 7.10 Assumptions

- Firebase supports efficient text-based searches.
- The UI provides clear result presentation.

---

### 8. Control Media Player via Microcontroller (UC-007)

#### 8.1 Brief Description

This use case describes how a user controls the Media Player using an external microcontroller in online or offline mode.

#### 8.2 Actors

- **Primary Actor**: Logged-in User (online mode) or Guest User (offline mode)
- **Secondary Actor**: External Microcontroller (e.g., S32K144)

#### 8.3 Preconditions

- The user is in offline mode or logged in for online mode.
- The microcontroller is connected via UART, USB, or Bluetooth.

#### 8.4 Basic Flow

1. The user ensures the microcontroller is connected to the system.
2. The system establishes communication with the microcontroller.
3. The user presses a button on the microcontroller (play/pause, next/previous, volume up/down).
4. The system receives the input via the communication protocol.
5. The system processes the input and updates the playback state using QMediaPlayer.
6. The system updates the UI to reflect the new state (e.g., play/pause icon, volume level).

#### 8.5 Alternative Flows

- **A1: No Song Playing**
  - At step 5, if no song is playing and play is pressed, the system starts the first song in the current playlist.
- **A2: No Next/Previous Song**
  - At step 5, if no next/previous song exists, the system ignores the input.

#### 8.6 Exceptions

- **E1: Connection Failure**
  - If the microcontroller connection fails, the system displays: "Microcontroller disconnected."
  - The user is prompted to reconnect.
- **E2: Media Playback Failure**
  - If playback fails, the system displays: "Error playing media."
  - The system attempts to skip to the next song.

#### 8.7 Postconditions

- The playback state reflects the microcontroller inputs.
- The UI is updated accordingly.

#### 8.8 Priority

Medium

#### 8.9 Frequency of Use

Occasional (depends on microcontroller usage).

#### 8.10 Assumptions

- The microcontroller sends standard control signals.
- The system supports the chosen communication protocol.

---

### 9. Song Recommendation via Chatbot (UC-008, Optional)

#### 9.1 Brief Description

This use case describes how a logged-in user interacts with an optional chatbot to receive song recommendations in online mode.

#### 9.2 Actors

- **Primary Actor**: Logged-in User

#### 9.3 Preconditions

- The user is logged in and in online mode.
- The chatbot feature is enabled and functional.

#### 9.4 Basic Flow

1. The Logged-in User navigates to the chatbot interface in the UI.
2. The system displays a conversational interface with a text input field.
3. The user enters preferences (e.g., "play rock music" or "happy songs").
4. The system processes the input using natural language processing.
5. The system retrieves matching songs from Firebase.
6. The system displays a list of recommended songs with metadata.
7. The user selects a song to play.

#### 9.5 Alternative Flows

- **A1: No Matching Songs**
  - At step 6, if no songs match, the system displays: "No songs found. Try different preferences."
  - The user can enter new preferences.
  - Return to step 3.

#### 9.6 Exceptions

- **E1: Chatbot Processing Failure**
  - If the system fails to process input, the system displays: "Unable to process request. Please try again."
  - The user is prompted to retry.

#### 9.7 Postconditions

- A list of recommended songs is displayed.
- The user can play a recommended song.

#### 9.8 Priority

Low

#### 9.9 Frequency of Use

Occasional

#### 9.10 Assumptions

- The system supports basic natural language understanding for the chatbot.
- Firebase contains sufficient songs for recommendations.
