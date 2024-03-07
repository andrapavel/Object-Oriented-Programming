#pragma once
#include<string>
#include<vector>

class Song
{
private:
	std::vector<std::string> lyrics;
protected:
	std::string title;
	std::string artist;

public:

	Song();
	Song(std::string title, std::string artist, std::vector<std::string> lyrics);

	std::string getTitle();
	std::string getArtist();

	std::vector<std::string> getLyrics();

	void setTitle(std::string title);
	void setArtist(std::string artist);
	void setLyrics(std::vector<std::string> lyrics);
};