#include "MediaFileManagementController.hpp"
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

QVariantList MediaFileManagementController::mediaFiles(const QString &playlistName) const
{
    QVariantList result;
    auto playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        for (const auto &media : playlist->mediaFiles())
        {
            QVariantMap map;
            map["title"] = media->title();
            map["artist"] = media->artist();
            map["filePath"] = media->filePath();
            result << map;
        }
    }
    return result;
}

QVariantList MediaFileManagementController::searchMediaFiles(const QString &query, const QString &playlistName) const
{
    QVariantList result;
    auto playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        QString lowerQuery = query.toLower();
        for (const auto &media : playlist->mediaFiles())
        {
            if (media->title().toLower().contains(lowerQuery) || media->artist().toLower().contains(lowerQuery))
            {
                QVariantMap map;
                map["title"] = media->title();
                map["artist"] = media->artist();
                map["filePath"] = media->filePath();
                result << map;
            }
        }
    }
    return result;
}

void MediaFileManagementController::loadMediaFiles(const QStringList &filePaths)
{
    QStringList validFormats = {".mp3", ".wav", ".m4a"};
    for (const QString &filePath : filePaths)
    {
        QFileInfo fileInfo(filePath);
        if (validFormats.contains(fileInfo.suffix().toLower()))
        {
            QString playlistName = m_playlistManager->playlistNames().isEmpty() ? "Default" : m_playlistManager->playlistNames().first();
            if (!m_playlistManager->playlistNames().contains(playlistName))
            {
                m_playlistManager->addPlaylist(playlistName);
            }
            auto playlist = m_playlistManager->playlist(playlistName);
            if (playlist)
            {
                playlist->addMediaFile(filePath);
                qDebug() << "Loaded media:" << fileInfo.fileName() << "to playlist:" << playlistName;
            }
        }
    }
}

void MediaFileManagementController::loadFolder(const QString &folderPath)
{
    QDir dir(folderPath);
    dir.setNameFilters({"*.mp3", "*.wav", "*.m4a"});
    QStringList files;
    for (const QFileInfo &fileInfo : dir.entryInfoList(QDir::Files))
    {
        files << fileInfo.absoluteFilePath();
    }
    if (!files.isEmpty())
    {
        loadMediaFiles(files);
        qDebug() << "Loaded" << files.size() << "files from folder:" << folderPath;
    }
}

void MediaFileManagementController::addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName)
{
    if (playlistName.isEmpty())
    {
        qDebug() << "Error: Playlist name is empty";
        return;
    }

    auto playlist = m_playlistManager->playlist(playlistName);
    if (!playlist)
    {
        qDebug() << "Error: Playlist" << playlistName << "does not exist";
        return;
    }

    QStringList validFormats = {".mp3", ".wav", ".m4a"};
    QStringList addedFiles;
    for (const QString &filePath : filePaths)
    {
        QFileInfo fileInfo(filePath);
        if (validFormats.contains(fileInfo.suffix().toLower()))
        {
            playlist->addMediaFile(filePath);
            addedFiles << fileInfo.fileName();
        }
    }

    if (!addedFiles.isEmpty())
    {
        qDebug() << "Added" << addedFiles.size() << "files to playlist:" << playlistName << ":" << addedFiles;
    }
    else
    {
        qDebug() << "No valid media files added to playlist:" << playlistName;
    }
}