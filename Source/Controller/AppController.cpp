#include <QDebug>
#include "AppController.hpp"

AppController::AppController(QObject *parent)
    : QObject(parent),
      m_playlistManager(QSharedPointer<PlaylistManager>::create(this)),
      m_playlistController(QSharedPointer<PlaylistManagementController>::create(m_playlistManager, this)),
      m_mediaController(QSharedPointer<MediaFileManagementController>::create(m_playlistManager, this)),
      m_playbackController(QSharedPointer<PlaybackController>::create(this))
{
    connect(m_playlistController.data(), &PlaylistManagementController::playlistsChanged, this, &AppController::playlistsChanged);
    connect(m_mediaController.data(), &MediaFileManagementController::mediaFilesChanged, this, &AppController::mediaFilesChanged);
    connect(m_playbackController.data(), &PlaybackController::currentPlaylistChanged, this, &AppController::currentPlaylistChanged);
    connect(m_playbackController.data(), &PlaybackController::currentMediaIndexChanged, this, &AppController::currentMediaIndexChanged);
    connect(m_playbackController.data(), &PlaybackController::currentMediaChanged, this, &AppController::currentMediaChanged);
    connect(m_playbackController.data(), &PlaybackController::playbackStateChanged, this, &AppController::playbackStateChanged);
    connect(m_playbackController.data(), &PlaybackController::volumeChanged, this, &AppController::volumeChanged);
    connect(m_playbackController.data(), &PlaybackController::positionChanged, this, &AppController::positionChanged);
}

AppController::~AppController()
{
}

QStringList AppController::playlistNames() const
{
    return m_playlistController->playlistNames();
}

int AppController::playlistCount() const
{
    return m_playlistController->playlistCount();
}

QString AppController::currentPlaylistName() const
{
    return m_playbackController->currentPlaylistName();
}

int AppController::currentMediaIndex() const
{
    return m_playbackController->currentMediaIndex();
}

QString AppController::currentMediaTitle() const
{
    return m_playbackController->currentMediaTitle();
}

QString AppController::currentMediaArtist() const
{
    return m_playbackController->currentMediaArtist();
}

qint64 AppController::currentMediaDuration() const
{
    return m_playbackController->currentMediaDuration();
}

QMediaPlayer::PlaybackState AppController::playbackState() const
{
    return m_playbackController->playbackState();
}

int AppController::volume() const
{
    return m_playbackController->volume();
}

void AppController::setVolume(int volume)
{
    m_playbackController->setVolume(volume);
}

qint64 AppController::position() const
{
    return m_playbackController->position();
}

void AppController::setPosition(qint64 position)
{
    m_playbackController->setPosition(position);
}

void AppController::addPlaylist(const QString &name)
{
    m_playlistController->addPlaylist(name);
}

void AppController::removePlaylist(const QString &name)
{
    m_playlistController->removePlaylist(name);
}

void AppController::renamePlaylist(const QString &oldName, const QString &newName)
{
    m_playlistController->renamePlaylist(oldName, newName);
}

QStringList AppController::searchPlaylists(const QString &query)
{
    return m_playlistController->searchPlaylists(query);
}

QVariantList AppController::mediaFiles(const QString &playlistName)
{
    return m_mediaController->mediaFiles(playlistName);
}

QVariantList AppController::searchMediaFiles(const QString &query, const QString &playlistName)
{
    return m_mediaController->searchMediaFiles(query, playlistName);
}

void AppController::loadFolder(const QString &folderPath)
{
    m_mediaController->loadFolder(folderPath);
}

void AppController::loadMediaFiles(const QStringList &filePaths)
{
    m_mediaController->loadMediaFiles(filePaths);
}

void AppController::selectPlaylist(const QString &name)
{
    auto playlist = m_playlistManager->playlist(name);
    m_playbackController->setCurrentPlaylist(playlist);
}

void AppController::selectMedia(int index)
{
    m_playbackController->setCurrentMediaIndex(index);
}

void AppController::play()
{
    m_playbackController->play();
}

void AppController::pause()
{
    m_playbackController->pause();
}

void AppController::stop()
{
    m_playbackController->stop();
}

void AppController::next()
{
    m_playbackController->next();
}

void AppController::previous()
{
    m_playbackController->previous();
}