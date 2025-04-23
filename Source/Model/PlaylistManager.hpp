#pragma once
#include <QMap>
#include <QObject>
#include "Playlist.hpp"

class PlaylistManager : public QObject
{
    Q_OBJECT

private:
    QMap<QString, Playlist *> m_playlists;

public:
    explicit PlaylistManager(QObject *parent = nullptr);
    ~PlaylistManager();

    int playlistCount() const;
    QStringList playlistNames() const;
    Playlist *playlist(const QString &playlistName) const;

    void addPlaylist(const QString &name);
    void removePlaylist(const QString &name);
    void renamePlaylist(const QString &oldName, const QString &newName);
    void loadMediaFiles(const QStringList &files, const QString &playlistName);

signals:
    void playlistsChanged();
    void mediaFilesChanged(const QString &playlistName);
};