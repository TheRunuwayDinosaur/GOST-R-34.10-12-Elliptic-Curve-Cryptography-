#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QtWidgets>
#include "BigInteger.h"
#include "MathWorker.h"
#include "PrimesGenThread.h"
#include "LoadingView.h"
#include "MessengerModel.h"
#include "AddUserView.h"
#include "SelectUsersView.h"
#include "AddChatView.h"

class CMainView : public QFrame{
    Q_OBJECT

public:
    CMainView(QFrame *parent = 0);
    ~CMainView();

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbMessLayout;
    QHBoxLayout *buttonsBox;
   // group boxes
    QGroupBox *gbMess;
   // labels
    QLabel *usersList;
   // buttons, spin boxes...
    QPushButton *pbAddUser;
    QPushButton *pbDeleteUser;
   // other
    CMathWorker *mathWorker;
    CLoadingView *loadingView;
    CBigInteger p;
    CBigInteger q;
    bool pGenerated;
    QVector <CPrimesGeneratorThread*> ths;
    QVector <CBigInteger> bigPrimes;
    CBigInteger ellipticA;
    CBigInteger ellipticB;
    CMessengerModel *messModel;
    QListView *listView;
    CAddUserView *addView;
    CSelectUsersView *selectUsersView;
    CAddChatView *addChatView;
    COpenKeys userOpenKeys;
    QString userName;

private slots:
    void on_listView_clicked(QModelIndex index);
    void on_pbAddUser_clicked();
    void on_pbDeleteUser_clicked();
    void on_add_user(QString userName);
    void on_publish_keys_to_main_view(COpenKeys userOpenKeys,QString userName);
    void on_send_keys_to_users(QModelIndexList users);
    void on_add_new_chat(QString userName);
    void on_chat_choised(QString userNameWith);

};

#endif // MAINVIEW_H
