#include "widget.h"
#include "audio.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    server(nullptr),
    client(nullptr),
    audio(new Audio(this))
{
    ui->setupUi(this);

}

bool Widget::checkBoxIsChecked() {
    return ui->checkBox->checkState() == Qt::Checked;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::setSentText(QString text) {
    ui->sentOutput->setText(text);
}

void Widget::setReceivedText(QString text) {
    ui->receiveOutput->setText(text);
}

void Widget::on_ipEdit_returnPressed() {
    on_enterButton_clicked();
}


void Widget::on_playButton_clicked() {
    audio->on_playButton_clicked();
    if (server != nullptr)
        disconnect(audio, SIGNAL(audioRead(QByteArray)), server, SLOT(slotSendDatagram(QByteArray)));
    delete server;
    server = new Server(ip, this);
    connect(audio, SIGNAL(audioRead(QByteArray)), server, SLOT(slotSendDatagram(QByteArray)));
}

void Widget::on_enterButton_clicked() {
    audio->on_enterButton_clicked();
    if (client != nullptr)
        disconnect(client, SIGNAL(datagramReceived(QByteArray)), audio, SLOT(playAudio(QByteArray)));
    ip = ui->ipEdit->text();
    delete client;
    client = new Client(ip, this);
    connect(client, SIGNAL(datagramReceived(QByteArray)), audio, SLOT(playAudio(QByteArray)));
}

void Widget::on_horizontalSlider_valueChanged(int value) {
    audio->on_horizontalSlider_valueChanged(value);
}

