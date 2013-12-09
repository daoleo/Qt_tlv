#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QComboBox;
class QTextEdit;
class QPushButton;
class QListWidget;
class TlvServer;
class QLineEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void onSendButtonClicked();
    void updateUserList(QString newUserIpAddress);
    void sendUserIpChanged(QString currentuserIp);
    void updateChatText(QString newInformation);
    QComboBox *sendModeComboBox;
    QTextEdit *chatTextEdit;
    QTextEdit *sendTextEdit;
    QLineEdit *sortLineEdit;
    QPushButton *sendButton;
    QListWidget *userListWidget;
    QString sendUserIp;
    TlvServer *tlvServer;
};

#endif // MAINWINDOW_H
