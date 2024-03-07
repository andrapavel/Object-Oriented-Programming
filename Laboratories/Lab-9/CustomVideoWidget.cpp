/*#include "CustomVideoWidget.h"
#include <QMediaPlayer>

CustomVideoWidget::CustomVideoWidget(QWidget *parent) : QVideoWidget(parent)
{
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(this);

    connect(mediaPlayer, &QMediaPlayer::stateChanged, this, &CustomVideoWidget::handleMediaStateChanged);
}

CustomVideoWidget::~CustomVideoWidget()
{
    delete mediaPlayer;
}

void CustomVideoWidget::playVideo(const QString &filePath)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer->play();
}

void CustomVideoWidget::handleMediaStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState)
    {
        // Video playback has stopped
        mediaPlayer->stop();
    }
}*/
