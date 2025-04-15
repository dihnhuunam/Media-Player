#pragma once
#include <QMap>
#include <QObject>
#include "Playlist.hpp"

class PlaylistManager : public QObject
{
    Q_OBJECT

private:
    QMap<QString, QSharedPointer<Playlist>> m_playlists;

public:
    explicit PlaylistManager(QObject *parent = nullptr);
    ~PlaylistManager();

    int playlistCount() const;
    QStringList playlistNames() const;
    QSharedPointer<Playlist> playlist(const QString &playlistName) const;

    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE void loadMediaFiles(const QStringList &files, const QString &playlistName);

signals:
    void playlistsChanged();
    void mediaFilesChanged(const QString &playlistName);
};