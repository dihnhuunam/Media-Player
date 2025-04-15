#pragma once
#include <QSharedPointer>
#include "PlaylistManager.hpp"

class PlaylistManagementController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)

private:
    QSharedPointer<PlaylistManager> m_playlistManager;

public:
    explicit PlaylistManagementController(QSharedPointer<PlaylistManager> playlistManager, QObject *parent = nullptr);
    ~PlaylistManagementController();

    QStringList playlistNames() const;
    int playlistCount() const;

    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QStringList searchPlaylists(const QString &query);

signals:
    void playlistsChanged();
};