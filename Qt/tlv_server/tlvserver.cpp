#include "tlvserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QStringList>
#include <QTime>
#include "tlvstruct.h"
#include <QCoreApplication>

TlvServer::TlvServer(QObject *parent) :
    QObject(parent)
{
}

void TlvServer::creatServer()
{
    tcpServer = new QTcpServer;
    tcpServer->listen(QHostAddress::LocalHost, 12000);
}

void TlvServer::newConnect()
{
    currentTcpClient = tcpServer->nextPendingConnection();
    QString newUserIpAddress = currentTcpClient->peerAddress().toString();
    if(clientList.size()>0)
    {
        qDebug()<<"all_User"<<currentTcpClient->peerAddress().toString()<<clientIpStringList.at(clientList.size()-1);
        if(newUserIpAddress == "127.0.0.1")
        {
            int localMachineNum = 0;
            for(int indexClientList = 0; indexClientList < clientList.size(); indexClientList++)
            {
                //qDebug()<<"all_User"<<clientIpStringList.at(indexClientList);//
                char *writepacket = tlvEncode(QStringList()<<clientIpStringList.at(indexClientList)<<"", ROUTING);
                currentTcpClient->write(writepacket);
                QTime time;time.start();
                while(time.elapsed()<50)
                    QCoreApplication::processEvents();
                //qDebug()<<"all_User"<<"11111111";
                if(clientList.at(indexClientList)->peerAddress().toString().mid(0, 9) == "127.0.0.1")
                    localMachineNum++;
            }
            //char *writepacket = tlvEncode(QStringList()<<clientIpStringList.at(clientList.size()-1)<<"", ROUTING);
            //currentTcpClient->write(writepacket);
            newUserIpAddress = newUserIpAddress + "." + QString::number(localMachineNum);
        }
        sendMessage("all_user", newUserIpAddress,"", ROUTING);
    }else if(newUserIpAddress == "127.0.0.1")
        newUserIpAddress += ".0";
   /**/ clientList<<currentTcpClient;
    //currentTcpClient = clientList.at(clientList.size()-1);
    //qDebug()<<currentTcpClient->peerAddress().toString();
    clientIpStringList<<newUserIpAddress;
    connect(currentTcpClient, &QTcpSocket::readyRead, this, &TlvServer::readMessage);
    emit newConnectAlready(newUserIpAddress);
    //connect(clientList.at(clientList.size()-1), &QTcpSocket::readyRead, {qDebug()<<"123"});
    //connect(currentTcpClient , SIGNAL(readyRead(int)), this, SLOT(readMessage(int)));
}

void TlvServer::sendMessage(QString sendMode, QString writeIpAddress,
                            QString sendMessage, int messageType)
{
    if(sendMode == "one_user")
    {
        int indexClientList = clientList.size()-1;
        while (indexClientList >= 0)
        {
            if(writeIpAddress.mid(0, 9) == "127.0.0.1")
            {
                if(writeIpAddress.split(".").size()<=4)
                {
                    char *writepacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
                    clientList.at(indexClientList)->write(writepacket);
                    break;
                }
                 QStringList ipAddressDecompose = writeIpAddress.split(".");
                 char *writepacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
                 clientList.at(ipAddressDecompose.at(4).toInt())->write(writepacket);
                 break;
            }else if(clientList.at(indexClientList)->peerAddress().toString() == writeIpAddress)
            {
                //QByteArray     tlvEncode(QStringList()<<sendMessage)

                //char *encodew = tlvEncode(QStringList()<<sendMessage, messageType);
                //qDebug()<<encodew[5]<<encodew[6]<<encodew[7]<<encodew[8]<<encodew[9];
              /* encodew[0]=1;// //
                encodew[1]=1;encodew[2]=1;
                encodew[3]=1;encodew[4]=1;
                if(messageType == CHAT_INFORMATION||messageType == ROUTING)
                    clientList.at(indexClientList)->write(tlvEncode(QStringList()<<sendMessage, messageType));
                else if(messageType == RETRANSMISSION_INFORMATION)*/
                char *writepacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
                //char *writepacket = tlvEncode(QStringList()<<sendMessage, ROUTING);
                clientList.at(indexClientList)->write(writepacket);
                break;
            }
            indexClientList--;
        }
    }else if(sendMode == "all_user")
    {
        int indexClientList = clientList.size()-1;
        while (indexClientList >= 0) {
            char *sendTlvPacket = tlvEncode(QStringList()<<writeIpAddress<<sendMessage, messageType);
            clientList.at(indexClientList)->write(sendTlvPacket);
            indexClientList--;
        }
    }
    QTime time;time.start();
    while(time.elapsed()<50)
        QCoreApplication::processEvents();
}

void TlvServer::readMessage()
{
    QByteArray qba= currentTcpClient->readAll(); //读取
    qDebug()<<"12345678945666";
    char *encodew = qba.data();
     //qDebug()<<"0000000"<<encodew[5]<<encodew[6]<<encodew[7]<<encodew[8]<<encodew[9];
     //if(encodew[0] == )
    //QString ss=QVariant(qba).toString();
    //qDebug()<<ss;
    QStringList retransmissionIpAddress;
    int packeType = tlvDecode(qba.data(), readInformation, retransmissionIpAddress);//
    if(packeType == RETRANSMISSION_INFORMATION)
        sendMessage("one_user", retransmissionIpAddress.at(0), readInformation);
    else if(packeType == CHAT_INFORMATION)
    {
        emit alreadyInformation(currentTcpClient->peerAddress().toString());
        emit alreadyInformation(readInformation+"\n");
        //qDebug()<<retransmissionIpAddress.at(0);
        //qDebug()<<readInformation;
    }
}

TlvServer::~TlvServer()
{

}
