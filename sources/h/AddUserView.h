#ifndef ADDUSERVIEW_H
#define ADDUSERVIEW_H

#include <QObject>
#include <QtWidgets>
#include "UserView.h"
#include "MessengerModel.h"

class CAddUserView : public QFrame{
    Q_OBJECT

public:
    CAddUserView(QWidget *parent = 0);
    void set_users(CMessengerModel *messModel_);

private:
   // v,h boxes
    QVBoxLayout *mainBox;
    QHBoxLayout *buttonsBox;
   // labels
    QLabel *lbUserName;
   // line edits
    QTextEdit *leUserName;
   // buttons, spin boxes...
    QPushButton *pbAdd;
   // other
    bool wasSendSignal;
    CMessengerModel *messModel;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_pbAdd_clicked();

signals:
    void add_user(QString userName);

};

#endif // ADDUSERVIEW_H
