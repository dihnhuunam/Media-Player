#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Playlist.hpp"
#include "MediaFile.hpp"

class PlaybackController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentPlaylistName READ currentPlaylistName NOTIFY currentPlaylistChanged)
    Q_PROPERTY(int currentMediaIndex READ currentMediaIndex WRITE setCurrentMediaIndex NOTIFY currentMediaIndexChanged)
    Q_PROPERTY(QString currentMediaTitle READ currentMediaTitle NOTIFY currentMediaChanged)
    Q_PROPERTY(QString currentMediaArtist READ currentMediaArtist NOTIFY currentMediaChanged)
    Q_PROPERTY(qint64 currentMediaDuration READ currentMediaDuration NOTIFY currentMediaChanged)
    Q_PROPERTY(QMediaPlayer::PlaybackState playbackState READ playbackState NOTIFY playbackStateChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)

private:
    QSharedPointer<Playlist> m_currentPlaylist;
    int m_currentMediaIndex;
    QSharedPointer<MediaFile> m_currentMedia;
    int m_volume;

public:
    explicit PlaybackController(QObject *parent = nullptr);
    ~PlaybackController();

    QString currentPlaylistName() const;
    void setCurrentPlaylist(QSharedPointer<Playlist> playlist);
    int currentMediaIndex() const;
    void setCurrentMediaIndex(int index);
    QString currentMediaTitle() const;
    QString currentMediaArtist() const;
    qint64 currentMediaDuration() const;
    QMediaPlayer::PlaybackState playbackState() const;
    int volume() const;
    void setVolume(int volume);
    qint64 position() const;
    void setPosition(qint64 position);

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();

signals:
    void currentPlaylistChanged();
    void currentMediaIndexChanged();
    void currentMediaChanged();
    void playbackStateChanged();
    void volumeChanged();
    void positionChanged();

private slots:
    void onMediaPlaybackStateChanged();
    void onMediaPositionChanged(qint64 position);
    void onMediaFinished();
};