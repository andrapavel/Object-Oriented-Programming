#include "song.h"

Song::Song(const QString& title, const QString& artist, int year, const QString& lyrics, const QString& url)
{
    this->title = title;
    this->artist = artist;
    this->url = url;
    this->year = year;
    this->lyrics = lyrics;
}

const QString& Song::get_title() const
{
    return this->title;
}

const QString& Song::get_artist() const
{
    return this->artist;
}

const QString& Song::get_lyrics() const
{
    return this->lyrics;
}

int Song::get_year() const
{
    return this->year;
}

const QString& Song::get_url() const
{
    return this->url;
}

bool Song::is_in_playlist() const
{
    return isInPlaylist;
}
