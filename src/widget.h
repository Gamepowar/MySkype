#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "server.h"
#include "client.h"
#include <QDebug>
//#include "audio.h"

#define INFO() qDebug() << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;

class Audio;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    bool checkBoxIsChecked();
    ~Widget();

    void setSentText(QString text);
    void setReceivedText(QString text);

public slots:
    void on_ipEdit_returnPressed();
    void on_enterButton_clicked();
    void on_playButton_clicked();
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Widget *ui; 
    QString ip;
    Server * server;
    Client * client;
    Audio * audio;
};

#endif // WIDGET_H

