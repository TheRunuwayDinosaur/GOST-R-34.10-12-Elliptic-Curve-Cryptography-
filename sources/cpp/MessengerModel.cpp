#include "MessengerModel.h"

CMessengerModel::CMessengerModel(QObject *parent) : QAbstractListModel(parent){

}

CMessengerModel::~CMessengerModel(){
    for (auto& user : users){
        disconnect(user,&CUserView::publish_keys_to_mess_model,this,&CMessengerModel::on_publish_keys_to_mess_model);
        disconnect(user,&CUserView::add_new_chat,this,&CMessengerModel::on_add_new_chat);
        disconnect(user,&CUserView::send_message,this,&CMessengerModel::on_send_message);
        disconnect(user,&CUserView::need_delete_chat,this,&CMessengerModel::on_need_delete_chat);
        delete user;
    }
    users.clear();
}

int CMessengerModel::size() const{
    return users.size();
}

int CMessengerModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return users.size();
}

QVariant CMessengerModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        int row = index.row();
        return QVariant(users[row]->get_name());
    }
    else return QVariant();
}

CUserView *CMessengerModel::get_user(int index) const{
    return users[index];
}

void CMessengerModel::add_user(const QString &userName){
    beginInsertRows(QModelIndex(),users.size(),users.size());
    CUserView *newUser = new CUserView(userName);
    connect(newUser,&CUserView::publish_keys_to_mess_model,this,&CMessengerModel::on_publish_keys_to_mess_model);
    connect(newUser,&CUserView::add_new_chat,this,&CMessengerModel::on_add_new_chat);
    connect(newUser,&CUserView::send_message,this,&CMessengerModel::on_send_message);
    connect(newUser,&CUserView::need_delete_chat,this,&CMessengerModel::on_need_delete_chat);
    users.push_back(newUser);
    endInsertRows();
}

void CMessengerModel::remove_user(int index){
    users[index]->delete_all_chats();
    QString userName = users[index]->get_name();
    beginRemoveRows(QModelIndex(),users.size(),users.size());
    disconnect(users[index],&CUserView::publish_keys_to_mess_model,this,&CMessengerModel::on_publish_keys_to_mess_model);
    disconnect(users[index],&CUserView::add_new_chat,this,&CMessengerModel::on_add_new_chat);
    disconnect(users[index],&CUserView::send_message,this,&CMessengerModel::on_send_message);
    disconnect(users[index],&CUserView::need_delete_chat,this,&CMessengerModel::on_need_delete_chat);
    delete users[index];
    users.remove(index);
    endRemoveRows();
    for (auto &user : users) user->delete_user_keys(userName);
}

void CMessengerModel::on_publish_keys_to_mess_model(COpenKeys userOpenKeys, QString userName){
    emit publish_keys_to_main_view(userOpenKeys,userName);
}

void CMessengerModel::on_add_new_chat(QString userName){
    emit add_new_chat(userName);
}

void CMessengerModel::on_need_delete_chat(QString userFrom, QString userTo){
    for (auto& user : users){
        if (user->get_name() == userTo){
            user->delete_chat(userFrom);
        }
    }
}

void CMessengerModel::on_send_message(QString message, QString userFrom, QString userTo,
                                      std::pair <CBigInteger,CBigInteger> digitalSignature){
    for (auto &user : users){
        if (user->get_name() == userTo){
            user->add_message(message,userFrom,digitalSignature);
            break;
        }
    }
}
