#pragma once
#include <QObject>
#include <QSharedPointer>
#include "PlaybackController.hpp"
#include "PlaylistController.hpp"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlaybackController *playbackController READ playbackController CONSTANT)
    Q_PROPERTY(PlaylistController *playlistController READ playlistController CONSTANT)

private:
    QSharedPointer<PlaybackController> m_playbackController{new PlaybackController(this)};
    QSharedPointer<PlaylistController> m_playlistController{new PlaylistController(this)};

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    PlaybackController *playbackController() const { return m_playbackController.data(); }
    PlaylistController *playlistController() const { return m_playlistController.data(); }
};