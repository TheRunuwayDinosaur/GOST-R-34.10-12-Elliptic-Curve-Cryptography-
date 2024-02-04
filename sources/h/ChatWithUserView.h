#ifndef CHATWITHUSERVIEW_H
#define CHATWITHUSERVIEW_H

#include <QObject>
#include <QtWidgets>
#include "StreebogMain.h"
#include "OpenKeys.h"
#include "CloseKeys.h"
#include "UpgradeListWidget.h"
#include "MathWorker.h"

class CChatWithUserView : public QFrame{
    Q_OBJECT

public:
    CChatWithUserView(const QString &userNameFrom,QWidget *parent = 0);
    ~CChatWithUserView();
    void set_user_name_from(const QString &userNameFrom_);
    void set_user_name_to(const QString &userNameTo_);
    void set_close_keys(const CCloseKeys &closeKeys_);
    void update_close_keys(const CCloseKeys &closeKeys_);
    QString get_user_name_to() const;
    void add_new_message(const QString &userNameFrom,const QString &message,
                         std::pair <CBigInteger,CBigInteger> &digitalSignature);
    void add_user_keys(const QString &userName,const COpenKeys &key);
    void delete_user_keys(const QString &userName);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QVBoxLayout *gbMessagesLayout;
    QHBoxLayout *buttonsBox;
   // group boxes
    QGroupBox *gbMessages;
   // labels
    QLabel *lbMessage;
    QLabel *lbHash;
   // line, text edits
    QTextEdit *teMessage;
    QTextEdit *teHash;
   // buttons, spin boxes..
    QPushButton *pbSendMessage;
   // other
    CUpgradeListWidget *messagesList;
    QMenu *menu;
    QAction *actionCheckHash;
    QAction *actionCheckDigitalSignature;
    QString userNameFrom;
    QString userNameTo;
    CStreebogMain *hashFunction;
    QMap <QString,COpenKeys> userKeys;
    CCloseKeys closeKeys;
    CMathWorker *mathWorker;
    QVector < std::pair <CBigInteger,CBigInteger> > messagesDigitalSignature;
private slots:
    void on_pbSendMessage_clicked();
    void on_actionCheckHash_triggered();
    void on_actionCheckDigitalSignature_triggered();
    void on_rightButtonClicked(int X,int Y);

signals:
    void send_message(QString message,QString userTo,std::pair <CBigInteger,CBigInteger> digitalSignature);

};

#endif // CHATWITHUSERVIEW_H
