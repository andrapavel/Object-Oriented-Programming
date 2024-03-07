#include "SongException.h"

SongException::SongException(const QString& description)
{
    errorDescription = description;
}

const QString& SongException::whatQString() const
{
    return errorDescription;
}
