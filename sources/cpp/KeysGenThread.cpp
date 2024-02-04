#include "KeysGenThread.h"

CKeysGenThread::CKeysGenThread(){
    keysGenerator = new CKeysGenerator();
}

CKeysGenThread::~CKeysGenThread(){
    delete keysGenerator;
}

void CKeysGenThread::run(){
    CCloseKeys keys = keysGenerator->generate_keys();
//    qDebug() << keys.get_p().get_number() << ' ' << keys.get_q().get_number();
//    qDebug() << keys.get_A().get_number() << ' ' << keys.get_B().get_number();
//    keys.get_ellipticP().write_point();
//    keys.get_ellipticQ().write_point();
//    CEllipticPoint temp = keys.get_ellipticP() * keys.get_q();
//    temp.write_point();
    emit keys_generated(keys.get_p().get_number(),keys.get_A().get_number(),
                        keys.get_B().get_number(),keys.get_q().get_number());
}
