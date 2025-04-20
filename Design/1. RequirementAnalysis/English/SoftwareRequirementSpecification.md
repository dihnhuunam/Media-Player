# Software Requirement Specification (SRS) - Media Player (English)

## 1. Introduction

### 1.1 Purpose

This Software Requirement Specification (SRS) defines the functional and non-functional requirements for a **Media Player** application designed to play music files with potential extensibility to video files.

### 1.2 Scope

The Media Player will allow users to play music from a database or local files, manage playlists, control playback, and interact with an external microcontroller. It includes user authentication, search functionality, and an optional chatbot for song recommendations. The application will feature a modern UI with smooth animations and persistent login capabilities.

### 1.3 Definitions, Acronyms, and Abbreviations

- **Qt**: Cross-platform framework for UI and application development.
- **QMediaPlayer**: Qt component for media playback.
- **QMediaMetaData**: Qt component for accessing media metadata.
- **SQL**: Structured Query Language for database management.
- **UART**: Universal Asynchronous Receiver/Transmitter for serial communication.
- **UI**: User Interface.

## 2. Overall Description

### 2.1 User Needs

- Users need a reliable media player to play music files from local storage or a database.
- Users require intuitive controls for playback, volume, and track navigation.
- Users expect a secure login system with persistent authentication.
- Users want to search for songs and playlists efficiently.
- Users may want to control the player via an external microcontroller.
- Users desire a visually appealing interface with smooth interactions.

### 2.2 Assumptions and Dependencies

- The application assumes access to a local file system and a stable database connection.
- The external microcontroller supports UART, USB, or Bluetooth communication.
- Qt Framework and SQLite are compatible with the target platform.

## 3. System Features

### 3.1 Play Music from Database

- **Description**: Connect to a SQL database to retrieve and play music files.
- **Input**: Database connection details, user-selected playlist.
- **Output**: Playback of selected music, display of song title and artist.
- **Functionality**: Users can create and manage playlists from database-stored music.

### 3.2 Play Music from Local File/Folder

- **Description**: Play single music files or load folders to create playlists.
- **Input**: File path or folder directory.
- **Output**: Playback of music, display of song metadata.
- **Functionality**: Supports common audio formats (e.g., MP3, WAV).

### 3.3 Basic Music Controls

- **Description**: Provide essential playback controls.
- **Input**: User actions (clicks, key presses, microcontroller inputs).
- **Output**: Volume adjustment, track navigation, play/pause, progress bar updates, time/duration display.
- **Functionality**: Smooth and responsive controls with real-time feedback.

### 3.4 User Accounts

- **Description**: Implement user registration and login.
- **Input**: Username, password, account details.
- **Output**: Secure access to the application, cached login credentials.
- **Functionality**: Persistent login for returning users.

### 3.5 Search Feature

- **Description**: Enable searching for songs and playlists.
- **Input**: Search query.
- **Output**: List of matching songs or playlists.
- **Functionality**: Dedicated pages for song and playlist searches.

### 3.6 External Microcontroller Control

- **Description**: Allow control via an external microcontroller.
- **Input**: Button presses on the microcontroller.
- **Output**: Corresponding media player actions (volume, track, play/pause).
- **Functionality**: Seamless integration with UART/USB/Bluetooth protocols.

### 3.7 Optional Chatbot

- **Description**: Recommend songs based on user preferences.
- **Input**: Genre, mood, or other criteria.
- **Output**: List of suggested songs.
- **Functionality**: Natural language interaction for recommendations.

## 4. Non-Functional Requirements

- **Performance**: The application should load and play media within 2 seconds.
- **Usability**: The UI must be intuitive, with animations enhancing the experience.
- **Security**: User credentials must be encrypted and securely stored.
- **Compatibility**: The application must run on Windows, macOS, and Linux.
- **Reliability**: The application should handle invalid inputs gracefully.

## 5. External Interface Requirements

### 5.1 User Interfaces

- Modern UI with a progress bar, playback controls, and search pages.
- Smooth animations for transitions and interactions.

### 5.2 Hardware Interfaces

- Communication with an external microcontroller via UART, USB, or Bluetooth.

### 5.3 Software Interfaces

- Qt Framework for UI and media handling.
- SQLite for database management.

## 6. Other Requirements

- **Scalability**: The application should support future video playback.
- **Documentation**: Provide user manuals and developer guides.
