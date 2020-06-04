#ifndef AUDIO_H
#define AUDIO_H

#include "widget.h"
#include <QObject>
#include <QByteArray>
#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>


class Audio : public QObject
{
    Q_OBJECT

public:
    explicit Audio(QObject *parent = 0);
    ~Audio();
    void on_playButton_clicked();
    void on_enterButton_clicked();
    void on_horizontalSlider_valueChanged(int value);

private:
    void initializeAudio();
    void createAudioInput();
    void createAudioOutput();

    int ApplyVolumeToSample(short iSample);

signals:
    void audioRead(QByteArray baDatagram);

public slots:
    void playAudio(QByteArray baDatagram);

private slots:
    void readMore();
    //void on_horizontalSlider_valueChanged(int value);

private:
    QAudioDeviceInfo m_Inputdevice;
    QAudioDeviceInfo m_Outputdevice;
    QAudioFormat m_format;
    QAudioInput *m_audioInput;
    QAudioOutput *m_audioOutput;
    QIODevice *m_input;
    QIODevice *m_output;
    QByteArray m_buffer;
    int m_iVolume;

};

#endif // AUDIO_H
