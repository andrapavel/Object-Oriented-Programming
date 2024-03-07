#ifndef SONG_H
#define SONG_H

#include <QString>

class Song
{

private:
    QString title;
    QString artist;
    QString lyrics;
    QString url;
    int year;

    bool isInPlaylist;

public:
    Song() = default;

    Song(const QString& title, const QString& artist, int year, const QString& lyrics, const QString& url);

    const QString& get_title() const;

    const QString& get_artist() const;

    const QString& get_lyrics() const;

    int get_year() const;

    const QString& get_url() const;

    bool operator==(const Song& other) const
    {
        return title == other.title && artist == other.artist;
    }

    bool is_in_playlist() const;

};

#endif // SONG_H
