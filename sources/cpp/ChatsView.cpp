#include "ChatsView.h"

CChatsView::CChatsView(QWidget *parent) : QFrame(parent){
    mainBox = new QVBoxLayout();
    gbChatsLayout = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    gbChats = new QGroupBox("Список чатов");
    gbChats->setStyleSheet("QGroupBox{"
                           "font: bold;"
                           "color: purple;"
                           "border: 1px solid silver;"
                           "border-radius: 30px;"
                           "margin-top: 6px; }"
                           "QGroupBox::title{"
                           "subcontrol-origin: margin;"
                           "left: 7px;"
                           "padding: 0px 5px 0px 5px;}");
    gbChats->setFont(QFont("Times",10));
    pbAddNewChat = new QPushButton("Новый чат");
    pbAddNewChat->setStyleSheet("QPushButton{"
                                 "border: none;"
                                 "color: white;"
                                 "font: bold;"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                                 "border-radius: 15px}"
                                 "QPushButton:hover{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                                 "QPushButton:pressed{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbAddNewChat->setFixedSize(250,50);
    pbAddNewChat->setFont(QFont("Times",10));
    pbDeleteChat = new QPushButton("Удалить чат");
    pbDeleteChat->setStyleSheet("QPushButton{"
                                 "border: none;"
                                 "color: white;"
                                 "font: bold;"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                                 "border-radius: 15px}"
                                 "QPushButton:hover{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                                 "QPushButton:pressed{"
                                 "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbDeleteChat->setFixedSize(250,50);
    pbDeleteChat->setFont(QFont("Times",10));
    namesChatsList = new QListWidget();
    namesChatsList->setStyleSheet("QListView{"
                             "color: black;}");
    namesChatsList->setFont(QFont("Times",10));
    gbChatsLayout->addWidget(namesChatsList);
    buttonsBox->setAlignment(Qt::AlignRight);
    buttonsBox->addWidget(pbDeleteChat);
    buttonsBox->addSpacing(50);
    buttonsBox->addWidget(pbAddNewChat);
    gbChats->setLayout(gbChatsLayout);
    mainBox->addWidget(gbChats);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->resize(600,590);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
   // connects
    connect(pbAddNewChat,SIGNAL(clicked()),SLOT(on_pbAddNewChat_clicked()));
    connect(pbDeleteChat,SIGNAL(clicked()),SLOT(on_pbDeleteChat_clicked()));
    connect(namesChatsList,&QListWidget::doubleClicked,this,&CChatsView::on_chats_clicked);
}

void CChatsView::set_user_name(const QString &userName){
    this->userName = userName;
}

void CChatsView::set_close_keys(const CCloseKeys &closeKeys_){
    this->closeKeys = closeKeys_;
    for (auto& chat : chats){
        chat->update_close_keys(this->closeKeys);
    }
}

void CChatsView::add_new_chat(const QString &userNameTo){
    CChatWithUserView *newChat = new CChatWithUserView(this->userName);
    newChat->set_user_name_from(this->userName);
    newChat->set_user_name_to(userNameTo);
    newChat->set_close_keys(this->closeKeys);
    connect(newChat,&CChatWithUserView::send_message,this,&CChatsView::on_send_message);
    chats.push_back(newChat);
    namesChatsList->addItem(userNameTo);
}

void CChatsView::add_message(const QString &message, const QString &userTo, std::pair<CBigInteger, CBigInteger> &digitalSignature){
    for (auto& chat : chats){
        if (chat->get_user_name_to() == userTo){
            chat->add_new_message(userTo,message,digitalSignature);
        }
    }
}

void CChatsView::add_user_keys(const QString &userName, const COpenKeys &key){
    for (auto& chat : chats){
        chat->add_user_keys(userName,key);
    }
}

void CChatsView::delete_chat(const QString &userTo){
    int deleteIndex = 0;
    for (int i = 0;i < chats.size();i++){
        if (chats[i]->get_user_name_to() == userTo){
            disconnect(chats[i],&CChatWithUserView::send_message,this,&CChatsView::on_send_message);
            delete chats[i];
            deleteIndex = i;
            break;
        }
    }
    chats.remove(deleteIndex);
    namesChatsList->model()->removeRow(deleteIndex);
}

void CChatsView::delete_all_chats(){
    for (auto& chat : chats){
        emit need_delete_chat(this->userName,chat->get_user_name_to());
    }
}

void CChatsView::delete_user_keys(const QString &userName){
    for (auto& chat : chats){
        chat->delete_user_keys(userName);
    }
}

bool CChatsView::find_chat(const QString &userName){
    for (auto& chat : chats){
        if (chat->get_user_name_to() == userName) return true;
    }
    return false;
}

CChatsView::~CChatsView(){
    for (auto& chat : chats){
        disconnect(chat,&CChatWithUserView::send_message,this,&CChatsView::on_send_message);
        delete chat;
    }
    chats.clear();
}

void CChatsView::on_pbAddNewChat_clicked(){
    emit need_add_new_chat();
}

void CChatsView::on_pbDeleteChat_clicked(){
    QModelIndexList selectedIndexs = namesChatsList->selectionModel()->selectedRows();
    for (auto& index : selectedIndexs){
        QString userTo = namesChatsList->model()->index(index.row(),0).data().toString();
        namesChatsList->model()->removeRow(index.row());
        disconnect(chats[index.row()],&CChatWithUserView::send_message,this,&CChatsView::on_send_message);
        delete chats[index.row()];
        chats.remove(index.row());
        emit need_delete_chat(userName,userTo);
    }
}

void CChatsView::on_chats_clicked(QModelIndex index){
    chats[index.row()]->show();
}

void CChatsView::on_send_message(QString message, QString userTo, std::pair <CBigInteger, CBigInteger> digitalSignature){
    emit send_message(message,this->userName,userTo,digitalSignature);
}
