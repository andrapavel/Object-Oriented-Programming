#include "Song.h"

Song::Song()
{
	this->title = "";
	this->artist = "";
}

Song::Song(std::string title, std::string artist, std::vector<std::string> lyrics)
{
	this->title = title;
	this->artist = artist;
	this->lyrics = lyrics;
}

std::string Song::getTitle()
{
	return this->title;
}

std::string Song::getArtist()
{
	return this->artist;
}

std::vector<std::string> Song::getLyrics()
{
	return this->lyrics;
}


void Song::setTitle(std::string title)
{
	this->title = title;
}

void Song::setArtist(std::string artist)
{
	this->artist = artist;
}

void Song::setLyrics(std::vector<std::string> lyrics)
{
	this->lyrics = lyrics;
}