#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <QVector>
#include <random>

// Playlist class
class Playlist
{
private:
    QVector<Song> songs;

public:
    void addSong(const Song& song);

    void removeSong(const Song& song);

    void clear();

    //void generateRandom(int n, const QVector<Song>& songList);

    void generateRandom(const QList<Song>& allSongs, int playlistSize);

    const QVector<Song>& getSongs() const
    {
        return songs;
    }

    QString printSongs() const;
};

#endif // PLAYLIST_H
