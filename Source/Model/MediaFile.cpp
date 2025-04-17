#include "MediaFile.hpp"
#include <QDebug>
#include <QFileInfo>
#include <QMediaMetaData>

MediaFile::MediaFile(const QString &filePath, QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_audioOutput(new QAudioOutput(this)),
      m_filePath(filePath),
      m_title("Unknown Title"),
      m_artists({"Unknown Artist"}),
      m_duration(0)
{
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(QUrl::fromLocalFile(m_filePath));
    connect(m_player, &QMediaPlayer::metaDataChanged, this, &MediaFile::loadMetaData);
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &MediaFile::onPlaybackStateChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MediaFile::onPositionChanged);
    loadMetaData();
}

MediaFile::~MediaFile()
{
    m_player->stop();
}

QMediaPlayer *MediaFile::player() const
{
    return m_player;
}

QString MediaFile::filePath() const
{
    return m_filePath;
}

QString MediaFile::title() const
{
    return m_title;
}

QString MediaFile::artist() const
{
    return m_artists.isEmpty() ? "Unknown Artist" : m_artists.join(", ");
}

QStringList MediaFile::artists() const
{
    return m_artists;
}

qint64 MediaFile::duration() const
{
    return m_duration;
}

qint64 MediaFile::position() const
{
    return m_player->position();
}

QMediaPlayer::PlaybackState MediaFile::playbackState() const
{
    return m_player->playbackState();
}

void MediaFile::play()
{
    if (m_player->playbackState() != QMediaPlayer::PlayingState)
    {
        if (m_player->source().isEmpty())
        {
            m_player->setSource(QUrl::fromLocalFile(m_filePath));
        }
        m_player->play();
        qDebug() << "MediaFile::play - Playing:" << m_title;
    }
}

void MediaFile::pause()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState)
    {
        m_player->pause();
        qDebug() << "MediaFile::pause - Paused:" << m_title;
    }
}

void MediaFile::stop()
{
    if (m_player->playbackState() != QMediaPlayer::StoppedState)
    {
        m_player->stop();
        qDebug() << "MediaFile::stop - Stopped:" << m_title;
    }
}

void MediaFile::loadMetaData()
{
    if (!m_player->metaData().isEmpty())
    {
        m_title = m_player->metaData().stringValue(QMediaMetaData::Title);
        if (m_title.isEmpty())
        {
            m_title = QFileInfo(m_filePath).baseName();
        }

        QVariant artistData = m_player->metaData().value(QMediaMetaData::ContributingArtist);
        m_artists = artistData.toStringList();
        if (m_artists.isEmpty())
        {
            m_artists << m_player->metaData().stringValue(QMediaMetaData::AlbumArtist);
        }
        if (m_artists.isEmpty() || m_artists.first().isEmpty())
        {
            m_artists = {"Unknown Artist"};
        }

        m_duration = m_player->duration();
        emit metaDataChanged();
        qDebug() << "MediaFile::loadMetaData - Loaded metadata for" << m_filePath << ": title =" << m_title << ", artist =" << artist() << ", duration =" << m_duration;
    }
}

void MediaFile::onPlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
    emit playbackStateChanged();
    qDebug() << "MediaFile::onPlaybackStateChanged - Playback state changed for" << m_title << ":" << state;
}

void MediaFile::onPositionChanged(qint64 position)
{
    emit positionChanged(position);
}