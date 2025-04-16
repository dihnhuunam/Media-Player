#include "MediaFileManagementController.hpp"
#include "MediaFile.hpp"
#include "Playlist.hpp"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

MediaFileManagementController::MediaFileManagementController(QObject *parent)
    : ManagementController(parent)
{
}

MediaFileManagementController::~MediaFileManagementController()
{
}

void MediaFileManagementController::loadFolder(const QString &path)
{
    if (!m_playlistManager || path.isEmpty())
    {
        qDebug() << "Error: Invalid playlist manager or path";
        return;
    }

    QDir dir(path);
    QStringList filters = {"*.mp3", "*.wav", "*.m4a"};
    QStringList files = dir.entryList(filters, QDir::Files);
    QStringList filePaths;

    for (const QString &file : files)
    {
        filePaths << dir.filePath(file);
    }

    if (!filePaths.isEmpty())
    {
        m_playlistManager->loadMediaFiles(filePaths, "Default");
        emit mediaFilesChanged("Default");
        qDebug() << "Loaded" << filePaths.size() << "files from folder:" << path;
    }
}

QVariantList MediaFileManagementController::mediaFiles(const QString &playlistName) const
{
    QVariantList result;
    if (!m_playlistManager)
    {
        qDebug() << "Error: PlaylistManager is null";
        return result;
    }

    auto playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        for (const auto &mediaFile : playlist->mediaFiles())
        {
            QVariantMap fileData;
            fileData["title"] = mediaFile->title();
            fileData["artist"] = mediaFile->artist();
            fileData["path"] = mediaFile->filePath();
            fileData["duration"] = mediaFile->duration();
            result << fileData;
        }
    }
    qDebug() << "Fetching media files for playlist:" << playlistName << "Count:" << result.size();
    return result;
}

void MediaFileManagementController::addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName)
{
    if (!m_playlistManager || filePaths.isEmpty() || playlistName.isEmpty())
    {
        qDebug() << "Error: Invalid playlist manager, file paths, or playlist name";
        return;
    }

    m_playlistManager->loadMediaFiles(filePaths, playlistName);
    emit mediaFilesChanged(playlistName);
    qDebug() << "Added" << filePaths.size() << "files to playlist:" << playlistName;
}

QVariantList MediaFileManagementController::searchMediaFiles(const QString &query, const QString &playlistName)
{
    QVariantList result;
    if (!m_playlistManager)
    {
        qDebug() << "Error: PlaylistManager is null";
        return result;
    }

    auto playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        QString lowerQuery = query.toLower();
        for (const auto &mediaFile : playlist->mediaFiles())
        {
            QString title = mediaFile->title().toLower();
            QString artist = mediaFile->artist().toLower();
            if (title.contains(lowerQuery) || artist.contains(lowerQuery))
            {
                QVariantMap fileData;
                fileData["title"] = mediaFile->title();
                fileData["artist"] = mediaFile->artist();
                fileData["path"] = mediaFile->filePath();
                fileData["duration"] = mediaFile->duration();
                result << fileData;
            }
        }
    }
    qDebug() << "Search media files in" << playlistName << "with query:" << query << "Results:" << result.size();
    return result;
}