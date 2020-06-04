#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QString ip, QObject *parent = nullptr);
    ~Server();

signals:

public slots:
    void slotSendDatagram(QByteArray baDatagram);

private:
    QUdpSocket * socket;
    QString ip;
};

#endif // SERVER_H
