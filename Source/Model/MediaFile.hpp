#pragma once
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>
#include <QAudioOutput>

class MediaFile : public QObject
{
    Q_OBJECT

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
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
    qint64 position() const;
    QMediaPlayer::PlaybackState playbackState() const;

    void play();
    void pause();
    void stop();

signals:
    void metaDataChanged();
    void playbackStateChanged();
    void positionChanged(qint64 position);

private slots:
    void loadMetaData();
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void onPositionChanged(qint64 position);
};