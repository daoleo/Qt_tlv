#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T10:20:39
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tlv_server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tlvserver.cpp

HEADERS  += mainwindow.h \
    tlvpacket.h \
    tlvstruct.h \
    tlvserver.h
