#include "mainwindow.h"
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QListWidget>
#include "tlvserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chatTextEdit = new QTextEdit;
    sendTextEdit = new QTextEdit(tr("123456789"));
    sortLineEdit = new QLineEdit(tr("12000"));
    sendButton = new QPushButton(tr("Send"));
    sendModeComboBox = new QComboBox;
    userListWidget = new QListWidget;
    tlvServer = new TlvServer;
    QStringList sendModeList;
    sendModeList<<"one_user"<<"all_user";
    //userListWidget->addItems(sendModeList);
    sendModeComboBox->addItems(sendModeList);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("Sort:")), sortLineEdit);
    hBoxLayout->addWidget(sendModeComboBox);
    hBoxLayout->addWidget(sendButton);
    gridLayout->addLayout(formLayout, 0, 0);
    gridLayout->addWidget(chatTextEdit, 1, 0);
    gridLayout->addWidget(sendTextEdit, 2, 0);
    gridLayout->addLayout(hBoxLayout, 3, 0);
    gridLayout->addWidget(userListWidget, 0, 2, 4, 1);
    gridLayout->setColumnStretch(0, 20);
    gridLayout->setColumnStretch(2, 10);
    gridLayout->setRowStretch(1, 20);
    gridLayout->setRowStretch(3, 10);
    QWidget *widget = new QWidget;
    widget->setLayout(gridLayout);
    setCentralWidget(widget);
    tlvServer->creatServer();
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
    connect(userListWidget, &QListWidget::currentTextChanged, this, &MainWindow::sendUserIpChanged);
    connect(tlvServer->tcpServer, &QTcpServer::newConnection, tlvServer, &TlvServer::newConnect);
    connect(tlvServer, &TlvServer::newConnectAlready, this, &MainWindow::updateUserList);
    connect(tlvServer, &TlvServer::alreadyInformation, this, &MainWindow::updateChatText);
}

void MainWindow::onSendButtonClicked()
{
   //emit tlvServer->newConnectAlready(QString("newUserIpAddress"));
    tlvServer->sendMessage(sendModeComboBox->currentText(), sendUserIp, sendTextEdit->toPlainText(), CHAT_INFORMATION);
    //tlvServer->sendMessage(sendModeComboBox->currentText(), "127.0.0.1", ROUTING, sendUserIp);
    //tlvServer->sendMessage(sendModeComboBox->currentText(), sendTextEdit->toPlainText(), sendUserIp, RETRANSMISSION_INFORMATION);
}

void MainWindow::updateUserList(QString newUserIpAddress)
{
    sendUserIp = newUserIpAddress;
    userListWidget->addItem(newUserIpAddress);
}

void  MainWindow::updateChatText(QString newInformation)
{
    chatTextEdit->insertPlainText(newInformation+"\n");
}

void MainWindow::sendUserIpChanged(QString currentuserIp)
{
    sendUserIp = currentuserIp;
    //qDebug()<<sendUserIp;
}

MainWindow::~MainWindow()
{

}
