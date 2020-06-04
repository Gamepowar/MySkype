#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString ip, QObject *parent = nullptr);
    ~Client();

signals:
    void datagramReceived(QByteArray baDatagram);

public slots:
    void slotProcessDatagrams();

private:
    QUdpSocket * socket;
};

#endif // CLIENT_H
