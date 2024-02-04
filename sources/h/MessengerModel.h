#ifndef MESSENGERMODEL_H
#define MESSENGERMODEL_H

#include <QObject>
#include <QtWidgets>
#include "UserView.h"

class CMessengerModel : public QAbstractListModel{
    Q_OBJECT

public:
    CMessengerModel(QObject *parent = 0);
    ~CMessengerModel();
    int size() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    CUserView *get_user(int index) const;
    void add_user(const QString &userName);
    void remove_user(int index);

private:
    QVector <CUserView*> users;

private slots:
    void on_publish_keys_to_mess_model(COpenKeys userOpenKeys,QString userName);
    void on_add_new_chat(QString userName);
    void on_need_delete_chat(QString userFrom,QString userTo);
    void on_send_message(QString message,QString userFrom,QString userTo,
                         std::pair <CBigInteger,CBigInteger> digitalSignature);

signals:
    void publish_keys_to_main_view(COpenKeys userOpenKeys,QString userName);
    void add_new_chat(QString userName);

};

#endif // MESSENGERMODEL_H
