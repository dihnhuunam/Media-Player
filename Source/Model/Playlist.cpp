#include "Playlist.hpp"
#include <QDebug>

Playlist::Playlist(const QString &name, QObject *parent)
    : QObject(parent),
      m_name(name)
{
}

Playlist::~Playlist()
{
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

QSharedPointer<MediaFile> Playlist::mediaFileAt(int index) const
{
    if (index >= 0 && index < m_mediaFiles.size())
    {
        return m_mediaFiles[index];
    }
    return nullptr;
}

void Playlist::addMediaFile(const QString &filePath)
{
    if (!filePath.isEmpty())
    {
        auto media = QSharedPointer<MediaFile>::create(filePath, this);
        m_mediaFiles.append(media);
        emit mediaFilesChanged();
        qDebug() << "Added media to" << m_name << ":" << filePath;
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
        m_mediaFiles.removeAt(index);
        emit mediaFilesChanged();
        qDebug() << "Removed media at index" << index << "from" << m_name;
    }
}