#include "ManagementController.hpp"
#include <QDebug>

ManagementController::ManagementController(QObject *parent)
    : QObject(parent), m_playlistManager(new PlaylistManager(this))
{
}

ManagementController::~ManagementController()
{
}

QStringList ManagementController::playlistNames() const
{
  if (!m_playlistManager)
  {
    qDebug() << "Error: PlaylistManager is null";
    return QStringList();
  }
  return m_playlistManager->playlistNames();
}

int ManagementController::playlistCount() const
{
  if (!m_playlistManager)
  {
    qDebug() << "Error: PlaylistManager is null";
    return 0;
  }
  return m_playlistManager->playlistCount();
}