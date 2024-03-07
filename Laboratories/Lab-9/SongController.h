#ifndef SONGCONTROLLER_H
#define SONGCONTROLLER_H

#include "SongRepo.h"
#include "song.h"
#include "Action.h"

#include <algorithm>
#include <vector>
#include <QString>
#include <QStack>
#include <stack>

class SongController
{
private:
    RepoSongs& repository;

    std::stack<std::unique_ptr<Action>> undoStack;
    std::stack<std::unique_ptr<Action>> redoStack;

public:
    SongController(RepoSongs& repository);

    void add_song(QString& title, QString& artist, int year, const QString& lyrics = "", const QString& url = "");

    //void remove_song(QString& title, QString& artist);

    void remove_song(const QString& title, const QString& artist);

    const Song& search_song(QString& title, QString& artist);

    QVector<Song> get_sorted_songs_by_artist(bool ascendingOrder = true);

    QVector<Song> get_sorted_songs_by_title(bool ascendingOrder = true);

    //void addAction(Action* action);

    void addAction(std::unique_ptr<Action> action);

    void addActionToUndoStack(std::unique_ptr<Action> action);

    void undo();

    void redo();

    void printSongs() const;
};

#endif // SONGCONTROLLER_H
