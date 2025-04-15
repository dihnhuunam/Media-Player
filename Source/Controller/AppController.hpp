#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QMediaPlayer>
#include "PlaylistManagementController.hpp"
#include "MediaFileManagementController.hpp"
#include "PlaybackController.hpp"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)
    Q_PROPERTY(QString currentPlaylistName READ currentPlaylistName NOTIFY currentPlaylistChanged)
    Q_PROPERTY(int currentMediaIndex READ currentMediaIndex NOTIFY currentMediaIndexChanged)
    Q_PROPERTY(QString currentMediaTitle READ currentMediaTitle NOTIFY currentMediaChanged)
    Q_PROPERTY(QString currentMediaArtist READ currentMediaArtist NOTIFY currentMediaChanged)
    Q_PROPERTY(qint64 currentMediaDuration READ currentMediaDuration NOTIFY currentMediaChanged)
    Q_PROPERTY(QMediaPlayer::PlaybackState playbackState READ playbackState NOTIFY playbackStateChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)

private:
    QSharedPointer<PlaylistManager> m_playlistManager;
    QSharedPointer<PlaylistManagementController> m_playlistController;
    QSharedPointer<MediaFileManagementController> m_mediaController;
    QSharedPointer<PlaybackController> m_playbackController;

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    QStringList playlistNames() const;
    int playlistCount() const;
    QString currentPlaylistName() const;
    int currentMediaIndex() const;
    QString currentMediaTitle() const;
    QString currentMediaArtist() const;
    qint64 currentMediaDuration() const;
    QMediaPlayer::PlaybackState playbackState() const;
    int volume() const;
    void setVolume(int volume);
    qint64 position() const;
    void setPosition(qint64 position);

    Q_INVOKABLE void addPlaylist(const QString &name);
    Q_INVOKABLE void removePlaylist(const QString &name);
    Q_INVOKABLE void renamePlaylist(const QString &oldName, const QString &newName);
    Q_INVOKABLE QStringList searchPlaylists(const QString &query);

    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName);
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName = "");
    Q_INVOKABLE void loadFolder(const QString &folderPath);
    Q_INVOKABLE void loadMediaFiles(const QStringList &filePaths);

    Q_INVOKABLE void selectPlaylist(const QString &name);
    Q_INVOKABLE void selectMedia(int index);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

signals:
    void playlistsChanged();
    void mediaFilesChanged(const QString &playlistName);
    void currentPlaylistChanged();
    void currentMediaIndexChanged();
    void currentMediaChanged();
    void playbackStateChanged();
    void volumeChanged();
    void positionChanged();
};