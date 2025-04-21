#pragma once
#include <QList>
#include <QObject>
#include "MediaFile.hpp"

class Playlist : public QObject
{
    Q_OBJECT

private:
    QString m_name;
    QList<MediaFile *> m_mediaFiles;

public:
    explicit Playlist(const QString &name = "Unknown Playlist Name", QObject *parent = nullptr);
    ~Playlist();

    QString name() const;
    void setName(const QString &name);
    int mediaCount() const;
    MediaFile *mediaFileAt(int index) const;
    QList<MediaFile *> mediaFiles() const;

    void addMediaFile(const QString &filePath);
    void addMediaFiles(const QStringList &filePaths);
    void removeMediaFile(int index);

signals:
    void nameChanged();
    void mediaFilesChanged();
};