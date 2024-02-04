#include "StreebogMain.h"

CStreebogMain::CStreebogMain(QObject *parent) : QObject(parent){
    CTX = new TGOSTHashContext();
}

CStreebogMain::~CStreebogMain(){
    delete CTX;
}

QString CStreebogMain::get_hash_from_string(const QString &message) const{
    uint8_t *buffer = (uint8_t*)malloc(strlen(message.toStdString().c_str()));
    memcpy(buffer,message.toStdString().c_str(),strlen(message.toStdString().c_str()));
    GOSTHashInit(CTX,DEFAULT_HASH_SIZE);
    GOSTHashUpdate(CTX,buffer,strlen(message.toStdString().c_str()));
    GOSTHashFinal(CTX);
    QString result = "";
    if (CTX->hash_size == 256){
        for(int i = 32; i < 64; i++){
            int hex = QVariant(CTX->hash[i]).toString().toInt();
            QString hexStr = QString::number(hex,16);
            if (hexStr.size() == 1) hexStr = '0' + hexStr;
            result += hexStr;
        }
    }
    else{
        for(int i = 0; i < 64; i++){
            int hex = QVariant(CTX->hash[i]).toString().toInt();
            QString hexStr = QString::number(hex,16);
            if (hexStr.size() == 1) hexStr = '0' + hexStr;
            result += hexStr;
        }
    }
    return result;
}
