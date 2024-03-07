/*#ifndef CUSTOMVIDEOWIDGET_H
#define CUSTOMVIDEOWIDGET_H

#include <QVideoWidget>

class CustomVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit CustomVideoWidget(QWidget *parent = nullptr);
    ~CustomVideoWidget();

    void playVideo(const QString &filePath);

private:
    QMediaPlayer *mediaPlayer;

private slots:
    void handleMediaStateChanged(QMediaPlayer::State state);
};

#endif // CUSTOMVIDEOWIDGET_H*/

