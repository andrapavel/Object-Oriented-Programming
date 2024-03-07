#include"SongCollection.h"
#include<fstream>
#include<iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

SongCollection::SongCollection(std::string filename)
{
    std::fstream file(filename);

    if (!file)
    {
        throw std::invalid_argument("Failed to open: " + filename);
    }

    std::string line;

    std::string artist, title;
    std::vector<std::string> lyrics;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value))
        {
            if (key == "ARTIST")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                artist.assign(value);
            }
            else if (key == "TITLE")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                title.assign(value);
            }
            else if (value != "LYRICS=")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 1);
                std::string data;
                std::istringstream valueStream(value);
                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~";

                    std::size_t pos = 0;
                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;

                    if (data.size() > 1)
                    {

                        //remove '' if they are at the end of the word
                        if ((int)data[data.size() - 1] == 39)
                        {
                            if ((int)data[data.size() - 2] == 39)
                                data = data.substr(0, data.size() - 2);
                            else
                                data = data.substr(0, data.size() - 1);
                        }

                        //remove '' if they are at the beginning of the word
                        if ((int)data[0] == 39)
                        {
                            if ((int)data[1] == 39)
                                data = data.substr(2, data.size());
                            else
                                data = data.substr(1, data.size());
                        }
                    }

                    data[0] = tolower(data[0]);
                    lyrics.push_back(data);
                }
            }
        }
        else
        {
            if (key[0] != '"')
            {
                std::string data;
                std::istringstream valueStream(key);
                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~";

                    std::size_t pos = 0;
                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;

                    if (data.size() > 1)
                    {

                        //remove '' if they are at the end of the word
                        if ((int)data[data.size() - 1] == 39)
                        {
                            if ((int)data[data.size() - 2] == 39)
                                data = data.substr(0, data.size() - 2);
                            else
                                data = data.substr(0, data.size() - 1);
                        }

                        //remove '' if they are at the beginning of the word
                        if ((int)data[0] == 39)
                        {
                            if ((int)data[1] == 39)
                                data = data.substr(2, data.size());
                            else
                                data = data.substr(1, data.size());
                        }
                    }

                    data[0] = tolower(data[0]);
                    lyrics.push_back(data);
                }
            }
            else
            {
                songs.push_back(Song(title, artist, lyrics));
                title = "";
                artist = "";
                lyrics.clear();
            }
        }
    }

    file.close();
}

void SongCollection::storeSongs(std::string filename, std::vector<Song>& _songs)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::invalid_argument("Failed to open: " + filename);
    }

    std::string line;
    std::string artist, title;
    std::vector<std::string> lyrics;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value))
        {
            if (key == "ARTIST")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                artist.assign(value);
            }
            else if (key == "TITLE")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                title.assign(value);
            }
            else if (value == "LYRICS=")
            {
                lyrics.clear();
            }
            else
            {
                // Remove leading double quote from the value
                value = value.substr(1);
                std::string data;
                std::istringstream valueStream(value);
                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~0123456789";
                    std::size_t pos = 0;
                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;
                    if (data.size() > 1)
                    {
                        // Remove trailing single quote from the value
                        if (data.back() == '\'')
                        {
                            data = data.substr(0, data.size() - 1);
                        }

                        // Remove leading single quote from the value
                        if (data.front() == '\'')
                        {
                            data = data.substr(1);
                        }
                    }

                    // Convert first character to lowercase
                    data[0] = std::tolower(data[0]);
                    lyrics.push_back(data);
                }
            }
        }
        else
        {
            if (key[0] != '"')
            {
                // Handle case where a song title contains a space
                std::string data;
                std::istringstream valueStream(key);
                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~";
                    std::size_t pos = 0;
                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;
                    if (data.size() > 1)
                    {
                        // Remove trailing single quote from the value
                        if (data.back() == '\'')
                        {
                            data = data.substr(0, data.size() - 1);
                        }

                        // Remove leading single quote from the value
                        if (data.front() == '\'')
                        {
                            data = data.substr(1);
                        }
                    }

                    // Convert first character to lowercase
                    data[0] = std::tolower(data[0]);
                    lyrics.push_back(data);
                }
            }
            else
            {
                _songs.push_back(Song(title, artist, lyrics));
                title = "";
                artist = "";
                lyrics.clear();
            }
        }
    }
}

std::set<std::string> SongCollection::getArtists()
{
    std::set<std::string> artists;

    for (int i = 0; i < songs.size(); i++)
    {
        artists.insert(songs[i].getArtist());
    }

    return artists;
}

std::map<std::string, std::vector<std::string>> SongCollection::artist_And_Title()
{
    std::map<std::string, std::vector<std::string>> artistTitles;

    for (auto& song : songs)
    {
        artistTitles[song.getArtist()].push_back(song.getTitle());
    }

    return artistTitles;
}

std::unordered_set<std::string> SongCollection::songs_containing(std::string find_word)
{
    // A map that contains words from the lyrics as keys and a vector of song titles that contain that word as values
    std::unordered_map<std::string, std::unordered_set<std::string>> word_to_song_titles;

    // Convert find_word to lowercase
    std::transform(find_word.begin(), find_word.end(), find_word.begin(), ::tolower);

    // Build the word_to_song_titles map
    for (auto& song : songs)
    {
        const auto& lyrics = song.getLyrics();
        for (auto& lyric_word : lyrics)
        {
            std::string word = lyric_word;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word == find_word) 
            {
                word_to_song_titles[word].insert(song.getTitle());
            }
        }
    }

    // Check if any song title contains the find_word
    auto it = word_to_song_titles.find(find_word);
    if (it != word_to_song_titles.end()) 
    {
        return it->second;
    }
    else 
    {
        throw std::runtime_error("No song containing \"" + find_word + "\" was found");
    }

}


