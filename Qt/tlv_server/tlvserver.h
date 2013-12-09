#ifndef TLVSEVER_H
#define TLVSEVER_H

#include <QObject>
#include <QStringList>

enum TLVDATATYPE{
    CHAT_INFORMATION = 1,
    ROUTING,
    RETRANSMISSION_INFORMATION

};

class QTcpServer;
class QTcpSocket;

class TlvServer : public QObject
{
    Q_OBJECT
public:
    explicit TlvServer(QObject *parent = 0);
    ~TlvServer();
    void creatServer();
    void sendMessage(QString sendMode, QString sendMessage, QString writeIpAddress, int messageType = CHAT_INFORMATION);
    void readMessage();
    void newConnect();
    QTcpServer *tcpServer;
    QTcpSocket *currentTcpClient;

signals:
    void newConnectAlready(const QString newUserIpAddress) const;
    void alreadyInformation(const QString newInformation) const;
public slots:

private:
    QList<QTcpSocket *> clientList;
    QStringList clientIpStringList;
    QString readInformation;
};

#endif // TLVSEVER_H
