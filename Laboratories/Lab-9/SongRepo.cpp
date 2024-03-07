#include "SongRepo.h"

const QVector<Song>& RepoSongs::get_all_songs() const
{
    return this->songs;
}

void RepoSongs::add_song_repo(Song &song)
{
    this->songs.push_back(song);
}

void RepoSongs::store(const Song &s)
{
    auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song)
       {
           return song.get_title() == s.get_title() && song.get_artist() == s.get_artist();
       });

    if (it != songs.end())
    {
        throw SongException("A song '" + s.get_title() + "' by '" + s.get_artist() + "' already exists.");
    }

    songs.push_back(s);
}

const Song& RepoSongs::find(const QString& title, const QString& artist)
{
    auto it = std::find_if(songs.begin(), songs.end(), [&](Song& song)
   {
        return song.get_title() == title && song.get_artist() == artist;
   });

    if (it == songs.end())
    {
        throw SongException("The song '" + title + "' by '" + artist + "' does not exist.");
    }

    return *it;
}

void RepoSongs::remove(const Song &s)
{
    auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song)
   {
       return song.get_title() == s.get_title() && song.get_artist() == s.get_artist();
   });

    if (it == songs.end())
    {
        throw SongException("The song '" + s.get_title() + "' by '" + s.get_artist() + "' does not exist.");
    }

    songs.erase(it);
}

const Song& RepoSongs::findSongByTitleArtist(const QString& title, const QString& artist) const
{
    for (const Song& song : songs)
    {
        if (song.get_title() == title && song.get_artist() == artist)
        {
            return song;
        }
    }
    throw SongException("Song not found.");
}

void RepoSongs::printSongs() const
{
    qDebug() << "Songs in repository:";
    for (const auto& song : songs)
    {
        qDebug() << "- Title: " << song.get_title() << ", Artist: " << song.get_artist();
    }
}

QVector<Song> RepoSongs::get_playlist() const
{
    QVector<Song> playlist;
    for (const Song& song : songs)
    {
        if (song.is_in_playlist())
        {
            playlist.append(song);
        }
    }
    return playlist;
}

// FILE REPOSITORY

void FileRepository::load()
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Unable to open file: " + filepath.toStdString());
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList songAttributes = line.split(';');
        if (songAttributes.size() == 5)
        {
            QString title = songAttributes[0];
            QString artist = songAttributes[1];
            int year = songAttributes[2].toInt();
            QString lyrics = songAttributes[3];
            QString url = songAttributes[4];

            // Create a new Song object and add it to the repository
            Song song(title, artist, year, lyrics, url);
            songs.push_back(song);
        }
    }

    file.close();
}

void FileRepository::save()
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("Unable to save songs to file: " + filepath.toStdString());
    }

    QTextStream out(&file);
    for (const auto& song : songs)
    {
        out << song.get_title() << ";"
            << song.get_artist() << ";"
            << song.get_year() << ";"
            << song.get_lyrics() << ";"
            << song.get_url() << "\n";
    }

    file.close();
}

void FileRepository::store(const Song& s)
{
    RepoSongs::store(s); // Call parent class implementation
    save(); // Save the data to the file after updating the songs
}

const Song& FileRepository::find(const QString& title, const QString& artist)
{
    const Song& foundSong = RepoSongs::find(title, artist); // Call parent class implementation
    save(); // Save the data to the file after updating the songs
    return foundSong;
}

void FileRepository::remove(const Song& s)
{
    RepoSongs::remove(s); // Call parent class implementation
    save(); // Save the data to the file after updating the songs
}

