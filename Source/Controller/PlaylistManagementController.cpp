#include "PlaylistManagementController.hpp"

PlaylistManagementController::PlaylistManagementController(QSharedPointer<PlaylistManager> playlistManager, QObject *parent)
    : QObject(parent),
      m_playlistManager(playlistManager)
{
    connect(m_playlistManager.data(), &PlaylistManager::playlistsChanged, this, &PlaylistManagementController::playlistsChanged);
}

PlaylistManagementController::~PlaylistManagementController()
{
}

QStringList PlaylistManagementController::playlistNames() const
{
    return m_playlistManager->playlistNames();
}

int PlaylistManagementController::playlistCount() const
{
    return m_playlistManager->playlistCount();
}

Q_INVOKABLE void PlaylistManagementController::addPlaylist(const QString &name)
{
    m_playlistManager->addPlaylist(name);
}

Q_INVOKABLE void PlaylistManagementController::removePlaylist(const QString &name)
{
    m_playlistManager->removePlaylist(name);
}

Q_INVOKABLE void PlaylistManagementController::renamePlaylist(const QString &oldName, const QString &newName)
{
    m_playlistManager->renamePlaylist(oldName, newName);
}

Q_INVOKABLE QStringList PlaylistManagementController::searchPlaylists(const QString &query)
{
    QStringList results;
    for (auto &name : m_playlistManager->playlistNames())
    {
        if (name.contains(query, Qt::CaseSensitive))
        {
            results.append(name);
        }
    }
    return results;
}
