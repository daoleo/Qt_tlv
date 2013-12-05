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

signals:

public slots:

private:
    QList<QTcpSocket> clientList;
};

#endif // TLVSEVER_H
