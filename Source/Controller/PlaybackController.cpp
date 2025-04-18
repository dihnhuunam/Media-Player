#include <QDebug>
#include <QRandomGenerator>
#include "PlaybackController.hpp"

PlaybackController::PlaybackController(QObject *parent)
    : QObject(parent),
      m_currentPlaylist(nullptr),
      m_currentMediaIndex(-1),
      m_currentMedia(nullptr),
      m_volume(50),
      m_shuffle(false),
      m_repeatMode(0),
      m_muted(false),
      m_currentShuffleIndex(-1)
{
    qDebug() << "PlaybackController: Created";
}

PlaybackController::~PlaybackController()
{
    qDebug() << "PlaybackController: Destroying";
    stop();
    if (m_currentMedia)
    {
        disconnect(m_currentMedia.data(), nullptr, this, nullptr);
        m_currentMedia->stop();
        m_currentMedia.reset();
    }
    m_currentPlaylist.reset();
    qDebug() << "PlaybackController: Destroyed";
}

QString PlaybackController::currentPlaylistName() const
{
    return m_currentPlaylist ? m_currentPlaylist->name() : "";
}

void PlaybackController::setCurrentPlaylist(QSharedPointer<Playlist> playlist)
{
    if (m_currentPlaylist != playlist)
    {
        qDebug() << "PlaybackController: Setting new playlist";
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
        m_shuffleOrder.clear();
        m_currentShuffleIndex = -1;
        if (m_shuffle && playlist && playlist->mediaCount() > 0)
        {
            generateShuffleOrder();
        }
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
        qDebug() << "PlaybackController: Invalid media index:" << index;
        return;
    }

    if (m_currentMedia)
    {
        disconnect(m_currentMedia.data(), &MediaFile::playbackStateChanged, this, &PlaybackController::onMediaPlaybackStateChanged);
        disconnect(m_currentMedia.data(), &MediaFile::positionChanged, this, &PlaybackController::onMediaPositionChanged);
        disconnect(m_currentMedia->player(), &QMediaPlayer::mediaStatusChanged, this, &PlaybackController::onMediaFinished);
        m_currentMedia->stop();
        m_currentMedia.reset();
    }

    m_currentMediaIndex = index;
    m_currentMedia = m_currentPlaylist->mediaFileAt(index);

    if (m_currentMedia)
    {
        m_currentMedia->player()->audioOutput()->setVolume(m_muted ? 0 : m_volume / 100.0);

        connect(m_currentMedia.data(), &MediaFile::playbackStateChanged, this, &PlaybackController::onMediaPlaybackStateChanged);
        connect(m_currentMedia.data(), &MediaFile::positionChanged, this, &PlaybackController::onMediaPositionChanged);
        connect(m_currentMedia->player(), &QMediaPlayer::mediaStatusChanged, this, &PlaybackController::onMediaFinished);
    }

    emit currentMediaIndexChanged();
    emit currentMediaChanged();
    emit playbackStateChanged();
    qDebug() << "PlaybackController: Selected media:" << (m_currentMedia ? m_currentMedia->title() : "none");
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
        if (m_currentMedia && !m_muted)
        {
            m_currentMedia->player()->audioOutput()->setVolume(m_volume / 100.0);
        }
        emit volumeChanged();
        qDebug() << "PlaybackController: Volume set to:" << volume;
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
        qDebug() << "PlaybackController: Position set to:" << position;
    }
}

bool PlaybackController::shuffle() const
{
    return m_shuffle;
}

void PlaybackController::setShuffle(bool enabled)
{
    if (m_shuffle != enabled)
    {
        m_shuffle = enabled;
        m_shuffleOrder.clear();
        m_currentShuffleIndex = -1;
        if (m_shuffle && m_currentPlaylist && m_currentPlaylist->mediaCount() > 0)
        {
            generateShuffleOrder();
            m_currentShuffleIndex = m_shuffleOrder.indexOf(m_currentMediaIndex);
        }
        emit shuffleChanged();
        qDebug() << "PlaybackController: Shuffle set to:" << enabled;
    }
}

int PlaybackController::repeatMode() const
{
    return m_repeatMode;
}

void PlaybackController::setRepeatMode(int mode)
{
    if (mode >= 0 && mode <= 2 && m_repeatMode != mode)
    {
        m_repeatMode = mode;
        emit repeatModeChanged();
        qDebug() << "PlaybackController: Repeat mode set to:" << mode;
    }
}

bool PlaybackController::muted() const
{
    return m_muted;
}

void PlaybackController::setMuted(bool muted)
{
    if (m_muted != muted)
    {
        m_muted = muted;
        if (m_currentMedia)
        {
            m_currentMedia->player()->audioOutput()->setVolume(m_muted ? 0 : m_volume / 100.0);
        }
        emit mutedChanged();
        qDebug() << "PlaybackController: Muted set to:" << muted;
    }
}

void PlaybackController::play()
{
    if (m_currentMedia)
    {
        m_currentMedia->play();
        qDebug() << "PlaybackController: Playing media";
    }
}

void PlaybackController::pause()
{
    if (m_currentMedia)
    {
        m_currentMedia->pause();
        qDebug() << "PlaybackController: Pausing media";
    }
}

void PlaybackController::stop()
{
    if (m_currentMedia)
    {
        m_currentMedia->stop();
        qDebug() << "PlaybackController: Stopping media";
    }
}

void PlaybackController::next()
{
    if (!m_currentPlaylist || m_currentPlaylist->mediaCount() == 0)
        return;

    if (m_repeatMode == 1)
    {
        play();
        return;
    }

    int nextIndex = -1;
    if (m_shuffle)
    {
        m_currentShuffleIndex = (m_currentShuffleIndex + 1) % m_shuffleOrder.size();
        nextIndex = m_shuffleOrder[m_currentShuffleIndex];
    }
    else
    {
        nextIndex = m_currentMediaIndex + 1;
        if (nextIndex >= m_currentPlaylist->mediaCount())
        {
            if (m_repeatMode == 2)
                nextIndex = 0;
            else
                return;
        }
    }

    if (nextIndex >= 0 && nextIndex < m_currentPlaylist->mediaCount())
    {
        setCurrentMediaIndex(nextIndex);
        play();
        qDebug() << "PlaybackController: Next media";
    }
}

void PlaybackController::previous()
{
    if (!m_currentPlaylist || m_currentPlaylist->mediaCount() == 0)
        return;

    if (m_repeatMode == 1)
    {
        play();
        return;
    }

    int prevIndex = -1;
    if (m_shuffle)
    {
        m_currentShuffleIndex = (m_currentShuffleIndex - 1 + m_shuffleOrder.size()) % m_shuffleOrder.size();
        prevIndex = m_shuffleOrder[m_currentShuffleIndex];
    }
    else
    {
        prevIndex = m_currentMediaIndex - 1;
        if (prevIndex < 0)
        {
            if (m_repeatMode == 2)
                prevIndex = m_currentPlaylist->mediaCount() - 1;
            else
                return;
        }
    }

    if (prevIndex >= 0 && prevIndex < m_currentPlaylist->mediaCount())
    {
        setCurrentMediaIndex(prevIndex);
        play();
        qDebug() << "PlaybackController: Previous media";
    }
}

void PlaybackController::playMedia(QSharedPointer<Playlist> playlist, int index)
{
    if (!playlist || index < 0 || index >= playlist->mediaCount())
    {
        qDebug() << "PlaybackController: Invalid playlist or index:" << index;
        return;
    }

    setCurrentPlaylist(playlist);
    setCurrentMediaIndex(index);
    play();
    qDebug() << "PlaybackController: Playing media from playlist:" << playlist->name() << "index:" << index;
}

void PlaybackController::onMediaPlaybackStateChanged()
{
    emit playbackStateChanged();
    qDebug() << "PlaybackController: Playback state changed";
}

void PlaybackController::onMediaPositionChanged(qint64 position)
{
    emit positionChanged();
}

void PlaybackController::onMediaFinished()
{
    if (m_currentMedia && m_currentMedia->player()->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        qDebug() << "PlaybackController: Media finished:" << m_currentMedia->title();
        next();
    }
}

void PlaybackController::generateShuffleOrder()
{
    m_shuffleOrder.clear();
    for (int i = 0; i < m_currentPlaylist->mediaCount(); ++i)
        m_shuffleOrder << i;

    // Fisher-Yates shuffle
    for (int i = m_shuffleOrder.size() - 1; i > 0; --i)
    {
        int j = QRandomGenerator::global()->bounded(i + 1);
        m_shuffleOrder.swapItemsAt(i, j);
    }
    qDebug() << "PlaybackController: Generated shuffle order:" << m_shuffleOrder;
}