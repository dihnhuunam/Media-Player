#pragma once
#include <QObject>
#include "PlaybackController.hpp"
#include "PlaylistController.hpp"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlaybackController *playbackController READ playbackController CONSTANT)
    Q_PROPERTY(PlaylistController *playlistController READ playlistController CONSTANT)

private:
    PlaybackController *m_playbackController;
    PlaylistController *m_playlistController;

public:
    explicit AppController(QObject *parent = nullptr);
    ~AppController();

    PlaybackController *playbackController() const { return m_playbackController; }
    PlaylistController *playlistController() const { return m_playlistController; }
};