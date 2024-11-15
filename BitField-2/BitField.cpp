#include "BitField.h"


size_t BitField::GetMemIndex(size_t n) const{
    if (n < _sizeBit){
        return n / (8 * sizeof(uint16_t));
    }
    throw"Bit out of range";
}
uint16_t BitField::GetMask(size_t n) const {
    return (1 << (n & sizeof(uint16_t)));
}

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = _sizeBit / (sizeof(uint16_t) * 16) + (_sizeBit % (16 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; i++)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; i++)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_sizeBit != tmp._sizeBit)
    {
        _memSize = tmp._memSize;
        _sizeBit = tmp._sizeBit;
        delete[] _mem;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; i++)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    if (n < _sizeBit)
        _mem[GetMemIndex(n)] |= GetMask(n);
    else throw "0";
}
void BitField::ClrBit(size_t n) {
    if (n < _sizeBit)
        _mem[GetMemIndex(n)] &= ~GetMask(n);
}
uint8_t BitField::GetBit(size_t n) const {
    uint16_t tmp = _mem[GetMemIndex(n)];
    tmp &= GetMask(n);
    return (tmp != 0 ? 1 : 0);
}
BitField BitField::operator|(const BitField& tmp) {
    size_t Size = _sizeBit > tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    BitField res(Size);
    for (size_t i = 0; i < _memSize; i++) {
        res._mem[i] |= _mem[i];
    }
    for (size_t i = 0; i < tmp._memSize; i++) {
        res._mem[i] |= tmp._mem[i];
    }
    return res;
}

BitField BitField::operator&(const BitField& tmp) {
    size_t Size = _sizeBit > tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    size_t size = _sizeBit < tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    BitField res(Size);
    for (size_t i = 0; i < size; i++) {
        res._mem[i] = _mem[i] & tmp._mem[i];
     }
    return res;
}
BitField BitField::operator^(const BitField& tmp) {
    size_t Size = _sizeBit > tmp._sizeBit ? _sizeBit : tmp._sizeBit;
    BitField res(Size);
    for (size_t i = 0; i < Size; i++)
        res._mem[i] = _mem[i] ^ tmp._mem[i];
    return res;
}
bool BitField::operator==(const BitField& tmp) const{
    if (tmp._memSize != _memSize) return false;
    for (size_t i = 0; i < tmp._memSize; i++) {
        if (_mem[i] != tmp._mem[i]) return false;
    }
    return true;
}
BitField BitField::operator~(){
    BitField res(_sizeBit);
    for (size_t i = 0; i < _sizeBit; i++) {
        if (this->GetBit(i) == 0)
            res.SetBit(i);
        else
            res.ClrBit(i);
    }
    return res;
}
