#include "mainwindow.h"
#include <QCoreApplication>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QListWidget>
#include "tlvclient.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chatTextEdit = new QTextEdit;
    sendTextEdit = new QTextEdit(tr("123456789"));
    ipLineEdit = new QLineEdit(tr("127.0.0.1"));
    //sortLineEdit = new QLineEdit(tr("12000"));
    sendButton = new QPushButton(tr("Send"));
    netConnectButton = new QPushButton(tr("Connect"));
    sendModeComboBox = new QComboBox;
    userListWidget = new QListWidget;
    tlvClient = new TlvClient;
    QStringList sendModeList;
    sendModeList<<"one_user"<<"all_user";
    //userListWidget->addItems(sendModeList);
    sendModeComboBox->addItems(sendModeList);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QHBoxLayout *ipSetLayout = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("IP_Address:")), ipLineEdit);
    ipSetLayout->addLayout(formLayout);
    ipSetLayout->addWidget(netConnectButton);
    hBoxLayout->addWidget(sendModeComboBox);
    hBoxLayout->addWidget(sendButton);
    gridLayout->addLayout(ipSetLayout, 0, 0, 1, 2);
    gridLayout->addWidget(chatTextEdit, 1, 0);
    gridLayout->addWidget(sendTextEdit, 2, 0);
    gridLayout->addLayout(hBoxLayout, 3, 0);
    gridLayout->addWidget(userListWidget, 1, 1, 3, 1);
    gridLayout->setColumnStretch(0, 20);
    gridLayout->setColumnStretch(1, 10);
    gridLayout->setRowStretch(1, 20);
    gridLayout->setRowStretch(2, 10);
    QWidget *widget = new QWidget;
    widget->setLayout(gridLayout);
    setCentralWidget(widget);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
     connect(netConnectButton, &QPushButton::clicked, this, &MainWindow::onNetConnectButtonClicked);
    connect(userListWidget, &QListWidget::currentTextChanged, this, &MainWindow::sendUserIpChanged);
     connect(tlvClient, &TlvClient::alreadyInformation, this, &MainWindow::updateChatText);
     connect(tlvClient, &TlvClient::newUserOnLine, this, &MainWindow::updateUserList);
}

void MainWindow::onSendButtonClicked()
{
    if(sendModeComboBox->currentText()!="server")
        tlvClient->sendMessage(sendModeComboBox->currentText(), sendUserIp, sendTextEdit->toPlainText(), RETRANSMISSION_INFORMATION);
    else
        tlvClient->sendMessage(sendModeComboBox->currentText(), sendUserIp, sendTextEdit->toPlainText());
    QTime time;time.start();
    while(time.elapsed()<50)
        QCoreApplication::processEvents();
}
void MainWindow::onNetConnectButtonClicked()
{
    sendUserIp = ipLineEdit->text();
    tlvClient->netConnect(sendUserIp);
}

void MainWindow::updateUserList(const QString newUserIpAddress)const
{
    userListWidget->addItem(newUserIpAddress);
}

void  MainWindow::updateChatText(QString newInformation)
{
    chatTextEdit->insertPlainText(newInformation+"\n");
}

void MainWindow::sendUserIpChanged(QString currentuserIp)
{
    sendUserIp = currentuserIp;
}

MainWindow::~MainWindow()
{

}
