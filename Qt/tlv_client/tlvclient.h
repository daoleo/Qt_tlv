#ifndef TLVCLIENT_H
#define TLVCLIENT_H

#include <QObject>
#include <QStringList>

enum TLVDATATYPE{
    CHAT_INFORMATION = 1,
    ROUTING,
    RETRANSMISSION_INFORMATION

};
class QTcpSocket;

class TlvClient : public QObject
{
    Q_OBJECT
public:
    explicit TlvClient(QObject *parent = 0);
    ~TlvClient();
    void netConnect(QString connectIpAddress);
    void sendMessage(QString sendMode, QString sendMessage, QString writeIpAddress, int messageType = CHAT_INFORMATION);
    void readMessage();
    QTcpSocket *tcpClient;
    QStringList userIpStringList;
    QString readInformation;
signals:
    void alreadyInformation(const QString newInformation) const;
    void newUserOnLine(const QString newUserIpAddress) const;
};

#endif // TLVCLIENT_H
