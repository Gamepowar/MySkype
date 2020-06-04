#include "audio.h"
#include <QDebug>
#include <QTimer>
const int BufferSize = 131072; // 14096


Audio::Audio(QObject *parent) :
    QObject(parent),
       m_Inputdevice(QAudioDeviceInfo::defaultInputDevice())
    ,   m_Outputdevice(QAudioDeviceInfo::defaultOutputDevice())
    ,   m_audioInput(0)
    ,   m_audioOutput(0)
    ,   m_input(0)
    ,   m_output(0)
    ,   m_iVolume(0)
    ,   m_buffer(BufferSize, 0)
{
    initializeAudio();
}



Audio::~Audio()
{
    delete m_audioInput;
    delete m_audioOutput;
    //delete m_input;
    //delete m_output;
}

//Initialize audio
void Audio::initializeAudio()
{

    m_format.setSampleRate(8000); //set frequency to 8000
    m_format.setChannelCount(1); //set channels to mono
    m_format.setSampleSize(16); //set sample size to 16 bit
    m_format.setSampleType(QAudioFormat::UnSignedInt); //Sample type as unsigned integer sample
    m_format.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    m_format.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(m_format))
    {
        //Default format not supported - trying to use nearest
        m_format = infoIn.nearestFormat(m_format);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());

    if (!infoOut.isFormatSupported(m_format))
    {
       //Default format not supported - trying to use nearest
        m_format = infoOut.nearestFormat(m_format);
    }
    createAudioInput();
    createAudioOutput();
}

void Audio::createAudioOutput()
{
    m_audioOutput = new QAudioOutput(m_Outputdevice, m_format, this);
}
void Audio::createAudioInput()
{
    if (m_input != 0) {
        disconnect(m_input, 0, this, 0);
        m_input = 0;
    }

    m_audioInput = new QAudioInput(m_Inputdevice, m_format, this);

}
void Audio::readMore()
{
    //Return if audio input is null
    if(!m_audioInput)
        return;

    //Check the number of samples in input buffer
    qint64 len = m_audioInput->bytesReady();

    //Limit sample size
    if(len > BufferSize) // 4096
        len = BufferSize;
    //Read sound samples from input device to buffer
    qint64 l = m_input->read(m_buffer.data(), len);
    if(l > 0)
    {
        //Assign sound samples to short array
        short* resultingData = (short*)m_buffer.data();


        short *outdata=resultingData;
        outdata[ 0 ] = resultingData [ 0 ];

         int iIndex;
         if(((Widget*)parent())->checkBoxIsChecked());
         {
                //Remove noise using Low Pass filter algortm[Simple algorithm used to remove noise]
                for ( iIndex=1; iIndex < len; iIndex++ )
                {
                    outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
                }
          }

         for ( iIndex=0; iIndex < len; iIndex++ )
         {
             //Cange volume to each integer data in a sample
             outdata[ iIndex ] = ApplyVolumeToSample( outdata[ iIndex ]);
         }

         //write modified sond sample to outputdevice for playback audio
         //m_output->write((char*)outdata, len);
         emit audioRead(QByteArray((char*)outdata, len)); // char and short????????????????????????????????????????????????????
    }
}

void Audio::playAudio(QByteArray baDatagram) {
    m_output->write(baDatagram);
}

int Audio::ApplyVolumeToSample(short iSample)
{
    //Calculate volume, Volume limited to  max 35535 and min -35535
    return std::max(std::min(((iSample * m_iVolume) / 50) ,35535), -35535);

}


void Audio::on_enterButton_clicked() {
    //Audio output device
    if (m_output == nullptr) {
        m_output= m_audioOutput->start();
    }
}


void Audio::on_playButton_clicked() {
    if (m_input == nullptr) {
        m_input = m_audioInput->start();
        //connect readyRead signal to readMre slot.
        //Call readmore when audio samples fill in inputbuffer
        //connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
        QTimer * ptimer = new QTimer(this);
        ptimer->setInterval(90); // CHANGE?????????????????????????????????????????????????????????????????????
        ptimer->start();
        connect(ptimer, SIGNAL(timeout()), SLOT(readMore()));
    }
}


void Audio::on_horizontalSlider_valueChanged(int value) {
    m_iVolume = value;
}

/*void Audio::on_pushButton_clicked()
{
    //Audio output device
    m_output= m_audioOutput->start();
     //Audio input device
    m_input = m_audioInput->start();
    //connect readyRead signal to readMre slot.
    //Call readmore when audio samples fill in inputbuffer
    connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));

}*/



