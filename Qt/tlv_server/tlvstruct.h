#ifndef TLVSTRUCT_H
#define TLVSTRUCT_H
#include "tlvpacket.h"
    char * tlvEncode(QStringList writeMessage, int dataType)
    {
        TlvPacket *tlvPacket;
        /*if(dataType == CHAT_INFORMATION)
        {
            tlvPacket = new TlvPacket(CHAT_INFORMATION, writeMessage.at(0).toLatin1().data(), writeMessage.at(0).size());
        }else*/ if(dataType == ROUTING)
        {
            tlvPacket = new TlvPacket(ROUTING, writeMessage.at(0).toLatin1().data(), writeMessage.at(0).size());
        }else //if(dataType == RETRANSMISSION_INFORMATION)
        {
            tlvPacket = new TlvPacket(dataType,
                                      writeMessage.at(0).size()+writeMessage.at(1).size());
            tlvPacket->writeType(ROUTING);
            tlvPacket->writeLength(writeMessage.at(0).size());
            tlvPacket->writeValue(writeMessage.at(0).toLatin1().data(), writeMessage.at(0).size());
            tlvPacket->writeType(CHAT_INFORMATION);
            tlvPacket->writeLength(writeMessage.at(1).size());
            tlvPacket->writeValue(writeMessage.at(1).toLatin1().data(), writeMessage.at(1).size());
        }
        return tlvPacket->packet();
    }

    int tlvDecode(char *readMessage, QString &chatInformation,
                    QStringList &routingList)
    {
        int packetType;
        TlvPacket *tlvPacket = new TlvPacket(readMessage);
        switch (tlvPacket->readType())
        {
            case CHAT_INFORMATION:
                qDebug()<<tlvPacket->readLength();
                tlvPacket->readType();
                qDebug()<<tlvPacket->readLength();
                routingList.append(tlvPacket->readValue());
                tlvPacket->readType();
                qDebug()<<tlvPacket->readLength();
                chatInformation = tlvPacket->readValue();
                packetType = CHAT_INFORMATION;
                //qDebug()<<chatInformation = new QString(tlvPacket->readValue());
                break;
            case ROUTING:
                qDebug()<<tlvPacket->readLength();
                routingList<<tlvPacket->readValue();
                packetType = ROUTING;
                //routingList->append(QString(tlvPacket->readValue()));
                break;
            case RETRANSMISSION_INFORMATION:
                qDebug()<<tlvPacket->readLength();
                tlvPacket->readType();
                qDebug()<<tlvPacket->readLength();
                routingList.append(tlvPacket->readValue());
                tlvPacket->readType();
                qDebug()<<tlvPacket->readLength();
                chatInformation = tlvPacket->readValue();
                packetType = RETRANSMISSION_INFORMATION;
                break;
            default:
                packetType = NULL;
                break;
        }
        /*if(tlvPacket->readType() == CHAT_INFORMATION)
        {
            qDebug()<<tlvPacket->readLength();
            qDebug()<<tlvPacket->readValue();
        }else if(tlvPacket->getTlvType() == ROUTING)
        {
            qDebug()<<tlvPacket->readLength();
            qDebug()<<tlvPacket->readValue();
        }else if(tlvPacket->getTlvType() == RETRANSMISSION_INFORMATION)
        {
            qDebug()<<tlvPacket->readLength();
            qDebug()<<tlvPacket->readType();
            qDebug()<<tlvPacket->readLength();
            qDebug()<<tlvPacket->readValue();
            qDebug()<<tlvPacket->readType();
            qDebug()<<tlvPacket->readLength();
            qDebug()<<tlvPacket->readValue();
        }*/
        return packetType;
    }
#endif // TLVSTRUCT_H
