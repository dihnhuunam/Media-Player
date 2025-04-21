#include "AppController.hpp"

AppController::AppController(QObject *parent)
    : QObject(parent),
      m_playbackController(new PlaybackController(this)),
      m_playlistController(new PlaylistController(this))
{
}

AppController::~AppController()
{
    delete m_playbackController;
    delete m_playlistController;
}