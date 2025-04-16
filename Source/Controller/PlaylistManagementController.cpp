#include "PlaylistManagementController.hpp"
#include <QDebug>

PlaylistManagementController::PlaylistManagementController(QObject *parent)
    : ManagementController(parent)
{
}

PlaylistManagementController::~PlaylistManagementController()
{
}

void PlaylistManagementController::addPlaylist(const QString &name)
{
    if (!m_playlistManager || name.isEmpty())
    {
        qDebug() << "Error: Invalid playlist manager or name";
        return;
    }
    m_playlistManager->addPlaylist(name);
    emit playlistsChanged();
    qDebug() << "Added playlist:" << name;
}

void PlaylistManagementController::removePlaylist(const QString &name)
{
    if (!m_playlistManager || name.isEmpty())
    {
        qDebug() << "Error: Invalid playlist manager or name";
        return;
    }
    m_playlistManager->removePlaylist(name);
    emit playlistsChanged();
    qDebug() << "Removed playlist:" << name;
}

void PlaylistManagementController::renamePlaylist(const QString &oldName, const QString &newName)
{
    if (!m_playlistManager || oldName.isEmpty() || newName.isEmpty())
    {
        qDebug() << "Error: Invalid playlist manager or names";
        return;
    }
    m_playlistManager->renamePlaylist(oldName, newName);
    emit playlistsChanged();
    qDebug() << "Renamed playlist from" << oldName << "to" << newName;
}

QStringList PlaylistManagementController::searchPlaylists(const QString &query)
{
    QStringList result;
    if (!m_playlistManager)
    {
        qDebug() << "Error: PlaylistManager is null";
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
    qDebug() << "Search playlists with query:" << query << "Results:" << result.size();
    return result;
}

QSharedPointer<Playlist> PlaylistManagementController::getPlaylist(const QString &name) const
{
    if (!m_playlistManager)
    {
        qDebug() << "Error: PlaylistManager is null";
        return QSharedPointer<Playlist>();
    }
    return m_playlistManager->playlist(name);
}