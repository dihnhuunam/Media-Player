#include "MediaFile.hpp"
#include <QDebug>
#include <QFileInfo>
#include <QMediaMetaData>

MediaFile::MediaFile(const QString &filePath, QObject *parent)
    : QObject(parent),
      m_player(new QMediaPlayer(this)),
      m_filePath(filePath),
      m_title("Unknown Title"),
      m_artists({"Unknown Artist"}),
      m_duration(0)
{
    m_player->setSource(QUrl::fromLocalFile(m_filePath));
    connect(m_player, &QMediaPlayer::metaDataChanged, this, &MediaFile::loadMetaData);
    loadMetaData();
}

MediaFile::~MediaFile()
{
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

qreal MediaFile::position() const
{
    return m_player->position();
}

QMediaPlayer::PlaybackState MediaFile::playbackState() const
{
    return m_player->playbackState();
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

        QVariant artistData = m_player->metaData().stringValue(QMediaMetaData::ContributingArtist);
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
        qDebug() << "Loaded metadata for" << m_filePath << ": title =" << m_title << ", artist =" << artist() << ", duration =" << m_duration;
    }
}