#include "KeysGenThread.h"

CKeysGenThread::CKeysGenThread(){
    keysGenerator = new CKeysGenerator();
}

CKeysGenThread::~CKeysGenThread(){
    delete keysGenerator;
}

void CKeysGenThread::run(){
    CCloseKeys keys = keysGenerator->generate_keys();
    emit keys_generated(keys.get_p().get_number(),keys.get_A().get_number(),
                        keys.get_B().get_number(),keys.get_q().get_number());
}
