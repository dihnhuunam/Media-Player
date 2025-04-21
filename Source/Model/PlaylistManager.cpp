#include "PlaylistManager.hpp"
#include <QDebug>

PlaylistManager::PlaylistManager(QObject *parent)
    : QObject(parent)
{
}

PlaylistManager::~PlaylistManager()
{
    for (Playlist *playlist : m_playlists)
    {
        delete playlist;
    }
    m_playlists.clear();
}

int PlaylistManager::playlistCount() const
{
    return m_playlists.size();
}

QStringList PlaylistManager::playlistNames() const
{
    return m_playlists.keys();
}

Playlist *PlaylistManager::playlist(const QString &playlistName) const
{
    return m_playlists.value(playlistName, nullptr);
}

void PlaylistManager::addPlaylist(const QString &name)
{
    if (!name.trimmed().isEmpty() && !m_playlists.contains(name))
    {
        m_playlists[name] = new Playlist(name, this);
        emit playlistsChanged();
        qDebug() << "PlaylistManager::addPlaylist - Added playlist:" << name;
    }
}

void PlaylistManager::removePlaylist(const QString &name)
{
    if (m_playlists.contains(name))
    {
        delete m_playlists[name];
        m_playlists.remove(name);
        emit playlistsChanged();
        qDebug() << "PlaylistManager::removePlaylist - Removed playlist:" << name;
    }
}

void PlaylistManager::renamePlaylist(const QString &oldName, const QString &newName)
{
    if (!newName.trimmed().isEmpty() && m_playlists.contains(oldName) && !m_playlists.contains(newName))
    {
        Playlist *playlist = m_playlists.take(oldName);
        playlist->setName(newName);
        m_playlists[newName] = playlist;
        emit playlistsChanged();
        qDebug() << "PlaylistManager::renamePlaylist - Renamed playlist from" << oldName << "to" << newName;
    }
}

void PlaylistManager::loadMediaFiles(const QStringList &files, const QString &playlistName)
{
    Playlist *playlist = m_playlists.value(playlistName, nullptr);
    if (!playlist)
    {
        addPlaylist(playlistName);
        playlist = m_playlists.value(playlistName, nullptr);
    }
    if (playlist)
    {
        playlist->addMediaFiles(files);
        emit mediaFilesChanged(playlistName);
    }
}