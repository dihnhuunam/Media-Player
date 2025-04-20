# **Project: Media Player Design**

## Objective

Design a **Media Player** application that mainly plays **music files**, with the ability to **extend to video files** in the future.

---

## Mandatory Features

### 1. Play Music from Database

- Connect the application to a **Database**.
- **Create playlists** from music files stored in the database.

### 2. Play Music from Local File/Folder

- Play a **single music file** from the local machine.
- **Create playlists** by loading all music files from a **local folder**.

### 3. Basic Music Controls

- **Increase/Decrease volume**.
- **Next/Previous** track.
- **Play/Pause** track.
- **Display current playback time and total duration** of the track (position/duration).
- **Progress bar** for searching.
- **Display song title** and **artist name**.

### 4. User Accounts

- **User registration** (Sign Up).
- **User login** required before using the Media Player.

### 5. Search Feature

- **Search bar for songs** (in a dedicated page).
- **Search bar for playlists** (in a separate dedicated page).

### 6. External Microcontroller Control

- Connect to an **external microcontroller** (e.g., S32K144 board or similar).
- Control the Media Player via microcontroller buttons:
  - **Increase/Decrease volume**.
  - **Next/Previous** track.
  - **Play/Pause** track.

### 7. Optional Feature

- Add a **chatbot** to recommend songs based on **genre**, **mood**, etc.

---

## Non-Functional Requirements

1. **Persistent Login**:
   - After logging into an account on a personal computer, login information should be **cached**.
   - The application should **automatically log in** on the next startup without requiring re-authentication.

2. **UI and Animation**:
   - The application must have an **attractive UI** with **smooth animations**.
   - The user interface should be **visually appealing** and provide a **modern user experience**.

---

## Technology Stack

- **Qt Framework** for UI, media playback, metadata handling.
- **QMediaPlayer** and **QMediaMetaData** for playing and managing media files.
- **SQL Database** (e.g., SQLite) for user and music data management.
- **External Microcontroller Communication** (e.g., via UART, USB, or Bluetooth).
