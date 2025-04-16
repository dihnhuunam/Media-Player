#pragma once
#include <QObject>
#include <QSharedPointer>
#include "PlaylistManagementController.hpp"
#include "MediaFileManagementController.hpp"
#include "PlaybackController.hpp"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlaybackController *playbackController READ playbackController CONSTANT)
    Q_PROPERTY(MediaFileManagementController *mediaFileController READ mediaFileController CONSTANT)
    Q_PROPERTY(PlaylistManagementController *playlistController READ playlistController CONSTANT)

private:
    QSharedPointer<PlaybackController> m_playbackController;
    QSharedPointer<MediaFileManagementController> m_mediaFileController;
    QSharedPointer<PlaylistManagementController> m_playlistController;

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    PlaybackController *playbackController() const { return m_playbackController.data(); }
    MediaFileManagementController *mediaFileController() const { return m_mediaFileController.data(); }
    PlaylistManagementController *playlistController() const { return m_playlistController.data(); }
};