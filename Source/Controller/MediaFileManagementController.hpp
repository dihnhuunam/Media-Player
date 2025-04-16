#pragma once
#include <QObject>
#include <QVariantList>
#include "ManagementController.hpp"

class MediaFileManagementController : public ManagementController
{
    Q_OBJECT

public:
    explicit MediaFileManagementController(QObject *parent = nullptr);
    ~MediaFileManagementController();

    Q_INVOKABLE void loadFolder(const QString &path);
    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName) const;
    Q_INVOKABLE void addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName);
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName);

signals:
    void mediaFilesChanged(const QString &playlistName);
};