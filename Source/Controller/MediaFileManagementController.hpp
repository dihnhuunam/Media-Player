#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QVariant>
#include "PlaylistManager.hpp"

class MediaFileManagementController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString defaultPlaylistName READ defaultPlaylistName CONSTANT)

private:
    QSharedPointer<PlaylistManager> m_playlistManager;
    QString m_defaultPlaylistName;

public:
    explicit MediaFileManagementController(QSharedPointer<PlaylistManager> manager, QObject *parent = nullptr);
    ~MediaFileManagementController();

    QString defaultPlaylistName() const;

    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName) const;
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName = "");
    Q_INVOKABLE void loadFolder(const QString &folderPath);
    Q_INVOKABLE void loadMediaFiles(const QStringList &filePaths);

signals:
    void mediaFilesChanged(const QString &playlistName);
};