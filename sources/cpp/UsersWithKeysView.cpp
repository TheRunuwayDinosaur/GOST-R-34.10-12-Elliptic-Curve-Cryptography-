#include "UsersWithKeysView.h"

CUsersWithKeysView::CUsersWithKeysView(QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    gbUsersLayout = new QVBoxLayout();
    gbUsers = new QGroupBox("Пользователи");
    gbUsers->setStyleSheet("QGroupBox{"
                           "font: bold;"
                           "color: purple;"
                           "border: 1px solid silver;"
                           "border-radius: 30px;"
                           "margin-top: 6px; }"
                           "QGroupBox::title{"
                           "subcontrol-origin: margin;"
                           "left: 7px;"
                           "padding: 0px 5px 0px 5px;}");
    gbUsers->setFont(QFont("Times",10));
    list = new QListWidget();
    list->setFont(QFont("Times",10));
    list->setStyleSheet("font: bold");
    gbUsersLayout->addWidget(list);
    gbUsers->setLayout(gbUsersLayout);
    mainBox->addWidget(gbUsers);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->resize(600,590);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
}

void CUsersWithKeysView::add_user_keys(const QString &userName, const COpenKeys &keys){
    userKeys[userName] = keys;
    this->update_list();
}

void CUsersWithKeysView::delete_user_keys(const QString &userName){
    userKeys.remove(userName);
    this->update_list();
}

void CUsersWithKeysView::update_list(){
    list->clear();
    list->setFont(QFont("Times",10));
    for (auto iter = userKeys.begin(); iter != userKeys.end();iter++){
        QString userName = iter.key();
        CBigInteger q = iter.value().get_q();
        CEllipticPoint ellipticP = iter.value().get_ellipticP();
        CEllipticPoint ellipticQ = iter.value().get_ellipticQ();
        QString userInfo = QString("%1:\n"
                           "q = %2\n"
                           "P{} = {%3;%4}\n"
                           "Q{} = {%5;%6}").arg(userName).arg(q.get_number()).arg(ellipticP.get_x().get_number()).arg(ellipticP.get_y().get_number()).arg(ellipticQ.get_x().get_number()).arg(ellipticQ.get_y().get_number());
        list->addItem(userInfo);
    }
}
