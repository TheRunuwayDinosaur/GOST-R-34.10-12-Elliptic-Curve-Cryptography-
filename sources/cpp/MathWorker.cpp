#include "MathWorker.h"

CMathWorker::CMathWorker(){
    QVector <bool> isPrimes(1000 + 1,true);
    isPrimes[0] = isPrimes[1] = false;
    for (int i = 2;i <= 1000;i++){
        if (!isPrimes[i]) continue;
        for (int j = 2 * i;j <= 1000;j += i) isPrimes[j] = false;
    }
    for (int i = 2;i <= 1000;i++){
        if (!isPrimes[i]) continue;
        primesForDelTest.push_back(i);
    }
    hexValue['0'] = 0;
    hexValue['1'] = 1;
    hexValue['2'] = 2;
    hexValue['3'] = 3;
    hexValue['4'] = 4;
    hexValue['5'] = 5;
    hexValue['6'] = 6;
    hexValue['7'] = 7;
    hexValue['8'] = 8;
    hexValue['9'] = 9;
    hexValue['a'] = 10;
    hexValue['b'] = 11;
    hexValue['c'] = 12;
    hexValue['d'] = 13;
    hexValue['e'] = 14;
    hexValue['f'] = 15;
}

CBigInteger CMathWorker::pow(const CBigInteger &a, CBigInteger p) const{
    CBigInteger result = 1,mult = a;
    while(p > 0){
        if (p.odd()) result *= mult;
        mult *= mult;
        p.divide_by_2();
    }
    return result;
}

CBigInteger CMathWorker::bin_pow(const CBigInteger &a, CBigInteger p, const CBigInteger &mod) const{
    CBigInteger result = 1 % mod,mult = a;
    while(p > 0){
        if (p.odd()) result = this->mul_mod(result,mult,mod);
        mult = this->mul_mod(mult,mult,mod);
        p.divide_by_2();
    }
    return result;
}

CBigInteger CMathWorker::inverse_element(const CBigInteger &a, const CBigInteger &m) const{
    CBigInteger t = 0,newT = 1;
    CBigInteger r = m,newR = a;
    while(newR != 0){
        CBigInteger q = r / newR;
        CBigInteger nnT = t - q * newT;
        t = newT; newT = nnT;
        CBigInteger nnR = r - q * newR;
        r = newR; newR = nnR;
    }
    if (r > 1) return -1;
    if (t < 0) t += m;
    return t;
}

CBigInteger CMathWorker::gcd(CBigInteger a, CBigInteger b) const{
    while(b != 0){
        a %= b;
        std::swap(a,b);
    }
    return a;
}

bool CMathWorker::check_prime(CBigInteger &value) const{
    return ferm_test(value) && del_test(value);
}

bool CMathWorker::ferm_test(CBigInteger value) const{
    int t = 10;
    std::uniform_int_distribution<int> dist((int)2, (int)1e9);
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    while(t > 0){
        //CBigInteger a = dist(gen) % value;
        CBigInteger a = this->generate_random_number(2,value.get_number().toLongLong() - 1);
        if (this->gcd(a,value) != 1) return false;
        if (this->bin_pow(a,value - 1,value) != 1) return false;
        t--;
    }
    return true;
}

bool CMathWorker::del_test(CBigInteger value) const{
    for (auto& p : primesForDelTest){
        if (value >= p) break;
        if (value % p == 0) return false;
    }
    return true;
}

CBigInteger CMathWorker::add_mod(const CBigInteger &a, const CBigInteger &b, const CBigInteger &mod) const{
    return (a + b) % mod;
}

CBigInteger CMathWorker::sub_mod(const CBigInteger &a, const CBigInteger &b, const CBigInteger &mod) const{
    return add_mod(a,mod - b,mod);
}

CBigInteger CMathWorker::mul_mod(const CBigInteger &a, const CBigInteger &b, const CBigInteger &mod) const{
    return (a * b) % mod;
}

CBigInteger CMathWorker::div_mod(const CBigInteger &a, const CBigInteger &b, const CBigInteger &mod) const{
    return (a * inverse_element(b,mod)) % mod;
}

std::pair<CBigInteger, CBigInteger> CMathWorker::generate_elliptic_params(const CBigInteger &p) const{
    CBigInteger A = QRandomGenerator::global()->bounded(1,1000000);
    CBigInteger B = QRandomGenerator::global()->bounded(1,1000000);
    while(4 * this->bin_pow(A,3,p) + 27 * this->bin_pow(B,2,p) == 0 || A == B){
        A = QRandomGenerator::global()->bounded(1,1000000);
        B = QRandomGenerator::global()->bounded(1,1000000);
    }
    return std::make_pair(A,B);
}

CEllipticPoint CMathWorker::generate_elliptic_point(const CBigInteger &p, const CBigInteger &A, const CBigInteger &B) const{
    while(true){
        CBigInteger x = this->generate_random_number(1,p.get_number().toLongLong());
        CBigInteger xValue = this->add_mod((this->add_mod(this->bin_pow(x,3,p),
                                           this->mul_mod(A,x,p),
                                           p)),
                                           B,
                                           p);
        if (this->bin_pow(xValue,(p - 1) / 2,p) != 1) continue;
        CBigInteger y = this->bin_pow(xValue,(p + 1) / 4,p);
        return CEllipticPoint(CBigInteger(x),CBigInteger(y));
    }
    return CEllipticPoint();
}

CBigInteger CMathWorker::generate_random_number(int64_t from, int64_t to) const{
    std::uniform_int_distribution<int> dist((int64_t)from,(int64_t)to);
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return dist(gen);
}

std::pair<CBigInteger, CBigInteger> CMathWorker::generate_digital_signature(const CCloseKeys &closeKeys, const QString &hash) const{
    CBigInteger q = closeKeys.get_q();
    CEllipticPoint ellipticP = closeKeys.get_ellipticP();
    CBigInteger d = closeKeys.get_d();
//    qDebug() << "генерируем d = " << d.get_number();
    CBigInteger h = this->hex_to_big_integer(hash);
//    qDebug() << "генерируем h = " << h.get_number();
    CBigInteger e = h % q;
    if (e == 0) e = 1;
//    qDebug() << "генерируем e = " << e.get_number();
    CBigInteger k,r,s;
    CEllipticPoint C = ellipticP;
    while(true){
        k = this->generate_random_number(1,q.get_number().toLongLong());
        C = ellipticP * k;
        r = C.get_x() % q;
        if (r == 0) continue;
        s = this->add_mod(this->mul_mod(r,d,q),
                          this->mul_mod(k,e,q),
                          q);
        if (s == 0) continue;
        break;
    }
//    qDebug() << "генерируем k = " << k.get_number();
//    qDebug() << "генерируем C: ";
//    C.write_point();
//    qDebug() << "генерируем r = " << r.get_number();
//    qDebug() << "генерируем s = " << s.get_number();
    return std::make_pair(r,s);
    {
//    working
//    CBigInteger p("3623986102229003635907788753683874306021320925534678605086546150450856166624002482588482022271496854025090823603058735163734263822371964987228582907372403");
//    CBigInteger A = 7;
//    CBigInteger B("1518655069210828534508950034714043154928747527740206436194018823352809982443793732829756914785974674866041605397883677596626326413990136959047435811826396");
//    CBigInteger q("3623986102229003635907788753683874306021320925534678605086546150450856166623969164898305032863068499961404079437936585455865192212970734808812618120619743");
//    CEllipticPoint ellipticP(CBigInteger("1928356944067022849399309401243137598997786635459507974357075491307766592685835441065557681003184874819658004903212332884252335830250729527632383493573274"),
//                             CBigInteger("2288728693371972859970012155529478416353562327329506180314497425931102860301572814141997072271708807066593850650334152381857347798885864807605098724013854"));
//    ellipticP.set_A(A); ellipticP.set_B(B);
//    ellipticP.set_p(p); ellipticP.set_q(q);
//    CBigInteger d("610081804136373098219538153239847583006845519069531562982388135354890606301782255383608393423372379057665527595116827307025046458837440766121180466875860");
//    CEllipticPoint ellipticQ(CBigInteger("909546853002536596556690768669830310006929272546556281596372965370312498563182320436892870052842808608262832456858223580713780290717986855863433431150561"),
//                             CBigInteger("2921457203374425620632449734248415455640700823559488705164895837509539134297327397380287741428246088626609329139441895016863758984106326600572476822372076"));
//    ellipticQ.set_A(A); ellipticQ.set_B(B);
//    ellipticQ.set_p(p); ellipticQ.set_q(q);
//    CBigInteger e("2897963881682868575562827278553865049173745197871825199562947419041388950970536661109553499954248733088719748844538964641281654463513296973827706272045964");
//    CBigInteger k("175516356025850499540628279921125280333451031747737791650208144243182057075034446102986750962508909227235866126872473516807810541747529710309879958632945");
//    CEllipticPoint C = ellipticP * k;
//    CBigInteger r = C.get_x() % q;
//    CBigInteger s = this->add_mod(this->mul_mod(r,d,q),
//                                  this->mul_mod(k,e,q),
//                                  q);
//    qDebug() << "генерируем r = " << r.get_number();
//    qDebug() << "генерируем s = " << s.get_number();
//    return std::make_pair(r,s);
    }
}

bool CMathWorker::check_digital_signature(const std::pair<CBigInteger, CBigInteger> &digitalSignature,
                                          const COpenKeys &openKeys, const QString &hash) const{
    CBigInteger r = digitalSignature.first;
//    qDebug() << "проверяем  r = " << r.get_number();
    CBigInteger s = digitalSignature.second;
//    qDebug() << "проверяем s = " << s.get_number();
    CBigInteger q = openKeys.get_q();
//    qDebug() << "q = " << q.get_number();
    CEllipticPoint ellipticP = openKeys.get_ellipticP();
//    qDebug() << "ellipticP: ";
//    ellipticP.write_point();
//    qDebug() << "хыхы = " << ellipticP.get_p().get_number();
    CEllipticPoint ellipticQ = openKeys.get_ellipticQ();
//    qDebug() << "ellipticQ: ";
//    ellipticQ.write_point();
    CBigInteger h = this->hex_to_big_integer(hash);
//    qDebug() << "Проверяем h = " << h.get_number();
//    qDebug() << "h = " << h.get_number();
    CBigInteger e = h % q;
    if (e == -1) e = 1;
//    qDebug() << "e = " << e.get_number();
    CBigInteger v = this->inverse_element(e,q);
//    qDebug() << "v = " << v.get_number();
//    qDebug() << "v * e % q = " << ((v * e) % q).get_number();
    CBigInteger z1 = this->mul_mod(s,v,q);
//    qDebug() << "z1 = " << z1.get_number();
    CBigInteger z2 = this->sub_mod(q,this->mul_mod(r,
                                   v,
                                   q),q);
//    qDebug() << "z2 = " << z2.get_number();
    CEllipticPoint leftPoint = ellipticP * z1;
    CEllipticPoint rightPoint = ellipticQ * z2;
    CEllipticPoint C = leftPoint + rightPoint;
//    qDebug() << "C: ";
//    C.write_point();
    CBigInteger R = C.get_x() % q;
//    qDebug() << "R = " << R.get_number();
    return R == r;
    {
//    working
//    CBigInteger r = digitalSignature.first;
//    CBigInteger s = digitalSignature.second;
//    qDebug() << "Проверяем подпись: ";
//    qDebug() << r.get_number() << ' ' << s.get_number();
//    CBigInteger A = 7;
//    CBigInteger B("1518655069210828534508950034714043154928747527740206436194018823352809982443793732829756914785974674866041605397883677596626326413990136959047435811826396");
//    CBigInteger p("3623986102229003635907788753683874306021320925534678605086546150450856166624002482588482022271496854025090823603058735163734263822371964987228582907372403");
//    CBigInteger q("3623986102229003635907788753683874306021320925534678605086546150450856166623969164898305032863068499961404079437936585455865192212970734808812618120619743");
//    CEllipticPoint ellipticP(CBigInteger("1928356944067022849399309401243137598997786635459507974357075491307766592685835441065557681003184874819658004903212332884252335830250729527632383493573274"),
//                             CBigInteger("2288728693371972859970012155529478416353562327329506180314497425931102860301572814141997072271708807066593850650334152381857347798885864807605098724013854"));
//    ellipticP.set_A(A); ellipticP.set_B(B);
//    ellipticP.set_p(p); ellipticP.set_q(q);
//    CEllipticPoint ellipticQ(CBigInteger("909546853002536596556690768669830310006929272546556281596372965370312498563182320436892870052842808608262832456858223580713780290717986855863433431150561"),
//                             CBigInteger("2921457203374425620632449734248415455640700823559488705164895837509539134297327397380287741428246088626609329139441895016863758984106326600572476822372076"));
//    ellipticQ.set_A(A); ellipticQ.set_B(B);
//    ellipticQ.set_p(p); ellipticQ.set_q(q);
//    CBigInteger e("2897963881682868575562827278553865049173745197871825199562947419041388950970536661109553499954248733088719748844538964641281654463513296973827706272045964");
//    CBigInteger v = this->inverse_element(e,q);
//    CBigInteger z1 = this->mul_mod(s,v,q);
//    qDebug() << "проверяем z1 = " << z1.get_number();
//    CBigInteger z2 = q - this->mul_mod(r,
//                                       v,
//                                       q);
//    qDebug() << "z2 = " << z2.get_number();
//    CEllipticPoint C = (ellipticP * z1) + (ellipticQ * z2);
//    qDebug() << "проверяем C: ";
//    C.write_point();
//    CBigInteger R = C.get_x() % q;
//    qDebug() << "R = " << R.get_number();
//    return R == r;
    }
}

CBigInteger CMathWorker::hex_to_big_integer(const QString &hex) const{
    CBigInteger result = 0;
    CBigInteger p = 16,step = 0;
    for (int i = hex.size() - 1;i >= 0;i--){
        result += hexValue[hex[i]] * this->pow(p,step++);
    }
    return result;
}

CBigInteger CMathWorker::sqrt(const CBigInteger &value) const{
    CBigInteger left = 1,right = value;
    while(right - left > 1){
        CBigInteger mid = (left + right) / 2;
        if (mid * mid <= value) left = mid;
        else right = mid;
    }
    return left;
}

CBigInteger CMathWorker::sqrt4(const CBigInteger &value) const{
    CBigInteger left = 1,right = value;
    while(right - left > 1){
        CBigInteger mid = (left + right) / 2;
        if (mid * mid * mid * mid <= value) left = mid;
        else right = mid;
    }
    return left;
}

std::pair <CBigInteger,CEllipticPoint> CMathWorker::find_cyclic_group(const CBigInteger &p, const CBigInteger &A,const CBigInteger &B) const{
    CBigInteger pSqrt = this->sqrt(p);
    CBigInteger l = p + 1 - 2 * pSqrt;
    CBigInteger r = p + 1 + 2 * pSqrt;
    qDebug() << l.get_number() << ' ' << r.get_number();
    for (CBigInteger i = l;i <= r;i++){
        if (!this->check_prime(i)) continue;
        qDebug() << i.get_number();
        for (int iter = 0;iter < 1000;iter++){
            CEllipticPoint basePoint = this->generate_elliptic_point(p,A,B);
            basePoint.write_point();
            basePoint.set_A(A); basePoint.set_B(B); basePoint.set_p(p);
            CEllipticPoint resultPoint = basePoint * i;
            if (resultPoint.is_inf()) return std::make_pair(i,basePoint);
        }
    }
    return std::make_pair(CBigInteger(),CEllipticPoint());
}

CBigInteger CMathWorker::cnt_points_on_elliptic_curve(const CBigInteger &p, const CBigInteger &A, const CBigInteger &B) const{
    CBigInteger step = p / 8;
    CBigInteger l1 = 0,r1 = step;
    CBigInteger l2 = step,r2 = step * 2;
    CBigInteger l3 = step * 2,r3 = step * 3;
    CBigInteger l4 = step * 3,r4 = step * 4;
    CBigInteger l5 = step * 4,r5 = step * 5;
    CBigInteger l6 = step * 5,r6 = step * 6;
    CBigInteger l7 = step * 6,r7 = step * 7;
    CBigInteger l8 = step * 7,r8 = p;
    CPointsGenThread *th1 = new CPointsGenThread();
    th1->set_p(p); th1->set_A(A); th1->set_B(B);
    th1->set_l(l1); th1->set_r(r1);
    CPointsGenThread *th2 = new CPointsGenThread();
    th2->set_p(p); th2->set_A(A); th2->set_B(B);
    th2->set_l(l2); th2->set_r(r2);
    CPointsGenThread *th3 = new CPointsGenThread();
    th3->set_p(p); th3->set_A(A); th3->set_B(B);
    th3->set_l(l3); th3->set_r(r3);
    CPointsGenThread *th4 = new CPointsGenThread();
    th4->set_p(p); th4->set_A(A); th4->set_B(B);
    th4->set_l(l4); th4->set_r(r4);
    th1->start(); th2->start(); th3->start(); th4->start();
    CPointsGenThread *th5 = new CPointsGenThread();
    th5->set_p(p); th5->set_A(A); th5->set_B(B);
    th5->set_l(l5); th5->set_r(r5);
    CPointsGenThread *th6 = new CPointsGenThread();
    th6->set_p(p); th6->set_A(A); th6->set_B(B);
    th6->set_l(l6); th6->set_r(r6);
    CPointsGenThread *th7 = new CPointsGenThread();
    th7->set_p(p); th7->set_A(A); th7->set_B(B);
    th7->set_l(l7); th7->set_r(r7);
    CPointsGenThread *th8 = new CPointsGenThread();
    th8->set_p(p); th8->set_A(A); th8->set_B(B);
    th8->set_l(l8); th8->set_r(r8);
    th1->start(); th2->start(); th3->start(); th4->start();
    th5->start(); th6->start(); th7->start(); th8->start();
    while(th1->isRunning() || th2->isRunning() || th3->isRunning() || th4->isRunning() ||
          th5->isRunning() || th6->isRunning() || th7->isRunning() || th8->isRunning()){};
    CBigInteger cnt = th1->get_points() + th2->get_points() + th3->get_points() + th4->get_points();
    cnt += th5->get_points() + th6->get_points() + th7->get_points() + th8->get_points();
    cnt += 1;
    delete th1; delete th2; delete th3; delete th4;
    delete th5; delete th6; delete th7; delete th8;
    return cnt;
//    CBigInteger cnt = 0;
//    for (CBigInteger x = 0;x < p;x++){
//        CBigInteger xValue = this->add_mod((this->add_mod(this->bin_pow(x,3,p),
//                                           this->mul_mod(A,x,p),
//                                           p)),
//                                           B,
//                                           p);
//        if (this->bin_pow(xValue,(p - 1) / 2,p) != 1){
//            if (this->bin_pow(xValue,(p - 1) / 2,p) == 0){
//                cnt++;
//            }
//            continue;
//        }
//        cnt += 2;
//    }
//    return cnt + 1;
}

// BigInteger operators
std::ostream& operator <<(std::ostream& os, const CBigInteger& bi){
    if (bi.numbers.empty()) os << 0;
    else {
        if (bi.isNegative) os << '-';
        os << bi.numbers.back();
        // следующие числа нам нужно печатать группами по 9 цифр
        // поэтому сохраним текущий символ-заполнитель, а потом восстановим его
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi.numbers.size()) - 2; i >= 0; --i) {
            os << std::setw(9) << bi.numbers[i];
        }
        os.fill(old_fill);
    }
    return os;
}

bool operator ==(const CBigInteger& left, const CBigInteger& right) {
    // числа разных знаков точно не равны
    if (left.isNegative != right.isNegative) return false;
    // поскольку у нас два представления нуля, нужно это особо обработать
    if (left.numbers.empty()) {
        if (right.numbers.empty() || (right.numbers.size() == 1 && right.numbers[0] == 0)) return true;
        else return false;
    }

    if (right.numbers.empty()) {
        if (left.numbers.size() == 1 && left.numbers[0] == 0) return true;
        else return false;
    }
    // так как у нас нет ведущих нулей, то в числах должно быть одинаковое количество цифр (разрядов)
    if (left.numbers.size() != right.numbers.size()) return false;
    for (size_t i = 0; i < left.numbers.size(); ++i) if (left.numbers[i] != right.numbers[i]) return false;
    return true;
}

bool operator <(const CBigInteger& left,const CBigInteger& right) {
    if (left == right) return false;
    if (left.isNegative) {
        if (right.isNegative) return ((-right) < (-left));
        else return true;
    }
    else if (right.isNegative) return false;
    else {
        if (left.numbers.size() != right.numbers.size()) {
            return left.numbers.size() < right.numbers.size();
        }
        else {
            for (long long i = left.numbers.size() - 1; i >= 0; --i) {
                if (left.numbers[i] != right.numbers[i]) return left.numbers[i] < right.numbers[i];
            }
            return false;
        }
    }
}

bool operator !=(const CBigInteger& left, const CBigInteger& right) {
    return !(left == right);
}

bool operator <=(const CBigInteger& left, const CBigInteger& right) {
    return (left < right || left == right);
}

bool operator >(const CBigInteger& left, const CBigInteger& right) {
    return !(left <= right);
}

bool operator >=(const CBigInteger& left, const CBigInteger& right) {
    return !(left < right);
}

const CBigInteger operator +(CBigInteger left, const CBigInteger& right) {
    // напишу лишь сложение двух положительных чисел
    // остальное выведу, используя смену знака и вычитание
    if (left.isNegative) {
        if (right.isNegative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right.isNegative) return left - (-right);
    int carry = 0; // флаг переноса из предыдущего разряда
    for (size_t i = 0; i < std::max(left.numbers.size(), right.numbers.size()) || carry != 0; ++i) {
        if (i == left.numbers.size()) left.numbers.push_back(0);
        left.numbers[i] += carry + (i < right.numbers.size() ? right.numbers[i] : 0);
        carry = left.numbers[i] >= CBigInteger::BASE;
        if (carry != 0) left.numbers[i] -= CBigInteger::BASE;
    }
    return left;
}

const CBigInteger operator -(CBigInteger left, const CBigInteger& right) {
    if (right.isNegative) return left + (-right);
    else if (left.isNegative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right.numbers.size() || carry != 0; ++i) {
        left.numbers[i] -= carry + (i < right.numbers.size() ? right.numbers[i] : 0);
        carry = left.numbers[i] < 0;
        if (carry != 0) left.numbers[i] += CBigInteger::BASE;
    }
    left.remove_leading_zeros();
    return left;
}

const CBigInteger operator *(const CBigInteger& left, const CBigInteger& right) {
    CBigInteger result("");
    result.numbers.resize(left.numbers.size() + right.numbers.size());
    for (size_t i = 0; i < left.numbers.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.numbers.size() || carry != 0; ++j) {
            long long cur = result.numbers[i + j] +
                    left.numbers[i] * 1LL * (j < right.numbers.size() ? right.numbers[j] : 0) + carry;
            result.numbers[i + j] = static_cast<int>(cur % CBigInteger::BASE);
            carry = static_cast<int>(cur / CBigInteger::BASE);
        }
    }
    // не забыть про знак
    result.isNegative = left.isNegative != right.isNegative;
    result.remove_leading_zeros();
    return result;
}

const CBigInteger operator /(const CBigInteger& left, const CBigInteger& right) {
    // на ноль делить нельзя
    if (right == 0){
        qDebug() << "ДЕЛИМ НА НОЛЬ!";
        return 0;
    }
    CBigInteger b = right;
    b.isNegative = false;
    CBigInteger result(""), current("");
    result.numbers.resize(left.numbers.size());
    for (long long i = static_cast<long long>(left.numbers.size()) - 1; i >= 0; --i) {
        current.shift_right();
        current.numbers[0] = left.numbers[i];
        current.remove_leading_zeros();
        int l = -1, r = CBigInteger::BASE + 1;
        while(r - l > 1){
            int m = (l + r) / 2;
            CBigInteger t = b * m;
            if (t <= current) l = m;
            else r = m;
        }
        result.numbers[i] = l;
        current = current - b * l;
    }
    result.isNegative = left.isNegative != right.isNegative;
    result.remove_leading_zeros();
    return result;
}

const CBigInteger operator %(const CBigInteger& left, const CBigInteger& right) {
    CBigInteger result = left - (left / right) * right;
    if (result.isNegative) result += right;
    return result;
}

// elliptic curve
const CEllipticPoint operator +(const CEllipticPoint &left,const CEllipticPoint &right){
    if (left.get_x() == 0 && left.get_y() == 0) return right;
    CMathWorker mathWorker;
    CBigInteger x1 = left.get_x(),y1 = left.get_y();
    CBigInteger x2 = right.get_x(),y2 = right.get_y();
    CBigInteger lambda = left & right;
    if (lambda == -1) return CEllipticPoint(CBigInteger(0),CBigInteger(0));
    CBigInteger p = left.get_p();
    CBigInteger xNew = mathWorker.sub_mod(mathWorker.sub_mod(mathWorker.bin_pow(lambda,2,p),x1,p),x2,p);
    CBigInteger yNew = mathWorker.sub_mod(mathWorker.mul_mod(lambda,(x1 - xNew),p),y1,p);
    CEllipticPoint result(xNew,yNew);
    result.set_A(left.get_A()); result.set_B(left.get_B());
    result.set_p(left.get_p());
    return result;
}

const CEllipticPoint operator *(CEllipticPoint point,CBigInteger x){
    CMathWorker mathWorker;
    bool wasAns = false;
    CEllipticPoint result;
    result.set_A(point.get_A()); result.set_B(point.get_B()); result.set_p(point.get_p());
    while(x > 0){
        //qDebug() << x.get_number();
        if (x.odd()){
            if (!wasAns){
                result = point;
                wasAns = true;
            }
            else result += point;
        }
        //qDebug() << "я вышел!";
        point += point;
        //result.write_point();
        //point.write_point();
        x.divide_by_2();
    }
    return result;
}

const CBigInteger operator &(const CEllipticPoint &left,const CEllipticPoint &right){
    CMathWorker mathWorker;
    CBigInteger A = left.get_A(),p = left.get_p();
    CBigInteger x1 = left.get_x(),y1 = left.get_y();
    CBigInteger x2 = right.get_x(),y2 = right.get_y();
    if (x1 == x2){
        if (y1 != y2) return -1;
        CBigInteger leftPart = mathWorker.add_mod(mathWorker.mul_mod(3,mathWorker.bin_pow(x1,2,p),p),A,p);
        CBigInteger rightPart = mathWorker.mul_mod(2,y1,p);
        CBigInteger lambda = mathWorker.div_mod(leftPart,rightPart,p);
        return lambda;
    }
    else{
        CBigInteger leftPart = mathWorker.sub_mod(y2,y1,p);
        CBigInteger rightPart = mathWorker.sub_mod(x2,x1,p);
        CBigInteger lambda = mathWorker.div_mod(leftPart,rightPart,p);
        return lambda;
    }
}
