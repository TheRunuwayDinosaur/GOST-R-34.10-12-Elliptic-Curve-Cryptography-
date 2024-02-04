#include "PrimesGenThread.h"

CPrimesGeneratorThread::CPrimesGeneratorThread(){
    generator = new CPrimesGenerator();
}

CPrimesGeneratorThread::~CPrimesGeneratorThread(){
    delete generator;
}

void CPrimesGeneratorThread::run(){
    CBigInteger prime = generator->generate_p();
    emit prime_generated(prime.get_number());
}
