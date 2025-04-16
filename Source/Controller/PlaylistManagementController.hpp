#pragma once
#include <QObject>
#include "ManagementController.hpp"

class PlaylistManagementController : public ManagementController
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)

public:
    explicit PlaylistManagementController(QObject *parent = nullptr);
    ~PlaylistManagementController();

    QStringList playlistNames() const;
    int playlistCount() const;

    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QStringList searchPlaylists(const QString &query);
    Q_INVOKABLE QSharedPointer<Playlist> getPlaylist(const QString &name) const;

signals:
    void playlistsChanged();
};