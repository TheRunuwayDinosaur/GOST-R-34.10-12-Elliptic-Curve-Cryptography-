#ifndef ADDCHATVIEW_H
#define ADDCHATVIEW_H

#include <QObject>
#include <QtWidgets>
#include "MessengerModel.h"

class CAddChatView : public QFrame{
    Q_OBJECT

public:
    CAddChatView(CMessengerModel *messModel_,QWidget *parent = 0);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbUsersLayout;
    QHBoxLayout *buttonsBox;
   // group boxes
    QGroupBox *gbUsers;
   // buttons, spin boxes
    QPushButton *pbChoise;
   // other
    QListView *listView;
    CMessengerModel *messModel;

private slots:
    void on_pbChoise_clicked();

signals:
    void chat_choised(QString userNameWith);

};

#endif // ADDCHATVIEW_H
