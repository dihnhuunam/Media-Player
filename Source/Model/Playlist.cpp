#include "Playlist.hpp"
#include <QFileInfo>

Playlist::Playlist(const QString &name, QObject *parent)
    : QObject(parent), m_name(name)
{
}

Playlist::~Playlist()
{
    for (MediaFile *media : m_mediaFiles)
    {
        delete media;
    }
    m_mediaFiles.clear();
}

QString Playlist::name() const
{
    return m_name;
}

void Playlist::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged();
    }
}

int Playlist::mediaCount() const
{
    return m_mediaFiles.size();
}

MediaFile *Playlist::mediaFileAt(int index) const
{
    if (index >= 0 && index < m_mediaFiles.size())
    {
        return m_mediaFiles[index];
    }
    return nullptr;
}

QList<MediaFile *> Playlist::mediaFiles() const
{
    return m_mediaFiles;
}

void Playlist::addMediaFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.exists())
    {
        MediaFile *media = new MediaFile(filePath, this);
        m_mediaFiles.append(media);
        emit mediaFilesChanged();
    }
}

void Playlist::addMediaFiles(const QStringList &filePaths)
{
    for (const QString &filePath : filePaths)
    {
        addMediaFile(filePath);
    }
}

void Playlist::removeMediaFile(int index)
{
    if (index >= 0 && index < m_mediaFiles.size())
    {
        delete m_mediaFiles[index];
        m_mediaFiles.removeAt(index);
        emit mediaFilesChanged();
    }
}