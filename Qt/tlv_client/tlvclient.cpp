#include "tlvclient.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "tlvstruct.h"

TlvClient::TlvClient(QObject *parent) :
    QObject(parent)
{
    tcpClient = new QTcpSocket;
}
void TlvClient::netConnect(QString connectIpAddress)
{
    QHostAddress hostAddress;
    hostAddress.setAddress(connectIpAddress);
    tcpClient->connectToHost(hostAddress, 12000);
    emit newUserOnLine("server");
    connect(tcpClient, &QTcpSocket::readyRead, this, &TlvClient::readMessage);
}

void TlvClient::sendMessage(QString sendMode, QString writeIpAddress, QString sendMessage, int messageType)
{
    if(sendMode == "one_user")
    {
           /* QStringList retransmissionIpAddress;
            char *encodew = tlvEncode(QStringList()<<sendMessage, messageType);
            int type = tlvDecode(encodew, readInformation, retransmissionIpAddress);
               qDebug()<<"0000000"<<encodew[5]<<encodew[6]<<encodew[7]<<encodew[8]<<encodew[9];
               if(type == CHAT_INFORMATION)
               {
                QString ss="QVariant(qba).toString()";
                qDebug()<<ss<<CHAT_INFORMATION<<ROUTING<<RETRANSMISSION_INFORMATION;
               }*/
        char *writepacket;
        //if(writeIpAddress!="server")
        //writeIpAddress = "server";
        /*qDebug()<<writeIpAddress;
        if(writeIpAddress!="server")
        {
            messageType = RETRANSMISSION_INFORMATION;
        }*/
        qDebug()<<"this type"<<messageType;
            writepacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
        //else
           // writepacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
            tcpClient->write(writepacket);

    }
}

void TlvClient::readMessage()
{
    QByteArray qba= tcpClient->readAll(); //读取
    //qDebug()<<"12345678945666";
    //char *encodew = qba.data();
     //qDebug()<<"0000000"<<encodew[5]<<encodew[6]<<encodew[7]<<encodew[8]<<encodew[9];
    //QString ss=QVariant(qba).toString();
    QStringList retransmissionIpAddress;
    int packetType = tlvDecode(qba.data(), readInformation, retransmissionIpAddress);//
    if(packetType == ROUTING)
        emit newUserOnLine(retransmissionIpAddress.at(0));
    else{
        emit alreadyInformation(retransmissionIpAddress.at(0)+":");
        emit alreadyInformation(readInformation+"\n");
    }
        //qDebug()<<retransmissionIpAddress.at(retransmissionIpAddress.size()-1);

       //qDebug()<<readInformation;

     //   sendMessage(QString("one_user"), retransmissionIpAddress.at(0), readInformation);
    //qDebug()<<ss;
}
TlvClient::~TlvClient()
{

}
