#include "tlvsever.h"
#include <QTcpServer>
#include <QTcpSocket>

tlvSever::tlvSever(QObject *parent) :
    QObject(parent)
{
}

void tlvSever::creatServer()
{
    tcpServer = new QTcpServer;
    tcpServer->listen(QHostAddress::LocalHost, 2000);
}

void tlvSever::newConnect()
{
    clientList<<tcpServer->nextPendingConnection();
    currentTcpClient = clientList.at(clientList.size()-1);
    connect(currentTcpClient, &QTcpSocket::readyRead, this, &tlvSever::readMessage);
    //connect(clientList.at(clientList.size()-1), &QTcpSocket::readyRead, {qDebug()<<"123"});
    //connect(currentTcpClient , SIGNAL(readyRead(int)), this, SLOT(readMessage(int)));
}

void tlvSever::sendMessage(int sendObject)
{

}

QString tlvSever::readMessage()
{
    QByteArray qba= currentTcpClient->readAll(); //读取
    QString ss=QVariant(qba).toString();
    qDebug()<<ss;
    return ss;
}

tlvSever::~tlvSever()
{

}
