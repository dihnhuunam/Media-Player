#include <QDebug>
#include "PlaylistManager.hpp"

PlaylistManager::PlaylistManager(QObject *parent)
    : QObject(parent),
      m_playlistsCount(0)
{
}

PlaylistManager::~PlaylistManager()
{
}

int PlaylistManager::playlistCount() const
{
    return m_playlists.count();
}

QStringList PlaylistManager::playlistNames() const
{
    QStringList names = m_playlists.keys();
    return names.mid(0, qMin(m_playlistsCount, names.size()));
}

QSharedPointer<Playlist> PlaylistManager::playlist(const QString &playlistName) const
{
    if (m_playlists.contains(playlistName))
    {
        return m_playlists[playlistName];
    }
    return nullptr;
}

int PlaylistManager::playlistsCount() const
{
    return m_playlistsCount;
}

void PlaylistManager::setPlaylistsCount(int count)
{
    if (count >= 0 && count != m_playlistsCount)
    {
        m_playlistsCount = count;
        emit playlistsCountChanged();
        emit playlistsChanged();
    }
}

int PlaylistManager::mediaCount(const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl->mediaCount();
    }
    return 0;
}

QSharedPointer<Playlist> PlaylistManager::mediaFileAt(int index, const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl;
    }
    return nullptr;
}

QString PlaylistManager::mediaNameAt(int index, const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl->mediaNameAt(index);
    }
    return "Unknown Media File";
}

QString PlaylistManager::mediaPathAt(int index, const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl->mediaPathAt(index);
    }
    return "Unknown File Path";
}

QVariantList PlaylistManager::mediaFiles(const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl->mediaFiles();
    }
    return QVariantList();
}

QVariantList PlaylistManager::searchMediaFiles(const QString &query, const QString &playlistName) const
{
    if (auto pl = playlist(playlistName))
    {
        return pl->searchMediaFiles(query);
    }
    return QVariantList();
}

void PlaylistManager::loadMediaFiles(QStringList &files, const QString &playlistName)
{
    if (auto pl = playlist(playlistName))
    {
        pl->addMediaFiles(files);
        emit mediaFilesChanged(playlistName);
    }
}

void PlaylistManager::addPlaylist(const QString &name)
{
    if (!name.isEmpty() && !m_playlists.contains(name))
    {
        m_playlists[name] = QSharedPointer<Playlist>(new Playlist(name));
        if (m_playlistsCount == 0)
        {
            m_playlistsCount = m_playlists.size();
            emit playlistsCountChanged();
        }
        emit playlistsChanged();
    }
}

void PlaylistManager::removePlaylist(const QString &name)
{
    if (m_playlists.contains(name))
    {
        m_playlists.remove(name);
        if (m_playlistsCount > m_playlists.size())
        {
            m_playlistsCount = m_playlists.size();
            emit playlistsCountChanged();
        }
        emit playlistsChanged();
    }
}

void PlaylistManager::renamePlaylist(const QString &oldName, const QString &newName)
{
    if (m_playlists.contains(oldName) && !newName.isEmpty() && !m_playlists.contains(newName))
    {
        auto playlist = m_playlists.take(oldName);
        playlist->setName(newName);
        m_playlists[newName] = playlist;
        emit playlistsChanged();
    }
}

QVariantList PlaylistManager::searchPlaylists(const QString &query)
{
    QVariantList results;
    QString lowerQuery = query.toLower();
    for (auto it = m_playlists.constBegin(); it != m_playlists.constEnd(); ++it)
    {
        if (it.key().toLower().contains(lowerQuery))
        {
            results.append(it.key());
        }
    }
    return results;
}