#pragma once
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>

class MediaFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath CONSTANT)
    Q_PROPERTY(QString title READ title NOTIFY metaDataChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY metaDataChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY metaDataChanged)

private:
    QMediaPlayer *m_player;
    QString m_filePath;
    QString m_title;
    QStringList m_artists;
    qint64 m_duration;

public:
    explicit MediaFile(const QString &filePath, QObject *parent = nullptr);
    ~MediaFile();

    QMediaPlayer *player() const;
    QString filePath() const;
    QString title() const;
    QString artist() const;
    QStringList artists() const;
    qint64 duration() const;
    qreal position() const;
    QMediaPlayer::PlaybackState playbackState() const;

signals:
    void metaDataChanged();

private slots:
    void loadMetaData();
};