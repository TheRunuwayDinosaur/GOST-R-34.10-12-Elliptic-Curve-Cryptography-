#ifndef CHATSVIEW_H
#define CHATSVIEW_H

#include <QObject>
#include <QtWidgets>
#include "ChatWithUserView.h"
#include "OpenKeys.h"
#include "CloseKeys.h"
#pragma once

class CChatsView : public QFrame{
    Q_OBJECT

public:
    CChatsView(QWidget *parent = 0);
    ~CChatsView();
    void set_user_name(const QString &userName_);
    void set_close_keys(const CCloseKeys &closeKeys_);
    void add_new_chat(const QString &userNameTo);
    void add_message(const QString &message,const QString &userTo,
                     std::pair <CBigInteger,CBigInteger> &digitalSignature);
    void add_user_keys(const QString &userName,const COpenKeys &key);
    void delete_chat(const QString &userTo);
    void delete_all_chats();
    void delete_user_keys(const QString &userName);
    bool find_chat(const QString &userName);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbChatsLayout;
    QHBoxLayout *buttonsBox;
   // group boxes
    QGroupBox *gbChats;
   // buttons, spin boxes
    QPushButton *pbAddNewChat;
    QPushButton *pbDeleteChat;
   // other
    COpenKeys openKeys;
    QString userName;
    QListWidget *namesChatsList;
    QVector <CChatWithUserView*> chats;
    CCloseKeys closeKeys;

private slots:
    void on_pbAddNewChat_clicked();
    void on_pbDeleteChat_clicked();
    void on_chats_clicked(QModelIndex index);
    void on_send_message(QString message,QString userTo,
                         std::pair <CBigInteger,CBigInteger> digitalSignature);

signals:
    void need_add_new_chat();
    void send_message(QString message,QString userFrom,QString userTo,
                      std::pair <CBigInteger,CBigInteger> digitalSignature);
    void need_delete_chat(QString userFrom,QString userTo);

};

#endif // CHATSVIEW_H
