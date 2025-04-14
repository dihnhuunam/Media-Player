#pragma once
#include <QObject>
#include <QString>

class MediaFile : public QObject
{
    Q_OBJECT
private:
    QString m_filePath;
    QString m_title;
    QString m_author;
    qint64 m_duration;

public:
    explicit MediaFile(const QString &filePath, QObject *parent = nullptr);
    ~MediaFile();

    QString filePath() const;
    QString title() const;
    QString author() const;
    qint64 duration() const;
};