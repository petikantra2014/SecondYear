#pragma once
#include <iostream>
#include <algorithm>


template<typename T>
class ArrayHandler
{
private:
    T* _array;
    size_t _size;
    size_t _count;
    int min = 1000000000;
    int max = -1000000000;
public:
    ArrayHandler(){
        _size = 5;
        _count = 0;
        _array = new T[_size];
    };
    ArrayHandler(size_t size){
        _size = size;
        _count = 0;
        _array = new T[_size];
    };
    void AppendElem(T elem){
        if (_count == _size){
            T* array = new T[_size];
            for(int i = 0; i < _size; i++)
            array[i] = _array[i];
            delete [] _array;
            _size++;
            _array = array;
        }
        
        _array[_count++] = elem;

        if (max < elem){
            max = elem;
        }
        if (min > elem){
            min = elem;
        }
    };
    bool FindElem(const T& elem) const {
        for(int i = 0; i < _count; i++){
            if(elem == _array[i]) return true;
        }
        return false;
    };
    T GetMax(){
    return max;
    };

    T GetMin(){
    return min;
    };
    ~ArrayHandler(){
        delete [] _array;
    };
};