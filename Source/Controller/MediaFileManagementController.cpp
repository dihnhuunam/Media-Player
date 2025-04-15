#include <QDebug>
#include <QDir>
#include "MediaFileManagementController.hpp"

MediaFileManagementController::MediaFileManagementController(QSharedPointer<PlaylistManager> manager, QObject *parent)
    : QObject(parent),
      m_playlistManager(manager),
      m_defaultPlaylistName("Default Playlist")
{
    if (!m_playlistManager->playlist(m_defaultPlaylistName))
    {
        m_playlistManager->addPlaylist(m_defaultPlaylistName);
    }
    connect(m_playlistManager.data(), &PlaylistManager::mediaFilesChanged, this, &MediaFileManagementController::mediaFilesChanged);
}

MediaFileManagementController::~MediaFileManagementController()
{
}

QString MediaFileManagementController::defaultPlaylistName() const
{
    return m_defaultPlaylistName;
}

QVariantList MediaFileManagementController::mediaFiles(const QString &playlistName) const
{
    QVariantList results;
    if (auto playlist = m_playlistManager->playlist(playlistName))
    {
        for (int i = 0; i < playlist->mediaCount(); ++i)
        {
            auto media = playlist->mediaFileAt(i);
            QVariantMap item;
            item["title"] = media->title();
            item["artist"] = media->artist();
            item["duration"] = media->duration();
            item["index"] = i;
            results << item;
        }
    }
    return results;
}

QVariantList MediaFileManagementController::searchMediaFiles(const QString &query, const QString &playlistName)
{
    QString targetPlaylist = playlistName.isEmpty() ? m_defaultPlaylistName : playlistName;
    QVariantList results;
    if (auto playlist = m_playlistManager->playlist(targetPlaylist))
    {
        for (int i = 0; i < playlist->mediaCount(); ++i)
        {
            auto media = playlist->mediaFileAt(i);
            if (media->title().contains(query, Qt::CaseInsensitive) || media->artist().contains(query, Qt::CaseInsensitive))
            {
                QVariantMap item;
                item["title"] = media->title();
                item["artist"] = media->artist();
                item["duration"] = media->duration();
                item["index"] = i;
                results << item;
            }
        }
    }
    qDebug() << "Search media in" << targetPlaylist << "with query" << query << ":" << results.size() << "results";
    return results;
}

void MediaFileManagementController::loadFolder(const QString &folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists())
    {
        qDebug() << "Folder does not exist:" << folderPath;
        return;
    }

    QStringList filters = {"*.mp3", "*.wav", "*.m4a"};
    QStringList filePaths;
    for (const QFileInfo &info : dir.entryInfoList(filters, QDir::Files))
    {
        filePaths << info.absoluteFilePath();
    }

    if (!filePaths.isEmpty())
    {
        m_playlistManager->loadMediaFiles(filePaths, m_defaultPlaylistName);
        qDebug() << "Loaded" << filePaths.size() << "files from" << folderPath;
    }
}

void MediaFileManagementController::loadMediaFiles(const QStringList &filePaths)
{
    if (!filePaths.isEmpty())
    {
        m_playlistManager->loadMediaFiles(filePaths, m_defaultPlaylistName);
        qDebug() << "Loaded" << filePaths.size() << "files";
    }
}