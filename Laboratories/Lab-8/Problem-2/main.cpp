#include <iostream>

#include "Song.h"
#include "SongCollection.h"

int main()
{
	SongCollection sc("Read.txt");

	std::vector<Song> _songs;

	try
	{
		sc.storeSongs("Read.txt", _songs);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Not able to open file" << std::endl;
	}

	/*for (int j = 0; j < _songs.size(); j++)
	{
		std::cout << "ARTIST: " << _songs[j].getArtist() << std::endl;
		std::cout << "TITLE: " << _songs[j].getTitle() << std::endl;
		std::cout << "LIRYCS: " << std::endl;
		for (int i = 0; i < _songs[j].getLyrics().size(); i++)
		{
			std::cout << _songs[j].getLyrics()[i] << "  ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}*/

	/*for (auto& str : sc.getArtists())
	{
		std::cout << str << std::endl;
	}*/

	/*for (auto& artist : sc.artist_And_Title())
	{
		std::cout << artist.first << std::endl;
		for (auto& title : artist.second)
		{
			std::cout << "\t" << title << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}*/

	/*auto sort_by_artist_ascending = [](Song& a, Song& b)
	{
		return a.getArtist() < b.getArtist();
	};
	sort(_songs.begin(), _songs.end(), sort_by_artist_ascending);*/


	/*auto sort_by_title_descending = [](Song& a, Song& b)
	{
		return a.getTitle() > b.getTitle();
	};
	sort(_songs.begin(), _songs.end(), sort_by_title_descending);*/

	/*auto sort_by_nrWords_ascending = [](Song& a, Song& b)
	{
		return a.getLyrics().size() < b.getLyrics().size();
	};
	sort(_songs.begin(), _songs.end(), sort_by_nrWords_ascending);*/

	/*for (int i = 0; i < _songs.size(); i++)
	{
		std::cout <<"ARTIST: "<< _songs[i].getArtist() << std::endl;
		std::cout <<"TITLE: "<< _songs[i].getTitle() << std::endl;
		std::cout << "LYRICS: " << std::endl;
		for (auto& lyrics : _songs[i].getLyrics())
		{
			std::cout << lyrics << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}*/

	/*std::unordered_set<std::string> titels;

	titels = sc.songs_containing("me");


	for (auto& title : titels)
	{
		std::cout << title << std::endl;
	}*/
}

