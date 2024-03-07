#ifndef SONGTESTS_H
#define SONGTESTS_H

#include "SongRepo.h"
#include "SongController.h"

#include <cassert>

class RepoTests
{
public:    
    static void runTests()
    {
        RepoSongs repository;

        try
        {
            Song song1("Title 1", "Artist 1", 2020, "Lyrics 1", "URL 1");
            repository.store(song1);

            Song song2("Title 2", "Artist 2", 2019, "Lyrics 2", "URL 2");
            repository.store(song2);

            Song song3("Title 3", "Artist 3", 2021, "Lyrics 3", "URL 3");
            repository.store(song3);

            Song& foundSong = repository.find("Title 1", "Artist 1");
            qDebug() << "Found song:" << foundSong.get_title() << "by" << foundSong.get_artist();

            std::vector<Song>& allSongs = repository.get_all_songs();
            for (const auto& song : allSongs)
            {
                qDebug() << "Song:" << song.get_title() << "by" << song.get_artist();
            }
        }
        catch (const SongException& ex)
        {
            qDebug() << ex.what();
        }
    }
};

class FileRepoTests
{
public:
    static void runTests()
    {
        testStoreAndLoad();
        testFind();
        testRemove();
    }
private:
    static void testStoreAndLoad()
    {
        // Create a repository and some songs
        FileRepository repo("test_songs.txt");
        Song song1("Title 1", "Artist 1", 2021, "Lyrics 1", "URL 1");
        Song song2("Title 2", "Artist 2", 2022, "Lyrics 2", "URL 2");

        // Store the songs in the repository
        repo.store(song1);
        repo.store(song2);

        // Load the songs from the repository
        repo.load();

        // Check if the songs were loaded correctly
        const std::vector<Song>& loadedSongs = repo.get_all_songs();
        assert(loadedSongs.size() == 2);
        assert(loadedSongs[0].get_title() == "Title 1");
        assert(loadedSongs[1].get_artist() == "Artist 2");
    }

    static void testFind()
    {
        // Create a repository and some songs
        FileRepository repo("test_songs.txt");
        Song song1("Title 1", "Artist 1", 2021, "Lyrics 1", "URL 1");
        Song song2("Title 2", "Artist 2", 2022, "Lyrics 2", "URL 2");

        // Store the songs in the repository
        repo.store(song1);
        repo.store(song2);

        // Find a song by title and artist
        const Song& foundSong = repo.find("Title 1", "Artist 1");
        assert(foundSong.get_year() == 2021);
        assert(foundSong.get_lyrics() == "Lyrics 1");
        assert(foundSong.get_url() == "URL 1");
    }

    static void testRemove()
    {
        // Create a repository and some songs
        FileRepository repo("test_songs.txt");
        Song song1("Title 1", "Artist 1", 2021, "Lyrics 1", "URL 1");
        Song song2("Title 2", "Artist 2", 2022, "Lyrics 2", "URL 2");

        // Store the songs in the repository
        repo.store(song1);
        repo.store(song2);

        // Remove a song from the repository
        repo.remove(song1);

        // Check if the song was removed
        const std::vector<Song>& remainingSongs = repo.get_all_songs();
        assert(remainingSongs.size() == 1);
        assert(remainingSongs[0].get_title() == "Title 2");
        assert(remainingSongs[0].get_artist() == "Artist 2");
    }

};

class SongControllerTests
{
public:
    static void runTests()
    {
        testAddSong();
        testRemoveSong();
        testSearchSong();
        testGetSortedSongsByArtist();
        testGetSortedSongsByTitle();
        testUndoRedo();
    }

private:
    static void testAddSong()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add a new song
        QString title = "Title 1";
        QString artist = "Artist 1";
        int year = 2021;
        QString lyrics = "Lyrics 1";
        QString url = "URL 1";

        controller.add_song(title, artist, year, lyrics, url);

        // Check if the song was added to the repository
        const Song& addedSong = repository.find(title, artist);
        assert(addedSong.get_year() == year);
        assert(addedSong.get_lyrics() == lyrics);
        assert(addedSong.get_url() == url);
    }

    static void testRemoveSong()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add a song to the repository
        QString title = "Title 1";
        QString artist = "Artist 1";
        int year = 2021;
        QString lyrics = "Lyrics 1";
        QString url = "URL 1";
        Song song(title, artist, year, lyrics, url);
        repository.store(song);

        // Remove the song
        controller.remove_song(title, artist);

        // Check if the song was removed from the repository
        bool songExists = true;
        try
        {
            repository.find(title, artist);
        }
        catch (const SongException&)
        {
            songExists = false;
        }
        assert(!songExists);
    }

    static void testSearchSong()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add a song to the repository
        QString title = "Title 1";
        QString artist = "Artist 1";
        int year = 2021;
        QString lyrics = "Lyrics 1";
        QString url = "URL 1";
        Song song(title, artist, year, lyrics, url);
        repository.store(song);

        // Search for the song
        const Song& foundSong = controller.search_song(title, artist);

        // Check if the correct song was found
        assert(foundSong.get_title() == title);
        assert(foundSong.get_artist() == artist);
    }

    static void testGetSortedSongsByArtist()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add some songs to the repository
        repository.store(Song("Title 1", "Artist B", 2021, "Lyrics 1", "URL 1"));
        repository.store(Song("Title 2", "Artist A", 2022, "Lyrics 2", "URL 2"));
        repository.store(Song("Title 3", "Artist C", 2023, "Lyrics 3", "URL 3"));

        // Get the songs sorted by artist in ascending order
        QVector<Song> sortedSongs = controller.get_sorted_songs_by_artist(true);

        // Check if the songs are sorted correctly
        assert(sortedSongs.size() == 3);
        assert(sortedSongs[0].get_artist() == "Artist A");
        assert(sortedSongs[1].get_artist() == "Artist B");
        assert(sortedSongs[2].get_artist() == "Artist C");
    }

    static void testGetSortedSongsByTitle()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add some songs to the repository
        repository.store(Song("Title B", "Artist 1", 2021, "Lyrics 1", "URL 1"));
        repository.store(Song("Title A", "Artist 2", 2022, "Lyrics 2", "URL 2"));
        repository.store(Song("Title C", "Artist 3", 2023, "Lyrics 3", "URL 3"));

        // Get the songs sorted by title in descending order
        QVector<Song> sortedSongs = controller.get_sorted_songs_by_title(false);

        // Check if the songs are sorted correctly
        assert(sortedSongs.size() == 3);
        assert(sortedSongs[0].get_title() == "Title C");
        assert(sortedSongs[1].get_title() == "Title B");
        assert(sortedSongs[2].get_title() == "Title A");
    }

    static void testUndoRedo()
    {
        FileRepository repository("test_songs.txt");
        SongController controller(repository);

        // Add a song and then undo the action
        QString title = "Title 1";
        QString artist = "Artist 1";
        int year = 2021;
        QString lyrics = "Lyrics 1";
        QString url = "URL 1";

        controller.add_song(title, artist, year, lyrics, url);
        controller.undo();

        // Check if the song was removed from the repository
        bool songExists = true;
        try
        {
            repository.find(title, artist);
        }
        catch (const SongException&)
        {
            songExists = false;
        }
        assert(!songExists);

        // Redo the action and check if the song is added again
        controller.redo();

        // Check if the song was added to the repository
        const Song& addedSong = repository.find(title, artist);
        assert(addedSong.get_year() == year);
        assert(addedSong.get_lyrics() == lyrics);
        assert(addedSong.get_url() == url);
    }
};

#endif // SONGTESTS_H

