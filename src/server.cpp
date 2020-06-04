#include "server.h"
#include "widget.h"


Server::Server(QString ip, QObject *parent) : QObject(parent), ip(ip)
{
    socket = new QUdpSocket(this);
}

Server::~Server() {
    delete socket;
}

void Server::slotSendDatagram(QByteArray baDatagram)
{
    // Код для дописывания номера отправляемой датаграммы //
    static uint64_t numOfDatagram = 0;
    numOfDatagram++;

    baDatagram.push_front(QByteArray((char*)&numOfDatagram, sizeof(uint64_t)));

    socket->writeDatagram(baDatagram, QHostAddress(ip), 2424);
    static int i = 0;
    i++;
    ((Widget*)parent())->setSentText(QString::number(i) + " " + QString::number(baDatagram.size()));
}

