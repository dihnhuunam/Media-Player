#include "ManagementController.hpp"

ManagementController::ManagementController(QObject *parent)
    : QObject(parent),
      m_playlistManager(QSharedPointer<PlaylistManager>::create(this))
{
}

ManagementController::~ManagementController()
{
}