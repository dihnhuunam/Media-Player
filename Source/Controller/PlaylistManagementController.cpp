#include "PlaylistManagementController.hpp"
#include <QDebug>

PlaylistManagementController::PlaylistManagementController(QObject *parent)
    : ManagementController(parent)
{
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

void PlaylistManagementController::addPlaylist(const QString &name)
{
    if (!name.isEmpty() && !m_playlistManager->playlistNames().contains(name))
    {
        m_playlistManager->addPlaylist(name);
        emit playlistsChanged();
        qDebug() << "Added playlist:" << name;
    }
}

void PlaylistManagementController::removePlaylist(const QString &name)
{
    if (m_playlistManager->playlistNames().contains(name))
    {
        m_playlistManager->removePlaylist(name);
        emit playlistsChanged();
        qDebug() << "Removed playlist:" << name;
    }
}

void PlaylistManagementController::renamePlaylist(const QString &oldName, const QString &newName)
{
    if (m_playlistManager->playlistNames().contains(oldName) && !newName.isEmpty() && oldName != newName && !m_playlistManager->playlistNames().contains(newName))
    {
        m_playlistManager->renamePlaylist(oldName, newName);
        emit playlistsChanged();
        qDebug() << "Renamed playlist from" << oldName << "to" << newName;
    }
}

QStringList PlaylistManagementController::searchPlaylists(const QString &query)
{
    QStringList result;
    QString lowerQuery = query.toLower();
    for (const QString &name : m_playlistManager->playlistNames())
    {
        if (name.toLower().contains(lowerQuery))
        {
            result << name;
        }
    }
    return result;
}

QSharedPointer<Playlist> PlaylistManagementController::getPlaylist(const QString &name) const
{
    return m_playlistManager->playlist(name);
}