# Media Player Use Cases (English)

## 1. Use Case: User Registration

- **Use Case ID**: UC-001
- **Actors**: Guest User
- **Description**: A guest user creates a new account to access the Media Player in online mode for database features.
- **Preconditions**: The user is not logged in and has selected online mode.
- **Postconditions**: The user has a registered account and can log in for online mode.
- **Basic Flow**:
  1. The user navigates to the registration page after selecting online mode.
  2. The user enters a username, password, and other required details.
  3. The system validates the input (e.g., unique username, password strength).
  4. The system stores the user’s credentials in the database.
  5. The system redirects the user to the login page.
- **Alternative Flows**:
  - A1: If the username is already taken, the system prompts the user to choose another.
  - A2: If the password is weak, the system displays an error and requests a stronger password.
- **Exceptions**:
  - Database connection failure: Display an error message and prompt to retry or switch to offline mode.
- **Priority**: High

## 2. Use Case: User Login

- **Use Case ID**: UC-002
- **Actors**: Registered User
- **Description**: A registered user logs into the Media Player in online mode to access database features.
- **Preconditions**: The user has a registered account and has selected online mode.
- **Postconditions**: The user is logged in and can use the Media Player with database access.
- **Basic Flow**:
  1. The user navigates to the login page after selecting online mode.
  2. The user enters their username and password.
  3. The system validates the credentials against the database.
  4. The system caches the login information for persistent login.
  5. The system grants access to the Media Player’s main interface with database connectivity.
- **Alternative Flows**:
  - A1: If credentials are incorrect, the system displays an error and allows retry or switching to offline mode.
- **Exceptions**:
  - Database connection failure: Display an error message and prompt to retry or switch to offline mode.
- **Priority**: High

## 3. Use Case: Select Online or Offline Mode

- **Use Case ID**: UC-009
- **Actors**: Guest User, Registered User
- **Description**: The user selects between online mode (requiring login for database access) or offline mode (bypassing login for local music playback) at the login screen.
- **Preconditions**: The application is running, and the user is at the login screen.
- **Postconditions**: The user is directed to the appropriate interface based on the selected mode.
- **Basic Flow**:
  1. The system displays the login screen with options for online and offline modes.
  2. The user selects either online mode or offline mode.
  3. If online mode is selected, the system directs the user to the login or registration page.
  4. If offline mode is selected, the system navigates directly to the music playback interface with access limited to local files.
- **Alternative Flows**:
  - A1: The user toggles between modes before confirming, returning to step 2.
- **Exceptions**:
  - None
- **Priority**: High

## 4. Use Case: Play Music from Database

- **Use Case ID**: UC-003
- **Actors**: Logged-in User
- **Description**: The user selects and plays music from a database-stored playlist in online mode.
- **Preconditions**: The user is logged in, in online mode, and the database is accessible.
- **Postconditions**: The selected music is played, and metadata is displayed.
- **Basic Flow**:
  1. The user navigates to the playlist section.
  2. The user selects a playlist from the database.
  3. The system retrieves the playlist’s songs.
  4. The user selects a song to play.
  5. The system plays the song and displays its title, artist, and duration.
- **Alternative Flows**:
  - A1: If the playlist is empty, the system prompts the user to add songs.
- **Exceptions**:
  - Database connection failure: Display an error message and prompt to switch to offline mode.
- **Priority**: High

## 5. Use Case: Play Music from Local File/Folder

- **Use Case ID**: UC-004
- **Actors**: Logged-in User (online mode), Guest User (offline mode)
- **Description**: The user plays a single music file or creates a playlist from a local folder in online or offline mode.
- **Preconditions**: The user is in offline mode or logged in for online mode, and local files are accessible.
- **Postconditions**: The selected music is played, and metadata is displayed.
- **Basic Flow**:
  1. The user selects the option to play a local file or folder.
  2. The user browses and selects a file or folder.
  3. If a folder is selected, the system loads all supported music files as a playlist.
  4. The user selects a song to play.
  5. The system plays the song and displays its title, artist, and duration.
- **Alternative Flows**:
  - A1: If no supported files are found, the system displays an error.
- **Exceptions**:
  - File access failure: Display an error message.
- **Priority**: High

## 6. Use Case: Control Music Playback

- **Use Case ID**: UC-005
- **Actors**: Logged-in User (online mode), Guest User (offline mode)
- **Description**: The user controls music playback using basic controls in online or offline mode.
- **Preconditions**: The user is in offline mode or logged in for online mode, and a song is playing.
- **Postconditions**: The playback state is updated based on user actions.
- **Basic Flow**:
  1. The user interacts with the playback controls (play/pause, next/previous, volume up/down).
  2. The system updates the playback state accordingly.
  3. The system updates the progress bar and time/duration display in real-time.
- **Alternative Flows**:
  - A1: If no next/previous song exists, the system disables the respective button.
- **Exceptions**:
  - Media playback failure: Display an error message.
- **Priority**: High

## 7. Use Case: Search Songs or Playlists

- **Use Case ID**: UC-006
- **Actors**: Logged-in User
- **Description**: The user searches for songs or playlists using dedicated search pages in online mode.
- **Preconditions**: The user is logged in, in online mode, and the database is accessible.
- **Postconditions**: Matching songs or playlists are displayed.
- **Basic Flow**:
  1. The user navigates to the song or playlist search page.
  2. The user enters a search query.
  3. The system queries the database and displays matching results.
  4. The user selects a result to play or view.
- **Alternative Flows**:
  - A1: If no results are found, the system displays a “no results” message.
- **Exceptions**:
  - Database connection failure: Display an error message and prompt to switch to offline mode.
- **Priority**: Medium

## 8. Use Case: Control Media Player via Microcontroller

- **Use Case ID**: UC-007
- **Actors**: Logged-in User (online mode), Guest User (offline mode), External Microcontroller
- **Description**: The user controls the Media Player using an external microcontroller in online or offline mode.
- **Preconditions**: The user is in offline mode or logged in for online mode, and the microcontroller is connected.
- **Postconditions**: The playback state is updated based on microcontroller inputs.
- **Basic Flow**:
  1. The user connects the microcontroller (e.g., via UART, USB, or Bluetooth).
  2. The user presses buttons on the microcontroller (play/pause, next/previous, volume up/down).
  3. The system receives and processes the input.
  4. The system updates the playback state accordingly.
- **Alternative Flows**:
  - A1: If no song is playing, play/pause starts the first song in the playlist.
- **Exceptions**:
  - Connection failure: Display an error message.
- **Priority**: Medium

## 9. Use Case: Song Recommendation via Chatbot (Optional)

- **Use Case ID**: UC-008
- **Actors**: Logged-in User
- **Description**: The user interacts with a chatbot to get song recommendations in online mode.
- **Preconditions**: The user is logged in, in online mode, and the chatbot is enabled.
- **Postconditions**: The user receives a list of recommended songs.
- **Basic Flow**:
  1. The user accesses the chatbot interface.
  2. The user inputs preferences (e.g., genre, mood).
  3. The system processes the input and retrieves matching songs.
  4. The system displays the recommended songs.
  5. The user selects a song to play.
- **Alternative Flows**:
  - A1: If no songs match, the system suggests broadening the criteria.
- **Exceptions**:
  - Processing failure: Display an error message.
- **Priority**: Low
