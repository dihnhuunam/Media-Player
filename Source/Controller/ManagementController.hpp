#pragma once
#include <QObject>
#include <QSharedPointer>
#include "PlaylistManager.hpp"

class ManagementController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList playlistNames READ playlistNames NOTIFY playlistsChanged)
    Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistsChanged)

protected:
    QSharedPointer<PlaylistManager> m_playlistManager;

public:
    explicit ManagementController(QObject *parent = nullptr);
    virtual ~ManagementController();

    virtual QStringList playlistNames() const;
    virtual int playlistCount() const;

signals:
    void playlistsChanged();
};