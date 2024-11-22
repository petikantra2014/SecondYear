#include "Set.h"


Set::Set(size_t mp) : _maxPower(mp), _bitField(BitField(mp)) {
}
Set::Set(const Set &s) : _maxPower(s._maxPower), _bitField(BitField(s._bitField)){

} 
Set::Set(const BitField &bf) : _maxPower(bf.GetLength()), _bitField(bf) {

}

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    if (Elem < _maxPower) {
    _bitField.SetBit(Elem);
    }
    else {
    throw "Elem out of range";
    }
}
void Set::DelElem(const uint64_t elem){
    _bitField.ClrBit(elem);
}
bool Set::IsMember(const uint64_t elem) const{
    if (elem < _maxPower && elem >= 0) {
    if (_bitField.GetBit(elem) == 1) return true;
    }
    return false;
}


bool Set::operator== (const Set &s) const{
    return (_bitField == s._bitField);
}
bool Set::operator!= (const Set &s) const{
    return !(_bitField == s._bitField);
    
}
Set& Set::operator=(const Set &s){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    this->InsElem(Elem);
    return *this;
}
                                  
Set Set::operator- (const uint64_t Elem){
    this->DelElem(Elem);
    return *this;
}
                                   
Set Set::operator+ (const Set &s){
    size_t Size = _maxPower > s._maxPower ? _maxPower : s._maxPower;
    Set res(Size);
    res._bitField = _bitField | s._bitField;
    return res;
}
Set Set::operator* (const Set &s){
    size_t Size = _maxPower > s._maxPower ? _maxPower : s._maxPower;
    Set res(Size);
    res._bitField = _bitField & s._bitField;
    return res;
}
Set Set::operator~ (){
    Set res(_maxPower);
    res._bitField = ~_bitField;
    return res;
}
std::vector<uint64_t> Set::GetPrimary(){
    std::vector<uint64_t> simple;
        std::vector<bool> is_prime(_maxPower+1, true);
        is_prime[0] =  false;
        for(size_t i = 2; i * i <= _maxPower; i++)
            if (is_prime[i])
                for (size_t j = i * i; j <= _maxPower; j += i)
                    is_prime[j] = false;
        for (size_t p = 1; p <= _maxPower; p++)
        {
            if (is_prime[p])
            {
                simple.push_back(p);
            }
        }

    return simple;

}