#include "MainView.h"

CMainView::CMainView(QFrame *parent) : QFrame(parent){
    mathWorker = new CMathWorker();
    mainBox = new QVBoxLayout();
    gbMessLayout = new QVBoxLayout();
    buttonsBox = new QHBoxLayout();
    gbMess = new QGroupBox("Список пользователей");
    gbMess->setStyleSheet("QGroupBox{"
                          "font: bold;"
                          "color: purple;"
                          "border: 1px solid silver;"
                          "border-radius: 30px;"
                          "margin-top: 6px; }"
                          "QGroupBox::title{"
                          "subcontrol-origin: margin;"
                          "left: 7px;"
                          "padding: 0px 5px 0px 5px;}");
    gbMess->setFont(QFont("Times",10));
    messModel = new CMessengerModel(this);
    listView = new QListView();
    selectUsersView = new CSelectUsersView(messModel);
    addChatView = new CAddChatView(messModel);
    listView->setStyleSheet("QListView{"
                             "color: black;}");
    pbAddUser = new QPushButton("Добавить пользователя");
    pbAddUser->setStyleSheet("QPushButton{"
                             "border:none;"
                             "color: white;"
                             "font: bold;"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                             "border-radius: 15px}"
                             "QPushButton:hover{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                             "QPushButton:disabled{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                             "QPushButton:pressed{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbAddUser->setFixedHeight(60);
    pbAddUser->setFont(QFont("Times",10));
    pbDeleteUser = new QPushButton("Удалить пользователя");
    pbDeleteUser->setStyleSheet("QPushButton{"
                             "border:none;"
                             "color: white;"
                             "font: bold;"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #00FA9A,stop: 0.4999 #00FA9A,stop: 0.5 #00FA9A,stop: 1 #238);"
                             "border-radius: 15px}"
                             "QPushButton:hover{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #87CEFA,stop: 0.4999 #BA55D3,stop: 0.5 #BA55D3,stop: 1 #238);}"
                             "QPushButton:disabled{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #E83812,stop: 0.4999 #E83812,stop: 0.5 #E83812,stop: 1 #238);}"
                             "QPushButton:pressed{"
                             "background-color: QLinearGradient(x1: 1, y1: 0, x2: 0, y2: 1,stop: 0 #DA70D6,stop: 0.4999 #FFF0F5,stop: 0.5 #FFF0F5,stop: 1 #238);}");
    pbDeleteUser->setFixedHeight(60);
    pbDeleteUser->setFont(QFont("Times",10));
    listView->setFont(QFont("Times",10));
    listView->setModel(messModel);
    gbMessLayout->addWidget(listView);
    gbMess->setLayout(gbMessLayout);
    buttonsBox->addWidget(pbAddUser);
    buttonsBox->addSpacing(50);
    buttonsBox->addWidget(pbDeleteUser);
    mainBox->addWidget(gbMess);
    mainBox->addLayout(buttonsBox);
    this->setLayout(mainBox);
    this->setFont(QFont("Times",10));
    this->setFixedSize(520,650);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowTitle("SMessenger on ECC");
    this->setWindowIcon(QIcon(":/icons/appGraphic/messIcon.ico"));
   // connects
    connect(listView,&QListView::doubleClicked,this,&CMainView::on_listView_clicked);
    connect(pbAddUser,SIGNAL(clicked()),SLOT(on_pbAddUser_clicked()));
    connect(pbDeleteUser,SIGNAL(clicked()),SLOT(on_pbDeleteUser_clicked()));
    connect(messModel,&CMessengerModel::publish_keys_to_main_view,this,&CMainView::on_publish_keys_to_main_view);
    connect(selectUsersView,&CSelectUsersView::send_keys_to_users,this,&CMainView::on_send_keys_to_users);
    connect(messModel,&CMessengerModel::add_new_chat,this,&CMainView::on_add_new_chat);
    connect(addChatView,&CAddChatView::chat_choised,this,&CMainView::on_chat_choised);
   // temp;
}

CMainView::~CMainView(){
    delete mathWorker;
    delete selectUsersView;
    delete addChatView;
}

void CMainView::on_listView_clicked(QModelIndex index){
    CUserView *user = messModel->get_user(index.row());
    user->show();
}

void CMainView::on_pbAddUser_clicked(){
    this->setEnabled(false);
    addView = new CAddUserView();
    addView->set_users(messModel);
    connect(addView,&CAddUserView::add_user,this,&CMainView::on_add_user);
    addView->show();
}

void CMainView::on_pbDeleteUser_clicked(){
    QModelIndexList selectedIndexs = listView->selectionModel()->selectedRows();
    for (auto& index : selectedIndexs) messModel->remove_user(index.row());
}

void CMainView::on_add_user(QString userName){
    if (userName.size() != 0) messModel->add_user(userName);
    addView->close();
    disconnect(addView,&CAddUserView::add_user,this,&CMainView::on_add_user);
    delete addView;
    this->setEnabled(true);
}

void CMainView::on_publish_keys_to_main_view(COpenKeys userOpenKeys, QString userName){
    this->userOpenKeys = userOpenKeys;
    this->userName = userName;
    selectUsersView->show();
}

void CMainView::on_send_keys_to_users(QModelIndexList users){
    selectUsersView->close();
    for (auto& index : users){
        CUserView *user = messModel->get_user(index.row());
        if (user->get_name() == userName) continue;
        user->add_user_keys(userName,userOpenKeys);
    }
    for (int i = 0;i < messModel->size();i++){
        if (messModel->get_user(i)->get_name() == userName){
            messModel->get_user(i)->set_keys_enabled();
            break;
        }
    }
}

void CMainView::on_add_new_chat(QString userName){
    this->userName = userName;
    addChatView->show();
}

void CMainView::on_chat_choised(QString userNameWith){
    if (userName == userNameWith){
        QMessageBox::critical(nullptr,"Ошибка","Вы не можете создать чат с самим собой!");
        return;
    }
    for (int i = 0;i < messModel->size();i++){
        CUserView *curUser = messModel->get_user(i);
        if (curUser->get_name() == userName){
            if (curUser->find_chat(userNameWith)){
                QMessageBox::critical(nullptr,"Ошибка","Такой чат уже существует!");
                return;
            }
        }
    }
    for (int i = 0;i < messModel->size();i++){
        CUserView *curUser = messModel->get_user(i);
        if (curUser->get_name() == userName){
            curUser->new_chat(userNameWith);
        }
        else if (curUser->get_name() == userNameWith){
            curUser->new_chat(userName);
        }
    }
}
