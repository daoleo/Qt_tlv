#ifndef TLVSEVER_H
#define TLVSEVER_H

#include <QObject>
class QTcpServer;
class QTcpSocket;

class tlvSever : public QObject
{
    Q_OBJECT
public:
    explicit tlvSever(QObject *parent = 0);
    ~tlvSever();
    void creatServer();
    void sendMessage(int sendObject);
    void newConnect();
    QString readMessage();


signals:

public slots:

private:
    QList<QTcpSocket *> clientList;
    QTcpServer *tcpServer;
    QTcpSocket *currentTcpClient;
};

#endif // TLVSEVER_H
