#pragma once
#include<vector>
#include<string>
#include<set>
#include<map>
#include<unordered_set>
#include "Song.h"

class SongCollection
{
private:
	std::vector<Song> songs;
public:

	SongCollection(std::string filename);

	void storeSongs(std::string filename, std::vector<Song>& _songs);
	std::set<std::string> getArtists();

	std::map<std::string, std::vector<std::string>> artist_And_Title();
	std::unordered_set<std::string> songs_containing(std::string word);
};