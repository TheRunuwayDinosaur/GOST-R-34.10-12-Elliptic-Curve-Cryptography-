#ifndef USERSWITHKEYSVIEW_H
#define USERSWITHKEYSVIEW_H

#include <QObject>
#include <QtWidgets>
#include "OpenKeys.h"
#pragma once

class CUsersWithKeysView : public QFrame{
    Q_OBJECT

public:
    CUsersWithKeysView(QWidget *parent = 0);
    void add_user_keys(const QString &userName,const COpenKeys &keys);
    void delete_user_keys(const QString &userName);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbUsersLayout;
   // group boxes
    QGroupBox *gbUsers;
   // other
    QListWidget *list;
    QMap <QString,COpenKeys> userKeys;
   // methods
    void update_list();

};

#endif // USERSWITHKEYSVIEW_H
