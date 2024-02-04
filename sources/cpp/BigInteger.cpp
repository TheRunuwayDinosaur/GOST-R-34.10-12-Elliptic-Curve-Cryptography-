#include "BigInteger.h"

CBigInteger::CBigInteger(){
    this->isNegative = false;
}

CBigInteger::CBigInteger(std::string str){
    this->set_number(str);
}

CBigInteger::CBigInteger(int x){
    if (x < 0) {
        this->isNegative = true;
        x *= -1;
    }
    else this->isNegative = false;
    do{
        this->numbers.push_back(x % CBigInteger::BASE);
        x /= CBigInteger::BASE;
    } while (x != 0);
}

CBigInteger::CBigInteger(unsigned int x){
    this->isNegative = false;
    do {
        this->numbers.push_back(x % CBigInteger::BASE);
        x /= CBigInteger::BASE;
    } while (x != 0);
}

CBigInteger::CBigInteger(long long x){
    if (x < 0) {
        this->isNegative = true;
        x *= -1;
    }
    else this->isNegative = false;
    do{
        this->numbers.push_back(x % CBigInteger::BASE);
        x /= CBigInteger::BASE;
    } while (x != 0);
}

CBigInteger::CBigInteger(unsigned long long x){
    this->isNegative = false;
    do {
        this->numbers.push_back(x % CBigInteger::BASE);
        x /= CBigInteger::BASE;
    } while (x != 0);
}

void CBigInteger::set_number(std::string str){
    this->numbers.clear();
    if (str.size() == 0) {
        this->isNegative = false;
    }
    else{
        if (str[0] == '-') {
            str = str.substr(1);
            this->isNegative = true;
        }
        else this->isNegative = false;
        for (int i = str.size(); i > 0; i -= 9) {
            if (i < 9) this->numbers.push_back(atoi(str.substr(0, i).c_str()));
            else this->numbers.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }
        this->remove_leading_zeros();
    }
}

void CBigInteger::shift_right(){
    if (this->numbers.size() == 0) {
        this->numbers.push_back(0);
        return;
    }
    this->numbers.push_back(this->numbers[this->numbers.size() - 1]);
    for (int i = this->numbers.size() - 2; i > 0; --i) this->numbers[i] = this->numbers[i - 1];
    this->numbers[0] = 0;
}

bool CBigInteger::odd(){
    if (this->numbers.size() == 0) return false;
    return this->numbers[0] & 1;
}

bool CBigInteger::even(){
    return !this->odd();
}

void CBigInteger::remove_leading_zeros(){
    while (this->numbers.size() > 1 && !this->numbers.back()) this->numbers.pop_back();
    if (this->numbers.size() == 1 && this->numbers[0] == 0) this->isNegative = false;
}

void CBigInteger::divide_by_2(){
    int add = 0;
    for (int i = this->numbers.size() - 1;i >= 0;i--){
        int digit = (this->numbers[i] >> 1) + add;
        add = ((this->numbers[i] & 1) * (this->BASE / 2));
        this->numbers[i] = digit;
    }
    this->remove_leading_zeros();
}

QString CBigInteger::get_number() const{
    std::stringstream ss;
    ss << *this;
    return QVariant(ss.str().c_str()).toString();
}

int CBigInteger::log2() const{
    CBigInteger temp = *this;
    int log = 0;
    while(temp > 0){
        log++; temp.divide_by_2();
    }
    return log;
}

CBigInteger CBigInteger::operator +() const{
    return CBigInteger(*this);
}

CBigInteger CBigInteger::operator -() const{
    CBigInteger copy(*this);
    copy.isNegative = !copy.isNegative;
    return copy;
}

CBigInteger CBigInteger::operator +=(const CBigInteger &value){
    return *this = (*this + value);
}

CBigInteger CBigInteger::operator -=(const CBigInteger &value){
    return *this = (*this - value);
}

CBigInteger CBigInteger::operator *=(const CBigInteger &value){
    return *this = (*this * value);
}

CBigInteger CBigInteger::operator /=(const CBigInteger &value){
    return *this = (*this / value);
}

CBigInteger CBigInteger::operator %=(const CBigInteger &value){
    return *this = (*this % value);
}

CBigInteger CBigInteger::operator ++(){
    return (*this += 1);
}

CBigInteger CBigInteger::operator --(){
    return (*this -= 1);
}

CBigInteger CBigInteger::operator ++(int){
    *this += 1;
    return *this - 1;
}

CBigInteger CBigInteger::operator --(int){
    *this -= 1;
    return *this + 1;
}
