#include <QFileInfo>
#include "Playlist.hpp"

Playlist::Playlist(const QString &name, QObject *parent)
    : m_name(name),
      QObject(parent)
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
    if (m_name != name && !name.isEmpty())
    {
        m_name = name;
        emit nameChanged();
    }
}

int Playlist::mediaCount() const
{
    return m_mediaFiles.count();
}

QSharedPointer<MediaFile> Playlist::mediaFileAt(int index) const
{
    if (index >= 0 && index < m_mediaFiles.count())
    {
        return m_mediaFiles[index];
    }
    return nullptr;
}

QString Playlist::mediaNameAt(int index) const
{
    if (this->mediaFileAt(index) != nullptr)
    {
        return this->mediaFileAt(index)->title() + " - " + this->mediaFileAt(index)->artist();
    }
    return "Unkown Media File";
}

QString Playlist::mediaPathAt(int index) const
{
    if (this->mediaFileAt(index) != nullptr)
        return this->mediaFileAt(index)->filePath();
    return "Unkown File Path";
}

QVariantList Playlist::mediaFiles() const
{
    QVariantList files;
    for (const auto &file : m_mediaFiles)
    {
        QVariantMap fileData;
        fileData["title"] = file->title();
        fileData["artist"] = file->artist();
        fileData["path"] = file->filePath();
        fileData["duration"] = file->duration();
        files.append(fileData);
    }
    return files;
}

void Playlist::addMediaFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QSharedPointer<MediaFile> newMediaFile = QSharedPointer<MediaFile>::create(filePath);
    if (fileInfo.exists())
    {
        m_mediaFiles.append(newMediaFile);
        qDebug() << newMediaFile->title() + " - " << newMediaFile->artist() + " - " << newMediaFile->filePath();
        emit mediaFilesChanged();
    }
}

void Playlist::addMediaFiles(const QStringList &filePaths)
{
    for (const auto &filePath : filePaths)
    {
        addMediaFile(filePath);
    }
}

void Playlist::removeMediaFile(int index)
{
    if (index >= 0 && index < m_mediaFiles.count())
    {
        m_mediaFiles.removeAt(index);
        emit mediaFilesChanged();
    }
}

QVariantList Playlist::searchMediaFiles(const QString &query)
{
    QVariantList results;
    QString lowerQuery = query.toLower();
    for (const auto &file : m_mediaFiles)
    {
        if (file->title().toLower().contains(lowerQuery) ||
            file->artist().toLower().contains(lowerQuery))
        {
            QVariantMap fileData;
            fileData["title"] = file->title();
            fileData["artist"] = file->artist();
            fileData["path"] = file->filePath();
            fileData["duration"] = file->duration();
            results.append(fileData);
        }
    }
    return results;
}
