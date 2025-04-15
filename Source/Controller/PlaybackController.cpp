#include <QDebug>
#include "PlaybackController.hpp"

PlaybackController::PlaybackController(QObject *parent)
    : QObject(parent),
      m_currentPlaylist(nullptr),
      m_currentMediaIndex(-1),
      m_currentMedia(nullptr),
      m_volume(50)
{
}

PlaybackController::~PlaybackController()
{
    stop();
}

QString PlaybackController::currentPlaylistName() const
{
    return m_currentPlaylist ? m_currentPlaylist->name() : "";
}

void PlaybackController::setCurrentPlaylist(QSharedPointer<Playlist> playlist)
{
    if (m_currentPlaylist != playlist)
    {
        if (m_currentMedia)
        {
            disconnect(m_currentMedia.data(), &MediaFile::playbackStateChanged, this, &PlaybackController::onMediaPlaybackStateChanged);
            disconnect(m_currentMedia.data(), &MediaFile::positionChanged, this, &PlaybackController::onMediaPositionChanged);
            disconnect(m_currentMedia->player(), &QMediaPlayer::mediaStatusChanged, this, &PlaybackController::onMediaFinished);
            m_currentMedia->stop();
            m_currentMedia.reset();
            emit currentMediaChanged();
            emit positionChanged();
        }
        m_currentPlaylist = playlist;
        m_currentMediaIndex = -1;
        emit currentPlaylistChanged();
        emit currentMediaIndexChanged();
    }
}

int PlaybackController::currentMediaIndex() const
{
    return m_currentMediaIndex;
}

void PlaybackController::setCurrentMediaIndex(int index)
{
    if (!m_currentPlaylist || index < 0 || index >= m_currentPlaylist->mediaCount())
    {
        qDebug() << "Invalid media index:" << index;
        return;
    }

    if (m_currentMedia)
    {
        disconnect(m_currentMedia.data(), &MediaFile::playbackStateChanged, this, &PlaybackController::onMediaPlaybackStateChanged);
        disconnect(m_currentMedia.data(), &MediaFile::positionChanged, this, &PlaybackController::onMediaPositionChanged);
        disconnect(m_currentMedia->player(), &QMediaPlayer::mediaStatusChanged, this, &PlaybackController::onMediaFinished);
        m_currentMedia->stop();
    }

    m_currentMediaIndex = index;
    m_currentMedia = m_currentPlaylist->mediaFileAt(index);

    m_currentMedia->player()->audioOutput()->setVolume(m_volume / 100.0);

    connect(m_currentMedia.data(), &MediaFile::playbackStateChanged, this, &PlaybackController::onMediaPlaybackStateChanged);
    connect(m_currentMedia.data(), &MediaFile::positionChanged, this, &PlaybackController::onMediaPositionChanged);
    connect(m_currentMedia->player(), &QMediaPlayer::mediaStatusChanged, this, &PlaybackController::onMediaFinished);

    emit currentMediaIndexChanged();
    emit currentMediaChanged();
    emit playbackStateChanged();
    qDebug() << "Selected media:" << m_currentMedia->title();
}

QString PlaybackController::currentMediaTitle() const
{
    return m_currentMedia ? m_currentMedia->title() : "";
}

QString PlaybackController::currentMediaArtist() const
{
    return m_currentMedia ? m_currentMedia->artist() : "";
}

qint64 PlaybackController::currentMediaDuration() const
{
    return m_currentMedia ? m_currentMedia->duration() : 0;
}

QMediaPlayer::PlaybackState PlaybackController::playbackState() const
{
    return m_currentMedia ? m_currentMedia->playbackState() : QMediaPlayer::StoppedState;
}

int PlaybackController::volume() const
{
    return m_volume;
}

void PlaybackController::setVolume(int volume)
{
    if (volume >= 0 && volume <= 100 && m_volume != volume)
    {
        m_volume = volume;
        if (m_currentMedia)
        {
            m_currentMedia->player()->audioOutput()->setVolume(m_volume / 100.0);
        }
        emit volumeChanged();
        qDebug() << "Volume set to:" << volume;
    }
}

qint64 PlaybackController::position() const
{
    return m_currentMedia ? m_currentMedia->position() : 0;
}

void PlaybackController::setPosition(qint64 position)
{
    if (m_currentMedia && position >= 0 && position <= m_currentMedia->duration())
    {
        m_currentMedia->player()->setPosition(position);
        qDebug() << "Position set to:" << position;
    }
}

void PlaybackController::play()
{
    if (m_currentMedia)
    {
        m_currentMedia->play();
    }
}

void PlaybackController::pause()
{
    if (m_currentMedia)
    {
        m_currentMedia->pause();
    }
}

void PlaybackController::stop()
{
    if (m_currentMedia)
    {
        m_currentMedia->stop();
    }
}

void PlaybackController::next()
{
    if (m_currentPlaylist && m_currentMediaIndex + 1 < m_currentPlaylist->mediaCount())
    {
        setCurrentMediaIndex(m_currentMediaIndex + 1);
        play();
        qDebug() << "Next media";
    }
}

void PlaybackController::previous()
{
    if (m_currentPlaylist && m_currentMediaIndex - 1 >= 0)
    {
        setCurrentMediaIndex(m_currentMediaIndex - 1);
        play();
        qDebug() << "Previous media";
    }
}

void PlaybackController::onMediaPlaybackStateChanged()
{
    emit playbackStateChanged();
}

void PlaybackController::onMediaPositionChanged(qint64 position)
{
    emit positionChanged();
}

void PlaybackController::onMediaFinished()
{
    if (m_currentMedia && m_currentMedia->player()->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        qDebug() << "Media finished:" << m_currentMedia->title();
        next();
    }
}