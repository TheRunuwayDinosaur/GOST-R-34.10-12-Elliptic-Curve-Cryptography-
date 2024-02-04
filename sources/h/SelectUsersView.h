#ifndef SELECTUSERSVIEW_H
#define SELECTUSERSVIEW_H

#include <QObject>
#include <QtWidgets>
#include "MessengerModel.h"
#pragma once

class CSelectUsersView : public QFrame{
    Q_OBJECT

public:
    CSelectUsersView(CMessengerModel *messModel_,QWidget *parent = 0);
    void set_openKey(COpenKeys key);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbUsersLayout;
    QHBoxLayout *buttonsBox;
   // group boxes
    QGroupBox *gbUsers;
   // buttons, spin boxes...
    QPushButton *pbChoise;
   // other
    QListView *listView;
    CMessengerModel *messModel;
    COpenKeys openKey;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_pbChoise_clicked();

signals:
    void send_keys_to_users(QModelIndexList users);

};

#endif // SELECTUSERSVIEW_H
