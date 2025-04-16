#pragma once
#include <QObject>
#include <QVariant>
#include "ManagementController.hpp"
#include "MediaFile.hpp"

class MediaFileManagementController : public ManagementController
{
    Q_OBJECT

public:
    explicit MediaFileManagementController(QObject *parent = nullptr);
    ~MediaFileManagementController();

    Q_INVOKABLE QVariantList mediaFiles(const QString &playlistName) const;
    Q_INVOKABLE QVariantList searchMediaFiles(const QString &query, const QString &playlistName) const;
    Q_INVOKABLE void loadMediaFiles(const QStringList &filePaths);
    Q_INVOKABLE void loadFolder(const QString &folderPath);
    Q_INVOKABLE void addFilesToPlaylist(const QStringList &filePaths, const QString &playlistName);
};