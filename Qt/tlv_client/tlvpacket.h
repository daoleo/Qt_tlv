#ifndef TLVPACKET_H
#define TLVPACKET_H
#include <QString>

class TlvPacket
{
public:
    TlvPacket(char type, char *value, int valueLength)
        :tlvType(type), tlvValue(value), tlvLength(valueLength)
    {
        indexValidTlvPacketEnd = 0;
        tlvWritePacket = new char[sizeof(type)+sizeof(int)+valueLength];
         writeType(tlvType);
         writeLength(tlvLength);
         writeValue(tlvValue, tlvLength);
    }

    TlvPacket(char type, int valueLength)
        :tlvType(type), tlvLength(valueLength)
    {
        indexValidTlvPacketEnd = 0;
        tlvWritePacket = new char[sizeof(type)+sizeof(int)+valueLength];
        writeType(tlvType);
        writeLength(tlvLength);
    }

    TlvPacket(char *packet):tlvReadPacket(packet)
    {
        indexReadTlvPacketEnd = 0;
    }

    void writeType(char Type)
    {
        tlvWritePacket[indexValidTlvPacketEnd] = Type;
        indexValidTlvPacketEnd++;
    }

    void writeLength(int valueLength)
    {
        char decomposeInt[4];
        valueLength +=16843009;
        decomposeInt[0] = ((valueLength&0xFF000000)>>24);
        decomposeInt[1] = ((valueLength&0x00FF0000)>>16);
        decomposeInt[2] = ((valueLength&0x0000FF00)>>8);
        decomposeInt[3] = (valueLength&0x000000FF);
        for(int indexDecompose = 0;indexDecompose < 4; indexDecompose++)
        {
            tlvWritePacket[indexValidTlvPacketEnd] = decomposeInt[indexDecompose];
            indexValidTlvPacketEnd++;
        }
    }

    void writeValue(char *value, int valueLength)
    {
        for(int indexValue = 0; indexValue < valueLength; indexValue++)
        {
            tlvWritePacket[indexValidTlvPacketEnd] = value[indexValue];
            indexValidTlvPacketEnd++;
        }
    }

    char * packet()
    {
        return tlvWritePacket;
    }

    char getTlvType(){
        return tlvType;
    }

    char readType()
    {
        tlvType = tlvReadPacket[indexReadTlvPacketEnd];
        indexReadTlvPacketEnd++;
        return tlvType;
    }

    int readLength()
    {
        tlvLength = tlvReadPacket[indexReadTlvPacketEnd++]&0xFF;tlvLength = tlvLength<<8;
        tlvLength += tlvReadPacket[indexReadTlvPacketEnd++]&0xFF;tlvLength = tlvLength<<8;
        tlvLength += tlvReadPacket[indexReadTlvPacketEnd++]&0xFF;tlvLength = tlvLength<<8;
        tlvLength += tlvReadPacket[indexReadTlvPacketEnd++]&0xFF;
        tlvLength -= 16843009;
        return tlvLength;
    }

    char *readValue()
    {
        tlvValue = new char[tlvLength+1];
        for(int indexTlvValue = 0;
            indexTlvValue < tlvLength;
            indexReadTlvPacketEnd++, indexTlvValue++)
        {
            tlvValue[indexTlvValue] = tlvReadPacket[indexReadTlvPacketEnd];
        }
        tlvValue[tlvLength]='\0';
        return tlvValue;
    }

private:
    char tlvType;
    int tlvLength;
    char *tlvValue;
    int indexValidTlvPacketEnd;
    int indexReadTlvPacketEnd;
    char *tlvWritePacket;
    char *tlvReadPacket;
};

#endif // TLVPACKET_H
