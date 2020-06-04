#include "client.h"
#include "widget.h"


Client::Client(QString ip, QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    qDebug() << socket->bind(QHostAddress::Any, 2424); // ip!

    connect(socket, SIGNAL(readyRead()), SLOT(slotProcessDatagrams()));
}

Client::~Client() {
    delete socket;
}

void Client::slotProcessDatagrams()
{
    QByteArray baDatagram;
    static int i = 0;
    do {
        baDatagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(baDatagram.data(), baDatagram.size());
        const uint64_t & num = ((uint64_t*)baDatagram.data())[0];
        if (num < i) continue;
        i = num;
        ((Widget*)parent())->setReceivedText(QString::number(num) + " " + QString::number(baDatagram.size()));
        emit datagramReceived(QByteArray(baDatagram.data() + sizeof(uint64_t), baDatagram.size() - sizeof(uint64_t)));
    } while(socket->hasPendingDatagrams());

    // озвучивание датаграммы
}
