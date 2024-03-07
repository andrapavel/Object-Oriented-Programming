#ifndef ACTION_H
#define ACTION_H

#include "song.h"
#include "SongRepo.h"

class Action
{
public:
    virtual ~Action() = default;
    virtual void apply() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

};

// ActionAdd class
class ActionAdd : public Action
{
private:
    RepoSongs& repository;
    Song song;

public:

    ActionAdd(RepoSongs& repo, const Song& s) : repository(repo), song(s) {}

    void apply() override
    {
        repository.store(song);
    }

    void undo() override
    {
        repository.remove(song);
    }

    void redo() override
    {
        apply();
    }
};

// ActionDelete class
class ActionDelete : public Action
{
private:
    RepoSongs& repository;
    Song song;

public:

    ActionDelete(RepoSongs& repo, const Song& s) : repository(repo), song(s) {}

    void apply() override
    {
        repository.remove(song);
    }

    void undo() override
    {
        repository.remove(song);
    }

    void redo() override
    {
        apply();
    }
};

#endif // ACTION_H
