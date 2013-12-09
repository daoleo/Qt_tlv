#-------------------------------------------------
#
# Project created by QtCreator 2013-12-07T18:42:38
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tlv_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tlvclient.cpp

HEADERS  += mainwindow.h \
    tlvpacket.h \
    tlvstruct.h \
    tlvclient.h
