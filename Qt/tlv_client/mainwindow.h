#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QComboBox;
class QTextEdit;
class QPushButton;
class QListWidget;
class TlvClient;
class QLineEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void onSendButtonClicked();
    void updateUserList(const QString newUserIpAddress) const;
    void sendUserIpChanged(QString currentuserIp);
    void updateChatText(QString newInformation);
    void onNetConnectButtonClicked();
    QComboBox *sendModeComboBox;
    QTextEdit *chatTextEdit;
    QTextEdit *sendTextEdit;
    QLineEdit *sortLineEdit;
    QLineEdit *ipLineEdit;
    QPushButton *sendButton;
    QPushButton *netConnectButton;
    QListWidget *userListWidget;
    QString sendUserIp;
    TlvClient *tlvClient;
};

#endif // MAINWINDOW_H
