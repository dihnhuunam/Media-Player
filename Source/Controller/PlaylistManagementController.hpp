#pragma once
#include <QObject>
#include "ManagementController.hpp"
#include "Playlist.hpp"

class PlaylistManagementController : public ManagementController
{
    Q_OBJECT

public:
    explicit PlaylistManagementController(QObject *parent = nullptr);
    ~PlaylistManagementController();

    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QStringList searchPlaylists(const QString &query);
    Q_INVOKABLE QSharedPointer<Playlist> getPlaylist(const QString &name) const;
};