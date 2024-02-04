#include "UserView.h"

CUserView::CUserView(const QString &name, QWidget *parent) : QFrame(parent){
    this->set_name(name);
    mainBox = new QVBoxLayout();
    tabs = new QTabWidget();
    tabs->setFont(QFont("Times",10));
    keysView = new CKeysView(this);
    usersWithKeysView = new CUsersWithKeysView(this);
    chatsView = new CChatsView(this);
    chatsView->set_user_name(this->userName);
    tabs->addTab(keysView,"Генерация ключей");
    tabs->addTab(usersWithKeysView,"Открытые ключи пользователей");
    tabs->addTab(chatsView,"Чаты");
    tabs->setTabIcon(0,QIcon(":/icons/appGraphic/keysView.ico"));
    tabs->setTabIcon(1,QIcon(":/icons/appGraphic/usersKeys.ico"));
    tabs->setTabIcon(2,QIcon(":/icons/appGraphic/chats.ico"));
    mainBox->addWidget(tabs);
    this->setLayout(mainBox);
    this->resize(700,750);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),QApplication::desktop()->availableGeometry()));
    this->setWindowIcon(QIcon(":/icons/appGraphic/user.ico"));
   // connects
    connect(keysView,&CKeysView::publish_keys_to_user,this,&CUserView::on_publish_keys_to_user);
    connect(keysView,&CKeysView::close_keys_generated,this,&CUserView::on_close_keys_generated);
    connect(chatsView,&CChatsView::need_add_new_chat,this,&CUserView::on_add_new_chat);
    connect(chatsView,&CChatsView::send_message,this,&CUserView::on_send_message);
    connect(chatsView,&CChatsView::need_delete_chat,this,&CUserView::on_need_delete_chat);
}

CUserView::~CUserView(){

}

void CUserView::set_name(const QString &name){
    this->userName = name;
    this->setWindowTitle(QString("Пользователь: %1").arg(this->userName));
}

void CUserView::add_user_keys(const QString &userName, const COpenKeys &key){
    userKeys[userName] = key;
    usersWithKeysView->add_user_keys(userName,key);
    chatsView->add_user_keys(userName,key);
}

void CUserView::delete_user_keys(const QString &userName){
    userKeys.remove(userName);
    usersWithKeysView->delete_user_keys(userName);
    chatsView->delete_user_keys(userName);
}

void CUserView::set_keys_enabled() const{
    keysView->setEnabled(true);
}

QString CUserView::get_name() const{
    return this->userName;
}

void CUserView::new_chat(const QString &userNameTo){
    chatsView->add_new_chat(userNameTo);
    for (auto iter = userKeys.begin();iter != userKeys.end();iter++){
        chatsView->add_user_keys(iter.key(),iter.value());
    }
}

void CUserView::add_message(const QString &message, const QString &userTo, std::pair<CBigInteger, CBigInteger> &digitalSignature){
    chatsView->add_message(message,userTo,digitalSignature);
}

bool CUserView::find_chat(const QString &userName){
    return chatsView->find_chat(userName);
}

void CUserView::delete_chat(const QString &userTo){
    chatsView->delete_chat(userTo);
}

void CUserView::delete_all_chats() const{
    chatsView->delete_all_chats();
}

void CUserView::on_publish_keys_to_user(COpenKeys userOpenKeys){
    emit publish_keys_to_mess_model(userOpenKeys,this->userName);
}

void CUserView::on_add_new_chat(){
    emit add_new_chat(this->userName);
}

void CUserView::on_need_delete_chat(QString userFrom, QString userTo){
    emit need_delete_chat(userFrom,userTo);
}

void CUserView::on_send_message(QString message, QString userFrom, QString userTo,
                                std::pair <CBigInteger,CBigInteger> digitalSignature){
    emit send_message(message,userFrom,userTo,digitalSignature);
}

void CUserView::on_close_keys_generated(){
    this->closeKeys = keysView->get_close_keys();
    chatsView->set_close_keys(this->closeKeys);
}
