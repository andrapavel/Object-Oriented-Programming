#include "SongController.h"
#include "Action.h"

SongController::SongController(RepoSongs& repository) : repository(repository)
{

}

void SongController::add_song(QString& title, QString& artist, int year, const QString& lyrics, const QString& url)
{
    try
    {
        repository.find(title, artist);  // Check if the song already exists
        throw SongException("A song '" + title + "' by '" + artist + "' already exists.");
    } catch (const SongException&)
    {
        Song newSong(title, artist, year, lyrics, url);
        repository.store(newSong);
        addAction(std::make_unique<ActionAdd>(repository, newSong));
    }
}

/*void SongController::remove_song(QString& title, QString& artist)
{
    const Song& song = search_song(title, artist);
    std::unique_ptr<Action> action = std::make_unique<ActionDelete>(repository, song);
    addAction(std::move(action));
    repository.remove(song);
}*/

void SongController::remove_song(const QString& title, const QString& artist)
{
    // Find the song by title and artist in the repository
    const Song& songToRemove = repository.findSongByTitleArtist(title, artist);

    // Remove the song from the repository
    repository.remove(songToRemove);
}

const Song& SongController::search_song(QString& title, QString& artist)
{
    return repository.find(title, artist);
}

QVector<Song> SongController::get_sorted_songs_by_artist(bool ascendingOrder)
{
    QVector<Song> sortedSongs = repository.get_all_songs();
    std::sort(sortedSongs.begin(), sortedSongs.end(), [&](const Song& song1, const Song& song2)
      {
          if (ascendingOrder)
          {
              return song1.get_artist() < song2.get_artist();
          }
          else
          {
              return song1.get_artist() > song2.get_artist();
          }
      });
    return sortedSongs;
}

QVector<Song> SongController::get_sorted_songs_by_title(bool ascendingOrder)
{
    QVector<Song> sortedSongs = repository.get_all_songs();
    std::sort(sortedSongs.begin(), sortedSongs.end(), [&](const Song& song1, const Song& song2)
        {
          if (ascendingOrder)
          {
              return song1.get_title() < song2.get_title();
          }
          else
          {
              return song1.get_title() > song2.get_title();
          }
        });
    return sortedSongs;
}

void SongController::addAction(std::unique_ptr<Action> action)
{
    undoStack.push(std::move(action));
    redoStack = std::stack<std::unique_ptr<Action>>();
    /*undoStack.push(std::move(action));
    redoStack.clear();*/
}

void SongController::addActionToUndoStack(std::unique_ptr<Action> action)
{
    undoStack.push(std::move(action));
}

void SongController::undo()
{
    if (!undoStack.empty())
    {
        std::unique_ptr<Action> action = std::move(undoStack.top());
        undoStack.pop();
        action->undo();
        redoStack.push(std::move(action));
    }
}

void SongController::redo()
{
    if (!redoStack.empty())
    {
        std::unique_ptr<Action> action = std::move(redoStack.top());
        redoStack.pop();
        action->redo();
        undoStack.push(std::move(action));
    }
}

void SongController::printSongs() const
{
    repository.printSongs();
}

