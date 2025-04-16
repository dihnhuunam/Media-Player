#include "AppController.hpp"

AppController::AppController(QObject *parent)
    : QObject(parent),
      m_playbackController(QSharedPointer<PlaybackController>::create(this)),
      m_mediaFileController(QSharedPointer<MediaFileManagementController>::create(this)),
      m_playlistController(QSharedPointer<PlaylistManagementController>::create(this))
{
}

AppController::~AppController()
{
}