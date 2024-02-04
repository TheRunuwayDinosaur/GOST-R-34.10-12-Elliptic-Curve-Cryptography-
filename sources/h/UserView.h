#ifndef USERVIEW_H
#define USERVIEW_H

#include <QObject>
#include <QtWidgets>
#include "EllipticPoint.h"
#include "MathWorker.h"
#include "KeysView.h"
#include "UsersWithKeysView.h"
#include "ChatsView.h"
#pragma once

class CUserView : public QFrame{
    Q_OBJECT

public:
    CUserView(const QString &name = "",QWidget *parent = 0);
    ~CUserView();
    void set_name(const QString &name);
    void add_user_keys(const QString &userName,const COpenKeys &key);
    void delete_user_keys(const QString &userName);
    void set_keys_enabled() const;
    QString get_name() const;
    void new_chat(const QString &userNameTo);
    void add_message(const QString &message,const QString &userTo,
                     std::pair <CBigInteger,CBigInteger> &digitalSignature);
    bool find_chat(const QString &userName);
    void delete_chat(const QString &userTo);
    void delete_all_chats() const;

private:
   // v,h boxes
    QVBoxLayout *mainBox;
   // tabs
    QTabWidget *tabs;
   // other
    QString userName;
    CKeysView *keysView;
    CUsersWithKeysView *usersWithKeysView;
    CChatsView *chatsView;
    QMap <QString,COpenKeys> userKeys;
    CCloseKeys closeKeys;

private slots:
    void on_publish_keys_to_user(COpenKeys userOpenKeys);
    void on_add_new_chat();
    void on_need_delete_chat(QString userFrom,QString userTo);
    void on_send_message(QString message,QString userFrom,QString userTo,
                         std::pair <CBigInteger,CBigInteger> digitalSignature);
    void on_close_keys_generated();

signals:
    void publish_keys_to_mess_model(COpenKeys userOpenKeys,QString userName);
    void add_new_chat(QString userName);
    void need_delete_chat(QString userFrom,QString userTo);
    void send_message(QString message,QString userFrom,QString userTo,
                      std::pair <CBigInteger,CBigInteger> digitalSignature);

};

#endif // USERVIEW_H
