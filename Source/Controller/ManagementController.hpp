#pragma once
#include <QObject>
#include <QSharedPointer>
#include "PlaylistManager.hpp"

class ManagementController : public QObject
{
    Q_OBJECT

protected:
    QSharedPointer<PlaylistManager> m_playlistManager;

public:
    explicit ManagementController(QObject *parent = nullptr);
    virtual ~ManagementController();
};