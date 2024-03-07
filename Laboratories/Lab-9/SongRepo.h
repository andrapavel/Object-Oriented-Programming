#ifndef SONGREPO_H
#define SONGREPO_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <stdexcept>
#include <QFile>

#include "song.h"
#include "SongException.h"

class RepoSongs
{

protected:
    QVector<Song> songs;

public:
    RepoSongs() = default;

    RepoSongs(const RepoSongs&) = delete;

    const QVector<Song>& get_all_songs() const;

    void add_song_repo(Song &song);

    virtual void store(const Song& s);

    virtual const Song& find(const QString& title, const QString& artist);

    virtual void remove(const Song& s);

    const Song& findSongByTitleArtist(const QString& title, const QString& artist) const;

    void printSongs() const;

    QVector<Song> get_playlist() const;
};

class FileRepository : public RepoSongs
{
private:
    QString filepath;

public:
    FileRepository(const QString& filepath);

    void load();

    void save();

    void store(const Song& s) override;

    const Song& find(const QString& title, const QString& artist) override;

    void remove(const Song& s) override;
};

#endif // SONGREPO_H

