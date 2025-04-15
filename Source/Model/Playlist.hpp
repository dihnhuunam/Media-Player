#pragma once
#include <QSharedPointer>
#include <QVariant>
#include "MediaFile.hpp"

class Playlist : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int mediaCount READ mediaCount NOTIFY mediaFilesChanged)

private:
    QString m_name;
    QList<QSharedPointer<MediaFile>> m_mediaFiles;

public:
    explicit Playlist(const QString &name = "Unknown Playlist Name", QObject *parent = nullptr);
    ~Playlist();

    QString name() const;
    void setName(const QString &name);
    int mediaCount() const;

    Q_INVOKABLE QSharedPointer<MediaFile> mediaFileAt(int index) const;
    Q_INVOKABLE QString mediaNameAt(int index) const;
    Q_INVOKABLE QString mediaPathAt(int index) const;
    Q_INVOKABLE QVariantList mediaFiles() const;

    Q_INVOKABLE void addMediaFile(const QString &filePath);
    Q_INVOKABLE void addMediaFiles(const QStringList &filePaths);
    Q_INVOKABLE void removeMediaFile(int index);
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query);

signals:
    void nameChanged();
    void mediaFilesChanged();
};