#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QTimer>
#include "MediaFile.hpp"

MediaFile::MediaFile(const QString &filePath, QObject *parent)
    : QObject(parent),
      m_filePath(filePath),
      m_title("Unknown Title"),
      m_author("Unknown Author"),
      m_duration(0)
{
    QFile file(filePath);
    if (!file.exists())
    {
        qDebug() << "Error: File does not exist" << filePath;
        return;
    }

    QMediaPlayer *player = new QMediaPlayer(this);
    player->setSource(QUrl(filePath));

    connect(player, &QMediaPlayer::mediaStatusChanged, this, [=]()
            {
        QMediaMetaData metaData = player->metaData();
        QString newTitle = metaData.stringValue(QMediaMetaData::Title);
        QString newAuthor = metaData.stringValue(QMediaMetaData::ContributingArtist); 
                
        if(!newTitle.isEmpty())
        {
            m_title = newTitle;
        }
        if(!newAuthor.isEmpty())
        {
            m_author = newAuthor;
        } });

    QTimer::singleShot(500, this, [=]()
                       {
        QMediaMetaData metaData = player->metaData();
        QString newTitle = metaData.stringValue(QMediaMetaData::Title);
        QString newAuthor = metaData.stringValue(QMediaMetaData::ContributingArtist); 
                
        if(!newTitle.isEmpty())
        {
            m_title = newTitle;
        }
        if(!newAuthor.isEmpty())
        {
            m_author = newAuthor;
        } 
        if(player->duration() > 0)
        {
            m_duration = player->duration();
        } });
}

MediaFile::~MediaFile()
{
}

QString MediaFile::filePath() const
{
    return m_filePath;
}

QString MediaFile::title() const
{
    return m_title;
}

QString MediaFile::author() const
{
    return m_author;
}

qint64 MediaFile::duration() const
{
    return m_duration;
}
