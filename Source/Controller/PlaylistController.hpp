#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QVariantList>
#include <QMap>
#include "PlaylistManager.hpp"
#include "Playlist.hpp"

class PlaylistController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)

private:
    QSharedPointer<PlaylistManager> m_playlistManager;
    QMap<QString, int> m_pendingMetadataCount; // Theo dõi số lượng media chờ metadata cho mỗi playlist

public:
    explicit PlaylistController(QObject *parent = nullptr);
    ~PlaylistController();

    // Playlist management methods
    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QStringList searchPlaylists(const QString &query);
    Q_INVOKABLE QSharedPointer<Playlist> getPlaylist(const QString &name) const;

    // Media file management methods
    Q_INVOKABLE void loadFolder(const QString &path);
    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName) const;
    Q_INVOKABLE void addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName);
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName);

    // Property accessors
    QStringList playlistNames() const;
    int playlistCount() const;

signals:
    void playlistsChanged();
    void mediaFilesChanged(const QString &playlistName);
    void mediaFilesLoaded(const QString &playlistName); // Tín hiệu khi tất cả metadata đã tải

private slots:
    void onMediaMetaDataChanged(const QString &playlistName, QSharedPointer<MediaFile> mediaFile);
};