#include "PlaylistController.hpp"
#include <QDebug>
#include <QDir>
#include <QFileInfo>

PlaylistController::PlaylistController(QObject *parent)
    : QObject(parent), m_playlistManager(new PlaylistManager(this))
{
    qDebug() << "PlaylistController: Created";
}

PlaylistController::~PlaylistController()
{
    qDebug() << "PlaylistController: Destroying";
    // Disconnect all signals from PlaylistManager and its playlists
    if (m_playlistManager)
    {
        disconnect(m_playlistManager, nullptr, this, nullptr);
        for (const QString &playlistName : m_playlistManager->playlistNames())
        {
            Playlist *playlist = m_playlistManager->playlist(playlistName);
            if (playlist)
            {
                for (MediaFile *mediaFile : playlist->mediaFiles())
                {
                    disconnect(mediaFile, nullptr, this, nullptr);
                }
            }
        }
        delete m_playlistManager;
        m_playlistManager = nullptr;
    }
    m_pendingMetadataCount.clear();
    qDebug() << "PlaylistController: Destroyed";
}

QStringList PlaylistController::playlistNames() const
{
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::playlistNames - Error: PlaylistManager is null";
        return QStringList();
    }
    return m_playlistManager->playlistNames();
}

int PlaylistController::playlistCount() const
{
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::playlistCount - Error: PlaylistManager is null";
        return 0;
    }
    return m_playlistManager->playlistCount();
}

void PlaylistController::addPlaylist(const QString &name)
{
    if (!m_playlistManager || name.isEmpty())
    {
        qDebug() << "PlaylistController::addPlaylist - Error: Invalid playlist manager or name";
        return;
    }
    m_playlistManager->addPlaylist(name);
    emit playlistsChanged();
    qDebug() << "PlaylistController::addPlaylist - Added playlist:" << name;
}

void PlaylistController::removePlaylist(const QString &name)
{
    if (!m_playlistManager || name.isEmpty())
    {
        qDebug() << "PlaylistController::removePlaylist - Error: Invalid playlist manager or name";
        return;
    }
    m_playlistManager->removePlaylist(name);
    emit playlistsChanged();
    qDebug() << "PlaylistController::removePlaylist - Removed playlist:" << name;
}

void PlaylistController::renamePlaylist(const QString &oldName, const QString &newName)
{
    if (!m_playlistManager || oldName.isEmpty() || newName.isEmpty())
    {
        qDebug() << "PlaylistController::renamePlaylist - Error: Invalid playlist manager or names";
        return;
    }
    m_playlistManager->renamePlaylist(oldName, newName);
    emit playlistsChanged();
    qDebug() << "PlaylistController::renamePlaylist - Renamed playlist from" << oldName << "to" << newName;
}

QStringList PlaylistController::searchPlaylists(const QString &query)
{
    QStringList result;
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::searchPlaylists - Error: PlaylistManager is null";
        return result;
    }
    QString lowerQuery = query.toLower();
    for (const QString &name : m_playlistManager->playlistNames())
    {
        if (name.toLower().contains(lowerQuery))
        {
            result << name;
        }
    }
    qDebug() << "PlaylistController::searchPlaylists - Search playlists with query:" << query << "Results:" << result.size();
    return result;
}

Playlist *PlaylistController::getPlaylist(const QString &name) const
{
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::getPlaylist - Error: PlaylistManager is null";
        return nullptr;
    }
    return m_playlistManager->playlist(name);
}

void PlaylistController::loadFolder(const QString &path)
{
    if (!m_playlistManager || path.isEmpty())
    {
        qDebug() << "PlaylistController::loadFolder - Error: Invalid playlist manager or path";
        return;
    }

    QDir dir(path);
    if (!dir.exists())
    {
        qDebug() << "PlaylistController::loadFolder - Error: Directory does not exist:" << path;
        return;
    }

    QStringList filters = {"*.mp3", "*.wav", "*.m4a"};
    QStringList files = dir.entryList(filters, QDir::Files);
    QStringList filePaths;

    for (const QString &file : files)
    {
        QString absolutePath = dir.absoluteFilePath(file);
        filePaths << absolutePath;
        qDebug() << "PlaylistController::loadFolder - Files in folder:" << absolutePath;
    }

    if (!filePaths.isEmpty())
    {
        m_pendingMetadataCount["Default"] = filePaths.size();

        m_playlistManager->loadMediaFiles(filePaths, "Default");
        Playlist *playlist = m_playlistManager->playlist("Default");
        if (playlist)
        {
            for (MediaFile *mediaFile : playlist->mediaFiles())
            {
                connect(mediaFile, &MediaFile::metaDataChanged, this,
                        [this, playlistName = QString("Default"), mediaFile]()
                        { onMediaMetaDataChanged(playlistName, mediaFile); });
            }
        }

        emit mediaFilesChanged("Default");
        qDebug() << "PlaylistController::loadFolder - Loaded" << filePaths.size() << "files from folder:" << path << "with absolute paths";
    }
    else
    {
        qDebug() << "PlaylistController::loadFolder - No media files found in folder:" << path;
    }
}

QVariantList PlaylistController::mediaFiles(const QString &playlistName) const
{
    QVariantList result;
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::mediaFiles - Error: PlaylistManager is null";
        return result;
    }

    Playlist *playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        for (MediaFile *mediaFile : playlist->mediaFiles())
        {
            QVariantMap fileData;
            fileData["title"] = mediaFile->title();
            fileData["artist"] = mediaFile->artist();
            fileData["path"] = mediaFile->filePath();
            fileData["duration"] = mediaFile->duration();
            result << fileData;
        }
    }
    qDebug() << "PlaylistController::mediaFiles - Fetching media files for playlist:" << playlistName << "Count:" << result.size();
    return result;
}

void PlaylistController::addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName)
{
    if (!m_playlistManager || filePaths.isEmpty() || playlistName.isEmpty())
    {
        qDebug() << "PlaylistController::addFilesToPlaylist - Error: Invalid playlist manager, file paths, or playlist name";
        return;
    }

    QStringList absoluteFilePaths;
    for (const QString &filePath : filePaths)
    {
        QFileInfo fileInfo(filePath);
        absoluteFilePaths << fileInfo.absoluteFilePath();
    }

    m_pendingMetadataCount[playlistName] = absoluteFilePaths.size();
    m_playlistManager->loadMediaFiles(absoluteFilePaths, playlistName);

    Playlist *playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        for (MediaFile *mediaFile : playlist->mediaFiles())
        {
            connect(mediaFile, &MediaFile::metaDataChanged, this,
                    [this, playlistName, mediaFile]()
                    { onMediaMetaDataChanged(playlistName, mediaFile); });
        }
    }

    emit mediaFilesChanged(playlistName);
    qDebug() << "PlaylistController::addFilesToPlaylist - Added" << absoluteFilePaths.size() << "files to playlist:" << playlistName << "with absolute paths";
}

QVariantList PlaylistController::searchMediaFiles(const QString &query, const QString &playlistName)
{
    QVariantList result;
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::searchMediaFiles - Error: PlaylistManager is null";
        return result;
    }

    Playlist *playlist = m_playlistManager->playlist(playlistName);
    if (playlist)
    {
        QString lowerQuery = query.toLower();
        for (MediaFile *mediaFile : playlist->mediaFiles())
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
    qDebug() << "PlaylistController::searchMediaFiles - Search media files in" << playlistName << "with query:" << query << "Results:" << result.size();
    return result;
}

QVariantList PlaylistController::searchMediaFiles(const QString &query)
{
    QVariantList result;
    if (!m_playlistManager)
    {
        qDebug() << "PlaylistController::searchMediaFiles - Error: PlaylistManager is null";
        return result;
    }

    QString lowerQuery = query.toLower();
    for (const QString &playlistName : m_playlistManager->playlistNames())
    {
        Playlist *playlist = m_playlistManager->playlist(playlistName);
        int index = 0;
        for (MediaFile *mediaFile : playlist->mediaFiles())
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
                fileData["playlistName"] = playlistName;
                fileData["index"] = index;
                result << fileData;
            }
            index++;
        }
    }
    qDebug() << "PlaylistController::searchMediaFiles - Global search with query:" << query << "Results:" << result.size();
    return result;
}

void PlaylistController::onMediaMetaDataChanged(const QString &playlistName, MediaFile *mediaFile)
{
    if (m_pendingMetadataCount.contains(playlistName))
    {
        m_pendingMetadataCount[playlistName]--;
        qDebug() << "PlaylistController::onMediaMetaDataChanged - Metadata loaded for" << mediaFile->filePath()
                 << "in playlist:" << playlistName << ", remaining:" << m_pendingMetadataCount[playlistName];

        if (m_pendingMetadataCount[playlistName] <= 0)
        {
            m_pendingMetadataCount.remove(playlistName);
            emit mediaFilesLoaded(playlistName);
            qDebug() << "PlaylistController::onMediaMetaDataChanged - All metadata loaded for playlist:" << playlistName;
        }
    }
}