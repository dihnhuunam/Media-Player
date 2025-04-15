#pragma once
#include <QMap>
#include "Playlist.hpp"

class PlaylistManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistsCount READ playlistsCount WRITE setPlaylistsCount NOTIFY playlistsCountChanged)

private:
    QMap<QString, QSharedPointer<Playlist>> m_playlists;
    int m_playlistsCount;

public:
    explicit PlaylistManager(QObject *parent = nullptr);
    ~PlaylistManager();

    /* Handle Playlists */
    int playlistCount() const;
    QStringList playlistNames() const;
    QSharedPointer<Playlist> playlist(const QString &playlistName) const;

    int playlistsCount() const;
    void setPlaylistsCount(int count);

    Q_INVOKABLE int mediaCount(const QString &playlistName) const;
    Q_INVOKABLE QSharedPointer<Playlist> mediaFileAt(int index, const QString &playlistName) const;
    Q_INVOKABLE QString mediaNameAt(int index, const QString &playlistName) const;
    Q_INVOKABLE QString mediaPathAt(int index, const QString &playlistName) const;
    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName) const;
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName) const;
    Q_INVOKABLE void loadMediaFiles(QStringList &files, const QString &playlistName);

    /* Handle Media Files in Playlist */
    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QVariantList searchPlaylists(const QString &query);

signals:
    void playlistNamesChanged();
    void playlistsChanged();
    void playlistsCountChanged();
    void mediaFilesChanged(const QString &playlistName);
};