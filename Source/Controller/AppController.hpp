#pragma once
#include <QObject>
#include <QSharedPointer>
#include "ManagementController.hpp"
#include "PlaylistManagementController.hpp"
#include "MediaFileManagementController.hpp"
#include "PlaybackController.hpp"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlaybackController *playbackController READ playbackController CONSTANT)
    Q_PROPERTY(ManagementController *playlistController READ playlistController CONSTANT)
    Q_PROPERTY(ManagementController *mediaFileController READ mediaFileController CONSTANT)

private:
    QSharedPointer<PlaybackController> m_playbackController{new PlaybackController(this)};
    QSharedPointer<ManagementController> m_playlistController{new PlaylistManagementController(this)};
    QSharedPointer<ManagementController> m_mediaFileController{new MediaFileManagementController(this)};

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    PlaybackController *playbackController() const { return m_playbackController.data(); }
    ManagementController *playlistController() const { return m_playlistController.data(); }
    ManagementController *mediaFileController() const { return m_mediaFileController.data(); }
};