#include "Playlist.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <QRandomGenerator>

void Playlist::addSong(const Song& song)
{
    //songs.append(song);
    songs.push_back(song);
}


void Playlist::removeSong(const Song& song)
{
    // Find and remove the song from the vector
    /*for (auto it = songs.begin(); it != songs.end(); it++)
    {
        if (it->get_title() == song.get_title() && it->get_artist() == song.get_artist())
        {
            songs.erase(it);
            break;
        }
    }*/
    songs.erase(std::remove(songs.begin(), songs.end(), song), songs.end());

}


void Playlist::clear()
{
    songs.clear();
}


void Playlist::generateRandom(const QList<Song>& allSongs, int playlistSize)
{
    // Clear the current playlist
    songs.clear();

    // Generate a random playlist of the desired size
    QRandomGenerator generator;
    while (songs.size() < playlistSize)
    {
        int randomIndex = generator.bounded(allSongs.size());
        const Song& song = allSongs[randomIndex];
        songs.append(song);
    }
}


QString Playlist::printSongs() const
{
    QString output = "Songs in playlist:\n";
    for (const auto& song : songs)
    {
        output += "- Title: " + song.get_title() + ", Artist: " + song.get_artist() + "\n";
    }
    return output;
}
