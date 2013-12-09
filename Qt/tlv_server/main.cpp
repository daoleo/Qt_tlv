#include "mainwindow.h"
#include <QApplication>
#include "tlvpacket.h"
#include <QDebug>
//#include "tlvstruct.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
     QString sss = "123456789";
     QString ss = "987654321";
     QString s;
     QStringList sslist;
     QStringList ssslist;
   /*  sslist<<sss<<ss;
    char ch = '1';
    char wer[40] ;
    char wer2[40];
    char *encodew;
    wer2[0] = '1';
    wer2[1] = 0x00;wer2[2] = 0x00;wer2[3] = 0x00;wer2[4] = 0x09;
    wer2[5] = '9';wer2[6] = '8';wer2[7] = '7';wer2[8] = '6';wer2[9] = '5';
    encodew = tlvEncode(sslist, RETRANSMISSION_INFORMATION);
    //qDebug()<<encodew[5]<<encodew[6]<<encodew[7]<<encodew[8]<<encodew[9];
   /* qDebug()<<encodew[10]<<encodew[11]<<encodew[12]<<encodew[13]<<encodew[14]
            <<encodew[15]<<encodew[16]<<encodew[17]<<encodew[18];
    qDebug()<<encodew[24]<<encodew[25]<<encodew[26]<<encodew[27];
            qDebug()<<encodew[28]<<encodew[29]
            <<encodew[30]<<encodew[31]<<encodew[32]<<encodew[33];
    //qDebug()<<encodew[24]<<encodew[25]<<encodew[26]<<encodew[27];
    tlvDncode(encodew, s, ssslist);
    qDebug()<<s;
    qDebug()<<ssslist.at(0);*/
    /*TlvPacket detlv(ch, sss.toLatin1().data());
    TlvPacket entlv(wer2);
   //qDebug()<<wer2[0];
   // qDebug()<<wer2[1]<<wer2[2]<<wer2[3]<<wer2[4];
    //qDebug()<<wer2[5]<<wer2[6]<<wer2[7]<<wer2[8]<<wer2[9];
    //qDebug()<<wer[5]<<wer[6]<<wer[7]<<wer[8]<<wer[9];
    qDebug()<<detlv.packet()[5]<<detlv.packet()[6]<<detlv.packet()[7];
    //qDebug()<<detlv.packet();
    qDebug()<<entlv.readType();
    qDebug()<<entlv.readLength();
    qDebug()<<entlv.readValue();*/
    return a.exec();
}
