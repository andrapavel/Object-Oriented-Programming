#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "song.h"
#include <QDebug>
#include "SongController.h"
#include "SongException.h"
#include "Playlist.h"
#include "CustomVideoWidget.h"

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QMessageBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QStringListModel>
#include <QLabel>
#include <QShortcut>
#include <QString>
#include <QTextEdit>
#include <QInputDialog>
#include <QFileDialog>

//#include <QMediaPlayer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SongController songController;
    RepoSongs songRepo;
    Playlist playlist;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QLabel* titleLabel;
    QLineEdit* titleLineEdit;
    QLabel* artistLabel;
    QLineEdit* artistLineEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QListView* songListView;
    QStringListModel* songListModel;
    QLineEdit* yearLineEdit;
    QLabel* lyricsLabel;
    QTextEdit* lyricsTextEdit;
    QLineEdit* urlLineEdit;
    //QMediaPlayer* mediaPlayer;

    QPushButton* sortTitleButton;
    QPushButton* sortArtistButton;
    QPushButton* viewLyricsButton;
    QPushButton* createRandomPlaylistButton;
    //QPushButton* playButton;


    QListView* playlistListView;
    QStringListModel* playlistListModel;
    //QPushButton* addToPlaylistButton;
    //QPushButton* removeFromPlaylistButton;

public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent), songController(songRepo)
    {
        // Initialize GUI components
        mainLayout = new QVBoxLayout();
        buttonsLayout = new QHBoxLayout();
        titleLabel = new QLabel("Title:");
        titleLineEdit = new QLineEdit(this);
        artistLabel = new QLabel("Artist:");
        artistLineEdit = new QLineEdit(this);
        addButton = new QPushButton("Add");
        removeButton = new QPushButton("Remove");
        songListView = new QListView();
        songListModel = new QStringListModel();
        yearLineEdit = new QLineEdit(this);
        lyricsLabel = new QLabel("Artist:");
        lyricsTextEdit = new QTextEdit(this);
        urlLineEdit = new QLineEdit(this);

        sortTitleButton = new QPushButton("Sort by Title");
        sortArtistButton = new QPushButton("Sort by Artist");
        viewLyricsButton = new QPushButton("View Lyrics", this);
        createRandomPlaylistButton = new QPushButton("Create Random Playlist", this);

        songListView->setModel(songListModel);

        // Connect button signals to slots
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
        connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeButtonClicked);

        connect(sortTitleButton, &QPushButton::clicked, this, &MainWindow::sortTitleButtonClicked);
        connect(sortArtistButton, &QPushButton::clicked, this, &MainWindow::sortArtistButtonClicked);
        connect(viewLyricsButton, &QPushButton::clicked, this, &MainWindow::showSongLyrics);
        connect(createRandomPlaylistButton, &QPushButton::clicked, this, &MainWindow::createRandomPlaylistButtonClicked);

        // Set up layouts
        mainLayout->addWidget(titleLabel);
        mainLayout->addWidget(titleLineEdit);
        mainLayout->addWidget(artistLabel);
        mainLayout->addWidget(artistLineEdit);

        buttonsLayout->addWidget(addButton);
        buttonsLayout->addWidget(removeButton);

        buttonsLayout->addWidget(sortTitleButton);
        buttonsLayout->addWidget(sortArtistButton);
        buttonsLayout->addWidget(viewLyricsButton);
        buttonsLayout->addWidget(createRandomPlaylistButton);

        mainLayout->addLayout(buttonsLayout);
        mainLayout->addWidget(songListView);

        mainLayout->addWidget(new QLabel("Year:"));
        mainLayout->addWidget(yearLineEdit);
        mainLayout->addWidget(new QLabel("Lyrics:"));
        mainLayout->addWidget(lyricsTextEdit);
        mainLayout->addWidget(new QLabel("URL:"));
        mainLayout->addWidget(urlLineEdit);

        QWidget* centralWidget = new QWidget();
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);

        // Set up key shortcuts for undo and redo
        QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
        connect(undoShortcut, &QShortcut::activated, this, &MainWindow::undoShortcutActivated);

        QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
        connect(redoShortcut, &QShortcut::activated, this, &MainWindow::redoShortcutActivated);

        // Set the window title
        setWindowTitle("Song Manager");
    }

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            addButtonClicked();
        }
        QMainWindow::keyPressEvent(event);
    }

private slots:
    void addButtonClicked()
    {
        QString title = titleLineEdit->text();
        QString artist = artistLineEdit->text();
        int year = yearLineEdit->text().toInt();
        QString lyrics = lyricsTextEdit->toPlainText();
        QString url = urlLineEdit->text();

        try
        {
            songController.add_song(title, artist, year, lyrics, url);
            updateSongList();
            clearInputFields();
        }
        catch (const SongException& ex)
        {
            QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
        }
    }

    void removeButtonClicked()
    {
        /*QModelIndexList selectedIndexes = songListView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty())
        {
            int row = selectedIndexes.first().row();
            QStringList songs = songListModel->stringList();
            if (row >= 0 && row < songs.size())
            {
                QString selectedSong = songs.at(row);
                QStringList songInfo = selectedSong.split(" - ");
                if (songInfo.size() >= 5)
                {
                    QString title = songInfo.at(0);
                    QString artist = songInfo.at(1);
                    QString year = songInfo.at(2);
                    QString lyrics = songInfo.at(3);
                    QString url = songInfo.at(4);

                    Song song(title, artist, year.toInt(), lyrics, url);
                    songController.remove_song(title, artist);
                    updateSongList();
                }
            }
        }*/
        qDebug()<<"remove";
        QModelIndexList selectedIndexes = songListView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty())
        {
            int row = selectedIndexes.first().row();
            qDebug()<<"remove  sel row "<<row <<songListModel->rowCount();
            if (row >= 0 && row < songListModel->rowCount())
            {
                QString selectedSong = songListModel->data(selectedIndexes.first(), Qt::UserRole + 1).toString();
                QStringList songInfo = selectedSong.split(" - ");
                qDebug()<<songInfo;
                if (songInfo.size() >= 5)
                {
                    QString title = songInfo.at(0);
                    QString artist = songInfo.at(1);
                    //QString year = songInfo.at(2);
                    //QString lyrics = songInfo.at(3);
                    //QString url = songInfo.at(4);

                    // Remove the song from the song list
                    songListModel->removeRow(row);

                    // Remove the song from the songController
                    songController.remove_song(title, artist);
                }
            }
        }
    }


    void sortSongsByTitle()
    {
        QStringList songList = songListModel->stringList();

        // Sort the song list by title
        std::sort(songList.begin(), songList.end(), [](const QString& song1, const QString& song2)
                  {
                      QStringList parts1 = song1.split(" - ");
                      QStringList parts2 = song2.split(" - ");
                      if (parts1.size() >= 2 && parts2.size() >= 2)
                      {
                          return parts1[0] < parts2[0];
                      }
                      return false;
                  });

        // Update the song list model with the sorted list
        songListModel->setStringList(songList);
    }

    void sortTitleButtonClicked()
    {
        sortSongsByTitle();
    }

    void sortSongsByArtist()
    {
        QStringList songList = songListModel->stringList();

        // Sort the song list by artist
        std::sort(songList.begin(), songList.end(), [](const QString& song1, const QString& song2)
        {
          QStringList parts1 = song1.split(" - ");
          QStringList parts2 = song2.split(" - ");
          if (parts1.size() >= 2 && parts2.size() >= 2)
          {
              return parts1[1] < parts2[1];
          }
          return false;
        });

        // Update the song list model with the sorted list
        songListModel->setStringList(songList);
    }

    void sortArtistButtonClicked()
    {
        sortSongsByArtist();
    }

    void undoShortcutActivated()
    {
        songController.undo();
        updateSongList();
    }

    void redoShortcutActivated()
    {
        songController.redo();
        updateSongList();
    }

    void showSongLyrics()
    {
        // Get the selected song from the song list
        QModelIndexList selectedIndexes = songListView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty())
        {
            int selectedIndex = selectedIndexes.first().row();
            QString selectedSong = songListModel->stringList().at(selectedIndex);

            QStringList parts = selectedSong.split(" - ");
            if (parts.size() >= 2)
            {
                QString title = parts[0];
                QString artist = parts[1];

                try
                {
                    const Song& foundSong = songRepo.find(title, artist);
                    QString lyrics = foundSong.get_lyrics();
                    lyricsLabel->setText(lyrics);
                }
                catch (const SongException& ex)
                {
                    // Handle the exception if the song is not found
                    QMessageBox::warning(this, "Song Not Found", ex.what());
                }
            }
        }
    }

    void updatePlaylistView()
    {
        playlistListModel->setStringList({});

        // Retrieve the songs from the playlist
        const QList<Song>& songs = playlist.getSongs();

        // Add the songs to the playlist view
        QStringList playlist;
        for (const Song& song : songs)
        {
            QString songInfo = song.get_title() + " - " + song.get_artist();
            playlist << songInfo;
        }
        playlistListModel->setStringList(playlist);
    }

    void createRandomPlaylistButtonClicked()
    {
        // Get all the songs from the repository
        QList<Song> allSongs = songRepo.get_all_songs();

        // Get the number of songs in the repository
        int songCount = allSongs.size();

        // Get the desired size of the random playlist from the user
        bool ok;
        int playlistSize = QInputDialog::getInt(this, "Random Playlist", "Enter the size of the random playlist:", 1, 1, songCount, 1, &ok);
        if (!ok)
            return; // User canceled

        // Clear the current playlist
        playlist.clear();

        // Generate a random playlist of the desired size
        playlist.generateRandom(allSongs, playlistSize);

        // Update the playlist view
        updatePlaylistView();
    }

    /*void playButtonClicked()
    {
        // Get the selected song or playlist
        // For playing a single song:
        QString selectedSong = getSelectedSong(); // Replace with your code to get the selected song

        // For playing a playlist:
        QList<QString> selectedPlaylist = getSelectedPlaylist();

        // Set the media content of the QMediaPlayer
        if (!selectedSong.isEmpty())
        {
            // For playing a single song:
            mediaPlayer->setMedia(QUrl::fromLocalFile(selectedSong));
        }
        else if (!selectedPlaylist.isEmpty())
        {
            // For playing a playlist:
            mediaPlayer->setMedia(QMediaContent(), QIODevice::ReadOnly); // Clear the media content first
            for (const QString& song : selectedPlaylist)
            {
                mediaPlayer->addToPlaylist(QUrl::fromLocalFile(song));
            }
        }

        // Start playing the media
        mediaPlayer->play();
    }*/


    /*void on_playButton_clicked()
    {
        QString videoFilePath = QFileDialog::getOpenFileName(this, "Select Video", QString(), "Video Files (*.mp4 *.avi)");

        if (!videoFilePath.isEmpty())
        {
            customVideoWidget->playVideo(videoFilePath);
        }
    }*/

private:

    void updateSongList()
    {
        QVector<Song> songs = songRepo.get_all_songs();

        // Sort songs by artist
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b)
        {
            return a.get_artist() < b.get_artist();
        });

        QStringList songList;
        for (const Song& song : songs)
        {
            QString songInfo = song.get_title() + " - " + song.get_artist();
            songList.append(songInfo);
        }
        songListModel->setStringList(songList);
    }

    void clearInputFields()
    {
        titleLineEdit->clear();
        artistLineEdit->clear();

        yearLineEdit->clear();
        lyricsTextEdit->clear();
        urlLineEdit->clear();
    }

public:
    ~MainWindow()
    {
        delete mainLayout;
        delete buttonsLayout;
        delete titleLabel;
        delete titleLineEdit;
        delete artistLabel;
        delete artistLineEdit;
        delete addButton;
        delete removeButton;
        delete songListView;
        delete songListModel;

        delete yearLineEdit;
        delete lyricsTextEdit;
        delete urlLineEdit;
    }

private:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
