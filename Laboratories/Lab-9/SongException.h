#ifndef SONGEXCEPTION_H
#define SONGEXCEPTION_H

#include <exception>
#include <QString>
#include <QDebug>

class SongException : public std::exception
{

private:
    QString errorDescription;

public:
    SongException(const QString& description);

    const QString& whatQString() const;
};

#endif // SONGEXCEPTION_H
